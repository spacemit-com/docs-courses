#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h> // 包含 memset 函数

int main() {
    const char *fifo_path = "my_fifo";

    int fd = open(fifo_path, O_RDONLY); // 打开管道读端
  
    char buffer[100];
    memset(buffer, 0, sizeof(buffer)); // 清空缓冲区
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1); // 读取数据
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0'; // 确保字符串以 '\0' 结尾
        printf("Received message: %s\n", buffer);
    } else {
        perror("Failed to read from FIFO");
    }

    close(fd); // 关闭管道读端

    return 0;
}
