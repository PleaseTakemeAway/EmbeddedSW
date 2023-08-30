#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

#define PORT 55000
int main()
{
    int server_socket;
    int client_socket;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int client_address_size;
    char toClient[] = "Hello Client\n";
    char fromClient[100];

    server_socket = socket(PF_INET,SOCK_STREAM,0);
    printf("Server Socket Create!!\n");
    memset(&server_address,0,sizeof(server_address));
    /* server_address에 서버의 주소 정보 대입*/
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);
    /*서버 소켓에 IP와 PORT 설정*/
    bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));
    listen(server_socket,5);
    printf("Wait Client....\n");
    client_socket = accept(server_socket,(struct sockaddr*)&client_address,&client_address_size);
    printf("Client Connect!\n");

    read(client_socket,fromClient,sizeof(fromClient));
    printf("From Client Message:%s\n",fromClient);
    write(client_socket,toClient,sizeof(toClient));
    printf("To Client Message:%s\n",toClient);

    close(client_socket);
    return 0;
}