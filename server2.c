#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define EXPECTED_ARGS 1
#define QUEUE_SIZE 5
#define PORT 30003
#define SIZE 1000

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

    char hostName[100];
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
        unsigned* buff = malloc(SIZE * sizeof(unsigned));
        int startingPoint = 0;
        while(startingPoint < SIZE) {
            ssize_t readBytes = read(clientFd, buff, SIZE * sizeof(unsigned));
            if(!readBytes) {
                break;  // EOF
            }
            int endPoint = startingPoint + readBytes / sizeof(unsigned);
            if(endPoint > SIZE) {
                endPoint = SIZE;
            }
            int i;
            for(i = startingPoint; i < endPoint; i++) {
                buff[i] = ntohl(buff[i]);  // Convert from network byte order
            }
            if(buff[0] == 418) { 
                printf("I'm a teapot\n");
                printf("Code recieved, terminating\n");
                goto end;  // I know, I know, goto is bad, but it's the only way to break out of two loops
            }
            for(i = startingPoint; i < endPoint; i++) {
                printf("%u ", buff[i]); 
            }
            startingPoint = endPoint;
        }
        printf("\nClient disconnected\n");
        free(buff);
    }
end:
    printf("Server terminated\n");
    close(sock);
    return 0;
}
