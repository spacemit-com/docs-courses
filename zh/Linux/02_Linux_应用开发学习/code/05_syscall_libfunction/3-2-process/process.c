#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork(); // 创建子进程
    if (pid == -1) {
        perror("fork");
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
