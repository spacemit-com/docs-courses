#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return -1;
    }

    if (pid == 0) {
        // 子进程写入文件
        write(fd, "Child process writing.\n", 23);
    } else {
        // 父进程写入文件
        write(fd, "Parent process writing.\n", 24);
    }

    close(fd);
    return 0;
}
