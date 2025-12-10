#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// 子线程计算平方值
void *compute_square(void *arg) {
    int n = *(int *)arg;  // 获取输入参数
    int *result = malloc(sizeof(int));  // 为结果分配内存
    if (result == NULL) {
        perror("Failed to allocate memory");
        pthread_exit(NULL);
    }
    *result = n * n;  // 计算平方值
    printf("Thread: Computed square of %d is %d\n", n, *result);
    pthread_exit((void *)result);  // 显式终止线程
}

int main() {
    pthread_t thread_id;  // 线程 ID
    int num = 5;          // 输入值
    int *result;          // 存储线程返回值

    // 创建线程
    if (pthread_create(&thread_id, NULL, compute_square, (void *)&num) != 0) {
        perror("Failed to create thread");
        return EXIT_FAILURE;
    }

    // 等待线程完成，并获取返回值
    if (pthread_join(thread_id, (void **)&result) != 0) {
        perror("Failed to join thread");
        return EXIT_FAILURE;
    }

    printf("Main: Square of %d is %d\n", num, *result);  // 输出结果
    free(result);  // 释放线程返回的动态内存

    return EXIT_SUCCESS;
}
