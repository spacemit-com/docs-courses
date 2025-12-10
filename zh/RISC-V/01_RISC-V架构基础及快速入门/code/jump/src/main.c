#include "type.h"
#include "string.h"
#include "printk.h"
#include "asm/csr.h"
#include "asm/timer.h"
#include "asm/irq.h"

// 跳转指令函数声明
int jal_example(void);
int jalr_example(void);

int main() {
    int x1;

    // 测试 JAL 指令
    x1 = jal_example();
    printk("Result of risc-v assembly 'jal x1, target_label' is: %d\n", x1);

    // 测试 JALR 指令
    x1 = jalr_example();
    printk("Result of risc-v assembly 'jalr x1, 0(x5)' is: %d\n", x1);
    
    while (1) {
        ;
    }
    return 0;
}

