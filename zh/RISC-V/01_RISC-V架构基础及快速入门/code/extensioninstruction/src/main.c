#include "type.h"
#include "string.h"
#include "printk.h"
#include "asm/csr.h"
#include "asm/timer.h"
#include "asm/irq.h"

// RV32I 乘法指令函数实现
int mul_example(int x, int y) {
    int result;
    asm("mul %1, %2, %0" : "=r" (result) : "r" (x), "r" (y));
    return result;
}
 
int mulh_example(int x, int y) {
    int result;
    asm("mulh %1, %2, %0" : "=r" (result) : "r" (x), "r" (y));
    return result;
}
 
int mulhsu_example(unsigned int x, unsigned int y) {
    unsigned int result;
    asm("mulhsu %1, %2, %0" : "=r" (result) : "r" (x), "r" (y));
    return result;
}
 
int mulw_example(int x, int y) {
    int result;
    asm("mulw %1, %2, %0" : "=r" (result) : "r" (x), "r" (y));
    return result;
}
 
// RV32I 除法指令函数实现
int div_example(int x, int y) {
    int result;
    asm("div %1, %2, %0" : "=r" (result) : "r" (x), "r" (y));
    return result;
}
 
int divu_example(unsigned int x, unsigned int y) {
    unsigned int result;
    asm("divu %1, %2, %0" : "=r" (result) : "r" (x), "r" (y));
    return result;
}
 
int rem_example(int x, int y) {
    int result;
    // REM 指令同样需要处理除零和溢出
    asm("rem %1, %2, %0" : "=r" (result) : "r" (x), "r" (y));
    return result;
}
 
int remu_example(unsigned int x, unsigned int y) {
    unsigned int result;
    // REMU 指令同样需要处理除零
    asm("remu %1, %2, %0" : "=r" (result) : "r" (x), "r" (y));
    return result;
}

int lr_example(int *address) {
    int result;
    asm volatile (
        "lr.w %0, (%1)"
        : "=r" (result)
        : "r" (address)
        : "memory"
    );
    return result;
}
 
int sc_example(int *address, int value) {
    int success;
    asm volatile (
        "sc.w %0, %2, (%1)"
        : "=r" (success)
        : "r" (address), "r" (value)
        : "memory"
    );
    return success;
}
 
int amoswap_example(int *address, int value) {
    int result;
    asm volatile (
        "amoswap.w %0, %2, (%1)"
        : "=r" (result)
        : "r" (address), "r" (value)
        : "memory"
    );
    return result;
}
 
int amoadd_example(int *address, int value) {
    int old_value;
    asm volatile (
        "amoadd.w %0, %2, (%1)"
        : "=r" (old_value)
        : "r" (address), "r" (value)
        : "memory"
    );
    return old_value;
}
 
// 单精度浮点算术运算指令函数实现
float fadd_s_example(float x, float y) {
    float result;
    asm volatile (
        "fadd.s %0, %1, %2"
        : "=f" (result)
        : "f" (x), "f" (y)
    );
    return result;
}
 
float fsub_s_example(float x, float y) {
    float result;
    asm volatile (
        "fsub.s %0, %1, %2"
        : "=f" (result)
        : "f" (x), "f" (y)
    );
    return result;
}
 
float fmul_s_example(float x, float y) {
    float result;
    asm volatile (
        "fmul.s %0, %1, %2"
        : "=f" (result)
        : "f" (x), "f" (y)
    );
    return result;
}
 
float fdiv_s_example(float x, float y) {
    float result;
    asm volatile (
        "fdiv.s %0, %1, %2"
        : "=f" (result)
        : "f" (x), "f" (y)
    );
    return result;
}
 
// 双精度浮点算术运算指令函数实现
double fadd_d_example(double x, double y) {
    double result;
    asm volatile (
        "fadd.d %0, %1, %2"
        : "=f" (result)
        : "f" (x), "f" (y)
    );
    return result;
}
 
double fsub_d_example(double x, double y) {
    double result;
    asm volatile (
        "fsub.d %0, %1, %2"
        : "=f" (result)
        : "f" (x), "f" (y)
    );
    return result;
}
 
