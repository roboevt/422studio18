#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

#define EXPECTED_ARGS 1
#define QUEUE_SIZE 5
#define PORT 30003

int main(int argc, char* argv[]) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("socket");
        return 1;
    }
    
    if(argc != EXPECTED_ARGS) {
        printf("Usage: %s", argv[0]);
        return 1;
    }

    char* hostName[100];
    gethostname(hostName, 100);
    printf("Host name: %s\n", hostName);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
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
    //unlink(argv[1]);
    return 0;
}
