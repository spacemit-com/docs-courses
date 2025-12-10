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
        sleep(20); // 延迟 20 秒
        printf("Child process (PID: %d), my parent is now: %d\n", getpid(), getppid());
    } else {
        // 父进程
        printf("Parent process (PID: %d) exiting...\n", getpid());
        exit(0); // 父进程退出
    }

    return 0;
}
