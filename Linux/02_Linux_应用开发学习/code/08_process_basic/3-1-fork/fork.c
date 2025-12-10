#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); // 调用 fork 创建子进程

    if (pid == -1) {
        perror("fork failed");
        return -1;
    }

    if (pid == 0) {
        // 子进程
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else {
        // 父进程
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
    }

    return 0;
}
