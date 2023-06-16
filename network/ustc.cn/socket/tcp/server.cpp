#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

#define SERVER_PORT 8000

int main()
{
    // 1. 创建socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 绑定端口
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    // 将IP地址设置为127.0.0.1
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    // socket进入监听状态
    listen(server_socket, 2);
    printf("====== Waiting for client's request ======\n");

    // 处理客户端请求
    while (1)
    {
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        char buf[1024];
        int n;
        // 与客户端建立连接
        int connect_socket = accept(server_socket, (struct sockaddr *)NULL, NULL);
        getpeername(connect_socket, (struct sockaddr *)&client_address, &client_len);
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);

        printf("Connect to Client which ip: %s and port: %d\n",
               client_ip, ntohs(client_address.sin_port));
        // 读取客户端传输内容
        n = recv(connect_socket, buf, 1024, 0);
        buf[n] = '\0';
        printf("recv msg from client: %s\n", buf);
        // 发送响应给客户端（输入exit断开连接）
        if (!strcmp(buf, "exit\n"))
        {
            strcpy(buf, "Goodbye!\n");
            send(connect_socket, buf, strlen(buf), 0);
            close(connect_socket);
            break;
        }
        else
        {
            strcpy(buf, "Received!\n");
            send(connect_socket, buf, strlen(buf), 0);
            close(connect_socket);
        }
    }
    close(server_socket);
    return 0;
}