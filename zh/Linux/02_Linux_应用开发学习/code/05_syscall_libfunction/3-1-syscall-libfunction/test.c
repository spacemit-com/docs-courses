#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    // 使用系统调用write
    const char *data1 = "Hello, This content is written by System Call!\n";
    int fd = open("syscall.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, data1, strlen(data1));
    close(fd);

    // 使用库函数fwrite
    const char *data2 = "Hello, This content is written by Library Function!\n";
    FILE *fp = fopen("libfunc.txt", "w");
    fwrite(data2, 1, strlen(data2), fp);
    fclose(fp);

    return 0;
}
