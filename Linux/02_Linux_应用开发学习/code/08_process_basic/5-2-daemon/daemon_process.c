#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void create_daemon() {
    pid_t pid;

    // 第一步：创建子进程，退出父进程
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        // 父进程退出
        exit(EXIT_SUCCESS);
    }

    // 第二步：创建新会话
    if (setsid() < 0) {
        perror("setsid failed");
        exit(EXIT_FAILURE);
    }

    // 第三步：更改工作目录
    if (chdir("/") < 0) {
        perror("chdir failed");
        exit(EXIT_FAILURE);
    }

    // 第四步：重设文件权限掩码
    umask(0);

    // 第五步：关闭文件描述符
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // 守护进程的核心逻辑
    while (1) {
        // 模拟守护进程运行：每隔 5 秒写入日志
        int fd = open("/tmp/daemon.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0) {
            exit(EXIT_FAILURE);
        }
        dprintf(fd, "Daemon is running...\n");
        close(fd);
        sleep(5);
    }
}

int main() {
    create_daemon();
    return 0;
}
