#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// 处理客户端请求的线程函数
void* handle_client(void* client_socket) {
    int clnt_sock = *(int*)client_socket;  // 获取客户端套接字
    free(client_socket);                   // 释放动态分配的内存

    // 提取客户端的 IP 地址和端口
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    getpeername(clnt_sock, (struct sockaddr*)&clnt_addr,
                &clnt_addr_size);  // 获取客户端地址信息

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clnt_addr.sin_addr, client_ip, sizeof(client_ip));
    int client_port = ntohs(clnt_addr.sin_port);

    // 打印客户端信息
    printf("Client connected: IP = %s, Port = %d\n", client_ip, client_port);

    // 获取线程ID
    pthread_t thread_id = pthread_self();

    // 向客户端发送数据
    char response[256];
    snprintf(response, sizeof(response), "Hello from thread %lu!\n", thread_id);
    write(clnt_sock, response, strlen(response));

    // 模拟服务器处理请求的时间
    sleep(1);

    // 关闭套接字
    close(clnt_sock);
    return NULL;
}

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
    while (1) {
        struct sockaddr_in clnt_addr;
        socklen_t clnt_addr_size = sizeof(clnt_addr);
        int* clnt_sock = malloc(sizeof(int));  // 动态分配内存来保存客户端套接字
        *clnt_sock =
            accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

        // 创建一个线程处理客户端请求
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, clnt_sock) != 0) {
            perror("Failed to create thread");
            close(*clnt_sock);  // 若线程创建失败，关闭套接字
            free(clnt_sock);    // 释放内存
        }
        pthread_detach(thread_id);  // 使线程在结束后自动回收资源
    }
    close(serv_sock);
    return 0;
}
