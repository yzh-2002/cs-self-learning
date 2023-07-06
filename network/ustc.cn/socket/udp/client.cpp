#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // POSIX操作系统接口相关的函数和符号常量
#include <sys/socket.h> //socket函数
#include <netinet/in.h> //定义网络相关结构体和函数
#include <arpa/inet.h> //inet_pton等函数

#define SERVER_PORT 8080
#define CLIENT_PORT 8081

int main(){
    // 创建socket(UDP)
    int client_fd =socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in client_address;
    client_address.sin_family =AF_INET;
    // client_address.sin_addr.s_addr =htonl(INADDR_ANY);
    client_address.sin_port =htons(CLIENT_PORT);
    // 绑定IP+Port    
    inet_pton(AF_INET, "127.0.0.1", &client_address.sin_addr);
    bind(client_fd,(sockaddr *)&client_address,sizeof(client_address));

    struct sockaddr_in server_address;
    socklen_t server_len = sizeof(server_address);
    // 由于udp未建立连接，因此每次接受数据都需要指定目的socket
    server_address.sin_family =AF_INET;
    // server_address.sin_addr.s_addr =htonl(INADDR_ANY);
    server_address.sin_port =htons(SERVER_PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
    // 向服务端发送消息
    while (1)
    {
        char sendline[1024],recvline[1024];
        int n;
        printf("send msg to server: ");
        fgets(sendline, 1024, stdin);
        sendto(client_fd, sendline, strlen(sendline), 0,(sockaddr*)&server_address,server_len);
        // FIXME:返回值为接受字节数
        n =recvfrom(client_fd,recvline,1024,0,(sockaddr*)&server_address,&server_len);
        recvline[n]='\0';
        printf("recv msg from server: %s\n", recvline);
        if (!strcmp(recvline, "Goodbye!\n"))
        {
            break;
        } 
    }
    close(client_fd);
    exit(0);
}