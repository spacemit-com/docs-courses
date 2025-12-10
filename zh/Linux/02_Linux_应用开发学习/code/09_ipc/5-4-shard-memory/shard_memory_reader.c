#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok("shmfile", 65); // 生成唯一键
    int shmid = shmget(key, 1024, 0666); // 获取共享内存
    char *str = (char*) shmat(shmid, NULL, 0); // 映射共享内存

    printf("Data read from shared memory: %s\n", str);

    shmdt(str); // 断开映射
    shmctl(shmid, IPC_RMID, NULL); // 删除共享内存
    return 0;
}
