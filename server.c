#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define EXPECTED_ARGS 2
#define QUEUE_SIZE 5

int main(int argc, char* argv[]) {
    int sock = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("socket");
        return 1;
    }
    
    if(argc != EXPECTED_ARGS) {
        printf("Usage: %s <addr>", argv[0]);
        return 1;
    }
    struct sockaddr_un addr;
    addr.sun_family = AF_LOCAL;
    if(strlen(argv[1]) > sizeof(addr.sun_path) - 1) {
        printf("Path too long");
        return 1;
    }
    strcpy(addr.sun_path, argv[1]);
    if(bind(sock, (const struct sockaddr *)&addr, sizeof(addr))) {
        perror("bind");
        return 1;
    }
    if(listen(sock, QUEUE_SIZE)) {
        perror("listen");
        return 1;
    }
    while(1) {
        int clientFd = accept(sock, NULL, NULL);
        if(clientFd < 0) {
            perror("accept");
            return 1;
        }
        printf("Client connected\n");
        FILE* client = fdopen(clientFd, "r");
        if(client == NULL) {
            perror("fdopen");
            return 1;
        }
        unsigned num;
        while(fscanf(client, "%u ", &num) != EOF) {
            printf("%u\n", num);
            if(num == 418) {
                printf("I'm a teapot\n");
                printf("Code recieved, terminating\n");
                goto end;  // I know, I know, goto is bad, but it's the only way to break out of two loops
            }
        }
        printf("Client disconnected\n");
    }
end:
    printf("Server terminated\n");
    close(sock);
    unlink(argv[1]);
    return 0;
}
