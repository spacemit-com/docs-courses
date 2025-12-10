#include "type.h"
#include "string.h"
#include "printk.h"
#include "asm/csr.h"
#include "asm/timer.h"
#include "asm/irq.h"

// 示例：装入立即数
void li_example() {
    unsigned int rd;
    asm("li %0, 42;" : "=r" (rd));
    printk("li example: rd = %u\n", rd);
}
 
// 示例：复制寄存器
void mv_example() {
    unsigned int rs = 10, rd;
    asm("mv %0, %1;" : "=r" (rd) : "r" (rs));
    printk("mv example: rd = %u\n", rd);
}
 
// 示例：整数取反
void neg_example() {
    int rs = 5, rd; 
    asm("neg %0, %1;" : "=r" (rd) : "r" (rs));
    printk("neg example: rd = %d\n", rd); // 输出 -5
}

// 示例：单精度浮点绝对值
void fabs_s_simplified_example() {
    float rs = -3.14f, rd;
    if (rs < 0) {
        asm("fmv.s %0, %1;" : "=f" (rd) : "f" (-rs)); // 简单地将 -rs 赋值给 rd
    } else {
        asm("fmv.s %0, %1;" : "=f" (rd) : "f" (rs)); // 直接赋值
    }
    printk("fabs_s simplified example: rd = %f\n", rd);
}
int main() {
    li_example();
    mv_example();
    neg_example();
    //fabs_s_simplified_example();
    while (1) {
		;
	}
	return 0;
}
