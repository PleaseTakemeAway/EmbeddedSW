#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_LEN 128

void char_change(char *msg);

int main(int argc, char *argv[]) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    int len, msg_size;
    char buf[BUF_LEN + 1];

    if (argc != 2) {
        printf("Usage: %s port\n", argv[0]);
        exit(0);
    }

    if ((server_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Server: Can't open stream socket.");
        exit(0);
    }

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Server: Can't bind local address.\n");
        exit(0);
    }

    listen(server_fd, 5);
    printf("Server: Waiting for connections...\n");

    len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);

    if (client_fd < 0) {
        printf("Server: Accept failed.\n");
        exit(0);
    }

    printf("Server: Connection established.\n");

    while (1) {
        msg_size = recv(client_fd, buf, sizeof(buf), 0);
        if (msg_size <= 0) {
            printf("Server: Connection closed by client.\n");
            break;
        }
        buf[msg_size] = '\0';
        printf("Client: %s", buf);

        printf("Server: Enter your message (or 'q' to quit): ");
        fgets(buf, sizeof(buf), stdin);
        send(client_fd, buf, strlen(buf), 0);
        
        if (strcmp(buf, "q\n") == 0) {
            printf("Server: Closing connection.\n");
            break;
        }
    }

    close(client_fd);
    close(server_fd);
    return 0;
}

