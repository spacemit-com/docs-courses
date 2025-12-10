#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *detached_thread_func(void *arg) {
    printf("Detached thread is running: %s\n", (char *)arg);
    sleep(2); // 模拟任务执行
    printf("Detached thread ends.\n");
    return NULL;
}

int main() {
    pthread_t thread_id;

    if (pthread_create(&thread_id, NULL, detached_thread_func, "Task A") != 0) {
        perror("Failed to create thread");
        return -1;
    }

    // 将线程设置为分离状态
    if (pthread_detach(thread_id) != 0) {
        perror("Failed to detach thread");
        return -1;
    }

    printf("Main thread does not wait for detached thread.\n");
    sleep(3); // 确保分离线程有足够的时间完成任务
    return 0;
}
