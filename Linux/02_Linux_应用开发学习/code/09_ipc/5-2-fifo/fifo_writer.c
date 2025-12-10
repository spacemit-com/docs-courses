#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h> // 包含 strlen 函数

int main() {
    const char *fifo_path = "my_fifo";
    if (mkfifo(fifo_path, 0666) == -1) { // 创建有名管道
        perror("Failed to create FIFO");
    }

    int fd = open(fifo_path, O_WRONLY); // 打开管道写端

    const char *message = "Hello through FIFO!";
    ssize_t bytes_written = write(fd, message, strlen(message) + 1); // 写入数据
    if (bytes_written == -1) {
        perror("Failed to write to FIFO");
    } else {
        printf("Message sent: %s\n", message);
    }

    close(fd); // 关闭管道写端

    return 0;
}
