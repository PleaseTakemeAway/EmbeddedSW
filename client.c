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

int main(int argc, char *argv[]) {
    int client_fd;
    struct sockaddr_in server_addr;
    char buf[BUF_LEN + 1];

    if (argc != 3) {
        printf("Usage: %s ip_address port_number\n", argv[0]);
        exit(0);
    }

    if ((client_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Client: Can't create socket\n");
        exit(0);
    }

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Client: Can't connect to the server.\n");
        exit(0);
    }

    printf("Client: Connected to the server.\n");

    while (1) {
        printf("Client: Enter your message (or 'q' to quit): ");
        fgets(buf, sizeof(buf), stdin);
        send(client_fd, buf, strlen(buf), 0);

        if (strcmp(buf, "q\n") == 0) {
            printf("Client: Closing connection.\n");
            break;
        }

        int msg_size = recv(client_fd, buf, sizeof(buf), 0);
        if (msg_size <= 0) {
            printf("Client: Connection closed by server.\n");
            break;
        }
        buf[msg_size] = '\0';
		for(int i=0;i<(msg_size-1);i++)
		{	
        	printf("Server: %c\n", buf[i]);
		}
    }

    close(client_fd);
    return 0;
}
