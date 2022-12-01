#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define EXPECTED_ARGS 1
#define EXPECTED_ARGS_QUIT 2
#define QUEUE_SIZE 5
#define PORT 30003

int main(int argc, char* argv[]) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("socket");
        return 1;
    }
    if(argc != EXPECTED_ARGS && argc != EXPECTED_ARGS_QUIT) {
        printf("Usage: %s <quit>\n", argv[0]);
        return 1;
    }
    int quit = 0;
    if(argc == EXPECTED_ARGS_QUIT) {
        if(strcmp(argv[1], "quit") == 0) {
            quit = 1;
        } else {
            printf("Usage: %s <addr> <quit>\n", argv[0]);
            return 1;
        }
    }

    char* hostName[100];
    gethostname(hostName, 100);
    printf("Host name: %s\n", hostName);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    if(!inet_aton("128.252.167.161", &addr.sin_addr)) {
        perror("inet_aton");
        return 1;
    }
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr))) {
        perror("connect");
        return 1;
    }
    FILE* server = fdopen(sock, "w");
    if(server == NULL) {
        perror("fdopen");
        return 1;
    }
    getaddrinfo()
    if(quit) {
        fprintf(server, "418");
    } else {
        fprintf(server, "1 2 3");
        printf("1 2 3\n");
    }
    fclose(server);
    return 0;
}