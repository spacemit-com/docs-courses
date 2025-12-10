#include <stdint.h>      // For fixed-width integer types
#include "type.h"
#include "string.h"
#include "printk.h"
#include "asm/csr.h"
#include "asm/timer.h"
#include "asm/irq.h"

// RV32I Basic Integer Load and Store Instruction Declarations
int lh_example(volatile int *addr);
int lw_example(volatile int *addr);
unsigned int lbu_example(volatile int *addr);
unsigned int lhu_example(volatile int *addr);
void sb_example(int value, volatile int *addr);
void sh_example(int value, volatile int *addr);
void sw_example(int value, volatile int *addr);

// RV64I Basic Integer Load and Store Instruction Declarations (Pointers changed to uint8_t *)
int64_t ld64_example(uint8_t *addr);
//int32_t lw64_example(uint8_t *addr);
//uint32_t lwu_example(uint8_t *addr);
int16_t lh64_example(uint8_t *addr);
uint16_t lhu64_example(uint8_t *addr);
int8_t lb_example(uint8_t *addr);
uint8_t lbu64_example(uint8_t *addr);
void sd_example(int64_t value, uint8_t *addr);
void sw64_example(int32_t value, uint8_t *addr);
void sh64_example(int16_t value, uint8_t *addr);
void sb64_example(int8_t value, uint8_t *addr);

// Single-Precision Load and Store Instruction Declarations
float flw_example(float *addr);
void fsw_example(float value, float *addr);

// Double-Precision Load and Store Instruction Declarations
double fld_example(double *addr);
//void fsd_example(double value, double *addr);

int main() {
    // Declared as volatile to prevent compiler optimizations
    volatile int data32[10] = {0};
    volatile int64_t data64[10] = {0};
    volatile float float_data[10] = {0};
    volatile double double_data[10] = {0};

    // RV32I Tests
    data32[0] = 42;
    // Removed ld_example call as it no longer exists
    // printk("Result of risc-v assembly 'ld x1, 0(x2)': %d\n", ld_example(&data32[0]));

    printk("Result of risc-v assembly 'lh x1, 0(x2)': %d\n", lh_example(&data32[0]));
    printk("Result of risc-v assembly 'lw x1, 0(x2)': %d\n", lw_example(&data32[0]));
    printk("Result of risc-v assembly 'lbu x1, 0(x2)': %u\n", lbu_example(&data32[0]));
    printk("Result of risc-v assembly 'lhu x1, 0(x2)': %u\n", lhu_example(&data32[0]));

    sb_example(0xFF, &data32[1]);
    printk("Result of risc-v assembly 'sb x1, 0(x2)': %d\n", data32[1] & 0xFF);

    sh_example(0xFFFF, &data32[1]);
    printk("Result of risc-v assembly 'sh x1, 0(x2)': %d\n", data32[1] & 0xFFFF);

    sw_example(123456, &data32[1]);
    printk("Result of risc-v assembly 'sw x1, 0(x2)': %d\n", data32[1]);

    // RV64I Tests
    data64[0] = 12345678901234LL;
    printk("Result of risc-v assembly 'ld64 x1, 0(x2)': %lld\n", ld64_example((uint8_t *)&data64[0]));

    // 'lw64 x3, 4(x4)' corresponds to loading from address +4 bytes
//    uint8_t *addr_lw64 = (uint8_t *)((char *)&data64[0] + 4);
//    printk("Result of risc-v assembly 'lw64 x3, 4(x4)': %d\n", lw64_example(addr_lw64));

    // 'lwu x5, 8(x6)' corresponds to loading from address +8 bytes
//    uint8_t *addr_lwu = (uint8_t *)((char *)&data64[0] + 8);
//    printk("Result of risc-v assembly 'lwu x5, 8(x6)': %u\n", lwu_example(addr_lwu));

    // 'lh64 x7, 12(x8)' corresponds to loading from address +12 bytes
    uint8_t *addr_lh64 = (uint8_t *)((char *)&data64[0] + 12);
    printk("Result of risc-v assembly 'lh64 x7, 12(x8)': %d\n", lh64_example(addr_lh64));

    // 'lhu64 x9, 16(x10)' corresponds to loading from address +16 bytes
    uint8_t *addr_lhu64 = (uint8_t *)((char *)&data64[0] + 16);
    printk("Result of risc-v assembly 'lhu64 x9, 16(x10)': %u\n", lhu64_example(addr_lhu64));

    // 'lb x11, 20(x12)' corresponds to loading from address +20 bytes
    uint8_t *addr_lb = (uint8_t *)((char *)&data64[0] + 20);
    printk("Result of risc-v assembly 'lb x11, 20(x12)': %d\n", lb_example(addr_lb));

    // 'lbu64 x13, 24(x14)' corresponds to loading from address +24 bytes
    uint8_t *addr_lbu64 = (uint8_t *)((char *)&data64[0] + 24);
    printk("Result of risc-v assembly 'lbu64 x13, 24(x14)': %u\n", lbu64_example(addr_lbu64));

    // Store operations
    sd_example(9876543210LL, (uint8_t *)&data64[1]);
    printk("Result of risc-v assembly 'sd x1, 0(x2)': %lld\n", data64[1]);

    // 'sw64 x3, 4(x4)' corresponds to storing at address +4 bytes
    uint8_t *addr_sw64 = (uint8_t *)((char *)&data64[0] + 4);
    sw64_example(999999, addr_sw64);
    printk("Result of risc-v assembly 'sw64 x3, 4(x4)': %d\n", *(int32_t *)addr_sw64); // Casting to int32_t for correct display

    // 'sh64 x5, 8(x6)' corresponds to storing at address +8 bytes
    uint8_t *addr_sh64 = (uint8_t *)((char *)&data64[0] + 8);
    sh64_example(0x1234, addr_sh64);
    printk("Result of risc-v assembly 'sh64 x5, 8(x6)': %d\n", *(int16_t *)addr_sh64);

    // 'sb64 x7, 12(x8)' corresponds to storing at address +12 bytes
    uint8_t *addr_sb64 = (uint8_t *)((char *)&data64[0] + 12);
    sb64_example(0x12, addr_sb64);
    printk("Result of risc-v assembly 'sb64 x7, 12(x8)': %d\n", *(int8_t *)addr_sb64);

    // Single-Precision Load and Store Instructions
    float_data[0] = 3.14f;
    printk("Result of risc-v assembly 'flw f1, 0(x2)': %.2f\n", flw_example((float *)&float_data[0]));

    fsw_example(2.71f, (float *)&float_data[1]);
    printk("Result of risc-v assembly 'fsw f3, 4(x4)': %.2f\n", float_data[1]);

    // Double-Precision Load and Store Instructions
    double_data[0] = 3.14159265358979;
    printk("Result of risc-v assembly 'fld f2, 0(x3)': %.15lf\n", fld_example((double *)&double_data[0]));

//    fsd_example(2.718281828459, (double *)&double_data[1]);
//    printk("Result of risc-v assembly 'fsd f4, 0(x5)': %.15lf\n", double_data[1]);

    while (1) {
        ; // Infinite loop to prevent program from exiting
    }

    return 0;
}

