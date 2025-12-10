#include <stdio.h>
#include <pthread.h>

// 全局变量和互斥锁
int count = 0; 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 初始化互斥锁

// 生产者线程函数
void *producer(void *arg) {
    int times = 100000000; // 生产一亿次
    while (times--) {
        pthread_mutex_lock(&mutex);   // 加锁
        count += 1;                    // 修改共享资源
        pthread_mutex_unlock(&mutex); // 解锁
    }
    return NULL;
}

// 消费者线程函数
void *consumer(void *arg) {
    int times = 100000000; // 消费一亿次
    while (times--) {
        pthread_mutex_lock(&mutex);   // 加锁
        count -= 1;                    // 修改共享资源
        pthread_mutex_unlock(&mutex); // 解锁
    }
    return NULL;
}

int main() {
    pthread_t thread_prod, thread_cons;

    // 创建生产者和消费者线程
    pthread_create(&thread_prod, NULL, producer, NULL);
    pthread_create(&thread_cons, NULL, consumer, NULL);

    // 等待线程结束
    pthread_join(thread_prod, NULL);
    pthread_join(thread_cons, NULL);

    // 输出最终结果
    printf("Final count = %d\n", count);

    return 0;
}
