#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return -1;
    }

    if (pid == 0) {
        // 子进程
        printf("Child process (PID: %d) exiting...\n", getpid());
        exit(0); // 子进程退出
    } else {
        // 父进程，故意不调用 wait() 回收子进程
        printf("Parent process (PID: %d) sleeping...\n", getpid());
        sleep(30); // 父进程休眠，子进程变为僵尸进程
    }

    return 0;
}
