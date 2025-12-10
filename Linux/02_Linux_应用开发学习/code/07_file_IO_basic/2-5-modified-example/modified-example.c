#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "example.txt";
    int fd; // 文件描述符
    char buffer[256];

    // 打开文件，这里将 O_WRONLY 标识修改为 O_RDWR 是因为后续还要进行读的操作
    fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR); 
    if (fd == -1) {
        perror("无法打开文件以写入");
        return 1;
    }

    const char *text = "Hello, this is a file writing example.\n";
    ssize_t bytes_written = write(fd, text, strlen(text));
    if (bytes_written == -1) {
        perror("写入文件时出错");
        close(fd);
        return 1;
    }

    const char *more_text = "Let's write some more lines into this file.\n";
    bytes_written = write(fd, more_text, strlen(more_text));
    if (bytes_written == -1) {
        perror("写入文件时出错");
        close(fd);
        return 1;
    }

    printf("已将内容写入 %s，且未关闭文件描述符.\n", filename);

    // 设置文件偏移量为 SEEK_SET 即文件开头
    lseek(fd, 0, SEEK_SET);

    printf("\n读取的内容:\n");

    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0'; // 确保字符串结束
        printf("%s", buffer);
    }

    if (bytes_read == -1) {
        perror("读取文件时出错");
    }

    close(fd); // 关闭文件

    return 0;
}