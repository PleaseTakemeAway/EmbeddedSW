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
    int clientSocket;
    struct sockaddr_in server_address;
    char toServer[] ="Hello Server!! I'm Client!!";
    char fromServer[100];
    clientSocket = socket(PF_INET,SOCK_STREAM,0);
    printf("Create Client Socket!!\n");
    
    memset(&server_address,0,sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port=htons(PORT);

    connect(clientSocket,(struct sockaddr*)&server_address,sizeof(server_address));
    printf("Connect Server!!\n");
    write(clientSocket,toServer,sizeof(toServer));
    printf("To server Message:%s\n",toServer);
    
    read(clientSocket,fromServer,sizeof(fromServer));
    printf("From Server Message:%s\n",fromServer);
    close(clientSocket);
    return 0;
}