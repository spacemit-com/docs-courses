#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // 创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  // 每个字节都用0填充
    serv_addr.sin_family = AF_INET;            // 使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // 具体的IP地址
    serv_addr.sin_port = htons(1234);                    // 端口
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // 进入监听状态，等待用户发起请求
    listen(serv_sock, 20);

    // 接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    while (1) {
        int clnt_sock =
            accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

        // 提取客户端的 IP 地址和端口
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clnt_addr.sin_addr, client_ip, sizeof(client_ip));
        int client_port = ntohs(clnt_addr.sin_port);

        // 打印客户端信息
        printf("Client connected: IP = %s, Port = %d\n", client_ip,
               client_port);

        // 向客户端发送数据
        char str[] = "Hello, this is server!\n";
        write(clnt_sock, str, sizeof(str));

        // 关闭套接字
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}