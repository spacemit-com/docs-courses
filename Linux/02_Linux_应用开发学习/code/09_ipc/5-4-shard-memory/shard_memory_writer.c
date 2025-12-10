#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    key_t key = ftok("shmfile", 65); // 生成唯一键
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // 创建共享内存
    char *str = (char*) shmat(shmid, NULL, 0); // 映射共享内存

    printf("Write data: ");
    fgets(str, 1024, stdin); // 从用户输入读取数据

    shmdt(str); // 断开映射
    return 0;
}
