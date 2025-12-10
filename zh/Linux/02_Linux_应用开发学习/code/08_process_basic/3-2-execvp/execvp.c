#include <unistd.h>
#include <stdio.h>

int main() {
    char *args[] = {"ls", "-l", NULL};

    printf("Before execvp\n");

    // 使用 execvp 执行 ls 命令
    execvp("ls", args);

    // 如果 execvp 成功，这行代码不会被执行
    perror("execvp failed");
    return 0;
}
