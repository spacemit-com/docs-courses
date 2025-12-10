#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

struct message {
    long mtype;       // 消息类型
    char mtext[100];  // 消息正文
};

int main() {
    key_t key = ftok("msgqueue", 65); // 生成唯一键
    int msgid = msgget(key, 0666 | IPC_CREAT); // 获取消息队列

    struct message msg;

    // 接收消息
    if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1) {
        perror("msgrcv failed");
        exit(1);
    }

    printf("Message received: %s\n", msg.mtext);

    // 删除消息队列
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
