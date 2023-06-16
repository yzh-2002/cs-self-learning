#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 8000
#define MAX_LINE 1024

int main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAX_LINE], sendline[MAX_LINE];
    struct sockaddr_in servaddr;

    if (argc != 2)
    {
        printf("usage: ./client <ipaddress>\n");
        return 0;
    }
    // 创建socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // 初始化socket地址
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        printf("inet_pton error for %s\n", argv[1]);
        return 0;
    }
    // 连接服务器
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
        return 0;
    }
    while (1)
    {
        // 发送请求给服务器
        printf("send msg to server: ");
        fgets(sendline, MAX_LINE, stdin);
        if (send(sockfd, sendline, strlen(sendline), 0) < 0)
        {
            printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
            return 0;
        }
        // 接收响应
        if ((n = recv(sockfd, recvline, MAX_LINE, 0)) == -1)
        {
            printf("recv msg error: %s(errno: %d)\n", strerror(errno), errno);
            return 0;
        }
        recvline[n] = '\0';
        printf("recv msg from server: %s\n", recvline);
        if (!strcmp(recvline, "Goodbye!\n"))
        {
            break;
        }
    }
    close(sockfd);
    return 0;
}
