#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_THREADS 5  // 最大线程数
#define QUEUE_SIZE 20  // 请求队列大小

// 请求结构体
typedef struct {
    int socket;
    struct sockaddr_in address;
} request_t;

// 线程池结构体
typedef struct {
    pthread_t threads[MAX_THREADS];       // 线程数组
    request_t request_queue[QUEUE_SIZE];  // 请求队列
    int queue_size;                       // 当前队列大小
    int queue_front;                      // 队列前端
    int queue_rear;                       // 队列后端
    sem_t queue_sem;                      // 信号量，用于控制队列
    pthread_mutex_t queue_lock;           // 互斥锁，用于保护队列
    int stop;                             // 停止标志
} thread_pool_t;

// 线程池工作函数
void* worker(void* pool) {
    thread_pool_t* thread_pool = (thread_pool_t*)pool;

    while (1) {
        sem_wait(&thread_pool->queue_sem);  // 等待队列

        pthread_mutex_lock(&thread_pool->queue_lock);  // 获取锁
        if (thread_pool->stop) {
            pthread_mutex_unlock(&thread_pool->queue_lock);
            break;  // 如果停止标志被设置，退出循环
        }

        // 从队列获取请求
        request_t req = thread_pool->request_queue[thread_pool->queue_front];
        thread_pool->queue_front = (thread_pool->queue_front + 1) % QUEUE_SIZE;
        thread_pool->queue_size--;
        pthread_mutex_unlock(&thread_pool->queue_lock);  // 释放锁

        // 处理请求
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &req.address.sin_addr, client_ip, sizeof(client_ip));
        int client_port = ntohs(req.address.sin_port);
        printf("Client connected: IP = %s, Port = %d\n", client_ip,
               client_port);

        // 向客户端发送数据，包含线程 ID
        char response[256];
        pthread_t thread_id = pthread_self();
        snprintf(response, sizeof(response), "Hello from thread %lu!\n",
                 thread_id);
        write(req.socket, response, strlen(response));

        // 关闭套接字
        close(req.socket);
    }
    return NULL;
}

// 初始化线程池
thread_pool_t* thread_pool_init() {
    thread_pool_t* pool = malloc(sizeof(thread_pool_t));
    pool->queue_size = 0;
    pool->queue_front = 0;
    pool->queue_rear = 0;
    pool->stop = 0;
    sem_init(&pool->queue_sem, 0, 0);
    pthread_mutex_init(&pool->queue_lock, NULL);

    // 创建线程
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_create(&pool->threads[i], NULL, worker, pool);
    }
    return pool;
}

// 向线程池添加请求
void thread_pool_add_request(thread_pool_t* pool, request_t req) {
    pthread_mutex_lock(&pool->queue_lock);  // 获取锁

    // 添加请求到队列
    pool->request_queue[pool->queue_rear] = req;
    pool->queue_rear = (pool->queue_rear + 1) % QUEUE_SIZE;
    pool->queue_size++;

    pthread_mutex_unlock(&pool->queue_lock);  // 释放锁
    sem_post(&pool->queue_sem);               // 发送信号
}

// 停止线程池
void thread_pool_destroy(thread_pool_t* pool) {
    pthread_mutex_lock(&pool->queue_lock);
    pool->stop = 1;  // 设置停止标志
    pthread_mutex_unlock(&pool->queue_lock);

    // 发送信号给所有线程
    for (int i = 0; i < MAX_THREADS; i++) {
        sem_post(&pool->queue_sem);
    }

    // 等待所有线程结束
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(pool->threads[i], NULL);
    }

    // 清理资源
    sem_destroy(&pool->queue_sem);
    pthread_mutex_destroy(&pool->queue_lock);
    free(pool);
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

    // 初始化线程池
    thread_pool_t* pool = thread_pool_init();

    // 接收客户端请求
    while (1) {
        struct sockaddr_in clnt_addr;
        socklen_t clnt_addr_size = sizeof(clnt_addr);
        int clnt_sock =
            accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

        // 添加请求到线程池
        request_t req;
        req.socket = clnt_sock;
        req.address = clnt_addr;
        thread_pool_add_request(pool, req);
    }

    // 关闭服务器套接字
    close(serv_sock);
    // 销毁线程池
    thread_pool_destroy(pool);
    return 0;
}
