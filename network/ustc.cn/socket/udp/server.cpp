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
    int server_fd =socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in server_address;
    server_address.sin_family =AF_INET;
    // server_address.sin_addr.s_addr =htonl(INADDR_ANY);
    server_address.sin_port =htons(SERVER_PORT);
    // 绑定IP+Port    
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
    bind(server_fd,(sockaddr *)&server_address,sizeof(server_address));

    struct sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);
    // 由于udp未建立连接，因此每次接受数据都需要指定目的socket
    client_address.sin_family =AF_INET;
    // client_address.sin_addr.s_addr =htonl(INADDR_ANY);
    client_address.sin_port =htons(CLIENT_PORT);
    inet_pton(AF_INET, "127.0.0.1", &client_address.sin_addr);
    // 接收处理消息
    while (1)
    {
        char buf[1024];
        int n;
        n =recvfrom(server_fd,buf,1024,0,(sockaddr*)&client_address,&client_len);
        buf[n] ='\0';
        printf("recvfrom msg from client: %s\n", buf);
        // 发送响应给客户端（输入exit断开连接）
        if (!strcmp(buf, "exit\n"))
        {
            strcpy(buf, "Goodbye!\n");
            sendto(server_fd, buf, 1024, 0, (sockaddr*)&client_address,client_len);
            break;
        }
        else
        {
            strcpy(buf, "Received!\n");
            sendto(server_fd, buf, 1024, 0,(sockaddr*)&client_address,client_len);
        }
    }
    close(server_fd);
    exit(0);
}