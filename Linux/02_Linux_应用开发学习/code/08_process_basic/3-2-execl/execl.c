#include <unistd.h>
#include <stdio.h>

int main() {
    printf("Before exec\n");

    // 使用 execl 执行 ls 命令
    execl("/bin/ls", "ls", "-l", NULL);

    // 如果 exec 成功，这行代码不会被执行
    perror("execl failed");
    return 0;
}
