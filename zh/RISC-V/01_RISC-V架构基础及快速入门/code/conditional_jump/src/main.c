#include "type.h"
#include "string.h"
#include "printk.h"
#include "asm/csr.h"
#include "asm/timer.h"
#include "asm/irq.h"

// 条件跳转指令函数声明
int beq_example(int x, int y);
int bne_example(int x, int y);
int blt_example(int x, int y);
int bltu_example(unsigned int x, unsigned int y);
int bge_example(int x, int y);
int bgeu_example(unsigned int x, unsigned int y);
int bgt_example(int x, int y);
int bgtu_example(unsigned int x, unsigned int y);
int ble_example(int x, int y);
int bleu_example(unsigned int x, unsigned int y);

int main() {
    // 条件跳转指令测试
    int x1, x2 = 5, x3 = 3, x4 = 7;
    unsigned int  ux2 = 3, ux3 = 7;

    x1 = beq_example(x2, x2);
    printk("Result of risc-v assembly 'beq x1, x2, target_label' is: %d\n", x1);

    x1 = bne_example(x2, x3);
    printk("Result of risc-v assembly 'bne x1, x3, target_label' is: %d\n", x1);

    x1 = blt_example(x3, x4);
    printk("Result of risc-v assembly 'blt x3, x4, target_label' is: %d\n", x1);

    x1 = bltu_example(ux2, ux3);
    printk("Result of risc-v assembly 'bltu x3, x4, target_label' is: %d\n", x1);

    x1 = bge_example(x4, x3);
    printk("Result of risc-v assembly 'bge x4, x3, target_label' is: %d\n", x1);

    x1 = bgeu_example(ux3, ux2);
    printk("Result of risc-v assembly 'bgeu x4, x3, target_label' is: %d\n", x1);

    x1 = bgt_example(x4, x3);
    printk("Result of risc-v assembly 'bgt x4, x3, target_label' is: %d\n", x1);

    x1 = bgtu_example(ux3, ux2);
    printk("Result of risc-v assembly 'bgtu x4, x3, target_label' is: %d\n", x1);

    x1 = ble_example(x3, x4);
    printk("Result of risc-v assembly 'ble x3, x4, target_label' is: %d\n", x1);

    x1 = bleu_example(ux2, ux3);
    printk("Result of risc-v assembly 'bleu x3, x4, target_label' is: %d\n", x1);

    while (1) {
        ;
    }

    return 0;
}

