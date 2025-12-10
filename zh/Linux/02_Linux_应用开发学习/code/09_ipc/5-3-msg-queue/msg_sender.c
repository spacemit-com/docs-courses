#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

struct message {
    long mtype;       // 消息类型
    char mtext[100];  // 消息正文
};

int main() {
    key_t key = ftok("msgqueue", 65); // 生成唯一键
    int msgid = msgget(key, 0666 | IPC_CREAT); // 创建消息队列

    struct message msg;
    msg.mtype = 1; // 设置消息类型
    strcpy(msg.mtext, "Hello from message queue!");

    // 发送消息
    if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
        perror("msgsnd failed");
        exit(1);
    }

    printf("Message sent: %s\n", msg.mtext);
    return 0;
}
