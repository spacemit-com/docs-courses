#include <arpa/inet.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

void init_openssl() {
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

void cleanup_openssl() {
    EVP_cleanup();
}

SSL_CTX* create_context() {
    const SSL_METHOD* method;
    SSL_CTX* ctx;

    method = SSLv23_client_method();  // 选择 SSL 方法
    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    return ctx;
}

int main() {
    init_openssl();                   // 初始化 OpenSSL
    SSL_CTX* ctx = create_context();  // 创建 SSL 上下文

    const char* server_ip = "127.0.0.1";  // 服务器的IP地址
    int port = 1234;                      // 服务器端口
    int num_attempts = 5;                 // 连接次数

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

        // 创建 SSL 连接
        SSL* ssl = SSL_new(ctx);
        SSL_set_fd(ssl, sock);
        if (SSL_connect(ssl) <= 0) {  // 执行 SSL 握手
            ERR_print_errors_fp(stderr);
        } else {
            // 读取服务器传回的数据
            char buffer[40];
            ssize_t bytes_read =
                SSL_read(ssl, buffer, sizeof(buffer) - 1);  // 使用 SSL_read
            if (bytes_read < 0) {
                perror("Failed to read from server");
            } else {
                buffer[bytes_read] = '\0';  // 确保字符串以 null 结尾
                printf("Message from server on port %d: %s\n", port, buffer);
            }
        }

        // 关闭 SSL 连接
        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(sock);

        // 暂停 1 秒钟
        sleep(1);
    }

    SSL_CTX_free(ctx);  // 释放 SSL 上下文
    cleanup_openssl();  // 清理 OpenSSL
    return 0;
}
