#include <arpa/inet.h>
#include <netinet/in.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
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

    method = SSLv23_server_method();  // 选择 SSL 方法
    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    return ctx;
}

void configure_context(SSL_CTX* ctx) {
    // 加载证书和私钥
    if (SSL_CTX_use_certificate_file(ctx, "server.crt", SSL_FILETYPE_PEM) <=
        0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, "server.key", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

int main() {
    init_openssl();                   // 初始化 OpenSSL
    SSL_CTX* ctx = create_context();  // 创建 SSL 上下文
    configure_context(ctx);           // 配置 SSL 上下文

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

        // 创建 SSL 连接
        SSL* ssl = SSL_new(ctx);
        SSL_set_fd(ssl, clnt_sock);
        if (SSL_accept(ssl) <= 0) {
            ERR_print_errors_fp(stderr);
        } else {
            // 向客户端发送数据
            char str[] = "Hello, this is server!\n";
            SSL_write(ssl, str, sizeof(str));
        }

        // 关闭 SSL 连接
        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(clnt_sock);
    }
    close(serv_sock);
    SSL_CTX_free(ctx);  // 释放 SSL 上下文
    cleanup_openssl();  // 清理 OpenSSL
    return 0;
}
