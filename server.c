#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 55000

int main() {
    int server_socket;
    int client_socket;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    socklen_t client_address_size; // 변경된 부분
    char toClient[] = "Hello Client\n";
    char fromClient[100];

    server_socket = socket(PF_INET, SOCK_STREAM, 0);
    printf("Server Socket Created!!\n");
    memset(&server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    listen(server_socket, 5);
    printf("Waiting for Clients...\n");
    
    client_address_size = sizeof(client_address); // 초기화 추가
    
    client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);
    printf("Client Connected!\n");

    read(client_socket, fromClient, sizeof(fromClient));
    printf("From Client Message: %s\n", fromClient);
    write(client_socket, toClient, sizeof(toClient));
    printf("To Client Message: %s\n", toClient);

    close(client_socket);
    close(server_socket);
    return 0;
}