double fmul_d_example(double x, double y) {
    double result;
    asm volatile (
        "fmul.d %0, %1, %2"
        : "=f" (result)
        : "f" (x), "f" (y)
    );
    return result;
}
 
double fdiv_d_example(double x, double y) {
    double result;
    asm volatile (
        "fdiv.d %0, %1, %2"
        : "=f" (result)
        : "f" (x), "f" (y)
    );
    return result;
}

int main() {
    // RV32I 乘法指令测试
    int x1 = 5, x2 = 3;
    int result;

    result = mul_example(x1, x2);
    printk("Result of risc-v assembly 'mul x1, x2, x3' is: %d\n", result);
    x1 = 0xFFFFFFFF;
    x2 = 0x0000000000000002;
    result = mulh_example(x1, x2);
    printk("Result of risc-v assembly 'mulh x1, x2, x3' is: %d\n", result);

    result = mulhsu_example(x1, x2);
    printk("Result of risc-v assembly 'mulhsu x1, x2, x3' is: %u\n", result);
    x1 = 50;
    x2 = 2333;
    result = mulw_example(x1, x2);
    printk("Result of risc-v assembly 'mulw x1, x2, x3' is: %d\n", result);

    x1 = 100;
    x2 = 0xFFFF;
    // RV32I 除法指令测试
    result = div_example(x1, x2);
    printk("Result of risc-v assembly 'div x1, x2, x3' is: %d\n", result);

    result = divu_example(x1, x2);
    printk("Result of risc-v assembly 'divu x1, x2, x3' is: %u\n", result);

    result = rem_example(x1, x2);
    printk("Result of risc-v assembly 'rem x1, x2, x3' is: %d\n", result);

    result = remu_example(x1, x2);
    printk("Result of risc-v assembly 'remu x1, x2, x3' is: %u\n", result);

    // 原子操作测试
    int shared_var = 0;
    result = lr_example(&shared_var);
    printk("Result of LR operation: %d\n", result);

    result = sc_example(&shared_var, 42);
    printk("Result of SC operation: %d (new value: %d)\n", result, shared_var);

    result = amoswap_example(&shared_var, 100);
    printk("Result of AMOSWAP operation: %d (new value: %d)\n", result, shared_var);

    result = amoadd_example(&shared_var, 10);
    printk("Result of AMOADD operation: %d (new value: %d)\n", result, shared_var);

    // 单精度浮点算术运算指令测试
    float f1 = 3.5f, f2 = 1.2f;
    float fresult;

    fresult = fadd_s_example(f1, f2);
    printk("Result of risc-v assembly 'fadd.s x1, x2, x3' is: %.2f\n", fresult);

    fresult = fsub_s_example(f1, f2);
    printk("Result of risc-v assembly 'fsub.s x1, x2, x3' is: %.2f\n", fresult);

    fresult = fmul_s_example(f1, f2);
    printk("Result of risc-v assembly 'fmul.s x1, x2, x3' is: %.2f\n", fresult);

    fresult = fdiv_s_example(f1, f2);
    printk("Result of risc-v assembly 'fdiv.s x1, x2, x3' is: %.2f\n", fresult);

    // 双精度浮点算术运算指令测试
    double d1 = 3.5, d2 = 1.2, dresult;

    dresult = fadd_d_example(d1, d2);
    printk("Result of risc-v assembly 'fadd.d x1, x2, x3' is: %.2lf\n", dresult);

    dresult = fsub_d_example(d1, d2);
    printk("Result of risc-v assembly 'fsub.d x1, x2, x3' is: %.2lf\n", dresult);

    dresult = fmul_d_example(d1, d2);
    printk("Result of risc-v assembly 'fmul.d x1, x2, x3' is: %.2lf\n", dresult);

    dresult = fdiv_d_example(d1, d2);
    printk("Result of risc-v assembly 'fdiv.d x1, x2, x3' is: %.2lf\n", dresult);

    while (1) {
        ;
    }

    return 0;
}