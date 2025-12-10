#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

int main() {
    const char* server_ip = "127.0.0.1";  // 服务器的IP地址
    int port = 1234;                      // 服务器端口
    int num_attempts = 10;                // 连接次数

    for (int i = 0; i < num_attempts; i++) {
        // 创建套接字
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Socket creation failed");
            exit(EXIT_FAILURE);
        }

        // 向服务器发起请求
        struct sockaddr_in serv_addr;
        memset(&serv_addr, 0, sizeof(serv_addr));  // 每个字节都用0填充
        serv_addr.sin_family = AF_INET;            // 使用IPv4地址
        serv_addr.sin_addr.s_addr = inet_addr(server_ip);  // 具体的IP地址
        serv_addr.sin_port = htons(port);  // 设置端口为1234

        // 尝试连接到服务器
        if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) <
            0) {
            perror("Connection failed");
            close(sock);
            sleep(1);  // 连接失败后休眠1秒
            continue;  // 如果连接失败，继续尝试下一个连接
        }

        // 读取服务器传回的数据
        char buffer[40];
        ssize_t bytes_read = read(sock, buffer, sizeof(buffer) - 1);
        if (bytes_read < 0) {
            perror("Failed to read from server");
        } else {
            buffer[bytes_read] = '\0';  // 确保字符串以 null 结尾
            printf("Message from server on port %d: %s", port, buffer);
        }

        // 关闭套接字
        close(sock);
    }

    return 0;
}
