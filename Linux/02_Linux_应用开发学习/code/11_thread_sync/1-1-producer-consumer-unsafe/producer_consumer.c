#include <stdio.h>
#include <pthread.h>

int count = 0; // 共享变量

void *producer(void *arg) {
    for (int i = 0; i < 100000000; i++) {
        count++; // 生产者操作
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < 100000000; i++) {
        count--; // 消费者操作
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final count value: %d\n", count);
    return 0;
}
