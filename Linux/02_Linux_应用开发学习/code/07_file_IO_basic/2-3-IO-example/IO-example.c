#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "example.txt";
    int fd; // 文件描述符
    char buffer[256];

    // 写入文件
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR); // 打开文件以进行写入
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

    close(fd); // 关闭文件
    printf("已将内容写入 %s.\n", filename);

    // 读取文件
    fd = open(filename, O_RDONLY); // 打开文件以进行读取
    if (fd == -1) {
        perror("无法打开文件以读取");
        return 1;
    }

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