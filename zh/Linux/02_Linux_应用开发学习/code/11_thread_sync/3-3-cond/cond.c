#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count = 0;
const int buf_size = 10; // 缓冲区大小
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (count >= buf_size) { // 缓冲区满时等待
            printf("缓冲区已满，等待消费者消费。\n");
            pthread_cond_wait(&cond, &mutex);
        }
        count += 1;
        printf("生产一个产品，缓冲区当前产品数量：%d\n", count);
        pthread_cond_signal(&cond); // 通知消费者
        printf("通知消费者...\n");
        pthread_mutex_unlock(&mutex);
        sleep(1); // 模拟生产的时间
    }
}

void *consumer(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (count <= 0) { // 缓冲区为空时等待
            printf("缓冲区已空，等待生产者生产。\n");
            pthread_cond_wait(&cond, &mutex);
        }
        count -= 1;
        printf("消费一个产品，缓冲区当前产品数量：%d\n", count);
        pthread_cond_signal(&cond); // 通知生产者
        printf("通知生产者...\n");
        pthread_mutex_unlock(&mutex);
        sleep(1); // 模拟消费的时间
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    return 0;
}
