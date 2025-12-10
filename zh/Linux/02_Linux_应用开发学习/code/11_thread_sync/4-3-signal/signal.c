#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUF_SIZE 10

int buffer[BUF_SIZE];
int count = 0;

sem_t empty;  // 空闲缓冲区信号量
sem_t full;   // 已占用缓冲区信号量
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg) {
    int item = 0;
    while (1) {
        sleep(1); // 模拟生产时间
        sem_wait(&empty); // 等待空闲缓冲区
        pthread_mutex_lock(&mutex);

        buffer[count++] = ++item; // 生产产品
        printf("Produced item %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&full); // 增加已占用缓冲区
    }
}

void *consumer(void *arg) {
    while (1) {
        sem_wait(&full); // 等待有产品可消费
        pthread_mutex_lock(&mutex);

        int item = buffer[--count]; // 消费产品
        printf("Consumed item %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // 增加空闲缓冲区
        sleep(1); // 模拟消费时间
    }
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, BUF_SIZE); // 初始化空闲信号量
    sem_init(&full, 0, 0);         // 初始化已占用信号量

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
