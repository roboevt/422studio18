#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define EXPECTED_ARGS 2
#define EXPECTED_ARGS_QUIT 3
#define QUEUE_SIZE 1

int main(int argc, char* argv[]) {
    int sock = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("socket");
        return 1;
    }
    if(argc != EXPECTED_ARGS && argc != EXPECTED_ARGS_QUIT) {
        printf("Usage: %s <addr> <quit>\n", argv[0]);
        return 1;
    }
    int quit = 0;
    if(argc == EXPECTED_ARGS_QUIT) {
        if(strcmp(argv[2], "quit") == 0) {
            quit = 1;
        } else {
            printf("Usage: %s <addr> <quit>\n", argv[0]);
            return 1;
        }
    }
    struct sockaddr_un addr;
    addr.sun_family = AF_LOCAL;
    if(strlen(argv[1]) > sizeof(addr.sun_path)) {
        printf("Path too long");
        return 1;
    }
    strcpy(addr.sun_path, argv[1]);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr))) {
        perror("connect");
        return 1;
    }
    FILE* server = fdopen(sock, "w");
    if(server == NULL) {
        perror("fdopen");
        return 1;
    }
    if(quit) {
        fprintf(server, "418");
    } else {
        fprintf(server, "1 2 3");
        printf("1 2 3\n");
    }
    fclose(server);
    return 0;
}