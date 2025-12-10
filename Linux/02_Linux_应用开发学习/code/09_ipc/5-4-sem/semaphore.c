#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

union semun {
    int val;
};

void wait_semaphore(int semid) {
    struct sembuf sem_op = {0, -1, 0}; // P 操作
    semop(semid, &sem_op, 1);
}

void signal_semaphore(int semid) {
    struct sembuf sem_op = {0, 1, 0}; // V 操作
    semop(semid, &sem_op, 1);
}

int main() {
    key_t key = ftok("path", 65);
    int semid = semget(key, 1, 0666 | IPC_CREAT);

    union semun arg;
    arg.val = 1; // 初始化信号量为 1
    semctl(semid, 0, SETVAL, arg);

    if (fork() == 0) {
        // 子进程：读取共享资源
        for (int i = 0; i < 5; i++) {
            wait_semaphore(semid);
            printf("Child process reading...\n");
            sleep(1);
            signal_semaphore(semid);
            sleep(1);
        }
    } else {
        // 父进程：写入共享资源
        for (int i = 0; i < 5; i++) {
            wait_semaphore(semid);
            printf("Parent process writing...\n");
            sleep(1);
            signal_semaphore(semid);
            sleep(1);
        }
        wait(NULL); // 等待子进程结束
        semctl(semid, 0, IPC_RMID); // 删除信号量
    }

    return 0;
}
