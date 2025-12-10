#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_func(void *arg) {
    printf("Thread is running: %s\n", (char *)arg);
    return NULL;
}

int main() {
    pthread_t thread_id;
    const char *message = "Hello, Thread!";

    if (pthread_create(&thread_id, NULL, thread_func, (void *)message) != 0) {
        perror("Failed to create thread");
        return EXIT_FAILURE;
    }

    // 等待线程完成
    pthread_join(thread_id, NULL);

    printf("Main thread ends.\n");
    return EXIT_SUCCESS;
}
