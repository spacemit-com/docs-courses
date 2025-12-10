#include "type.h"
#include "string.h"
#include "printk.h"
#include "asm/csr.h"
#include "asm/timer.h"
#include "asm/irq.h"

// Function declarations for RV32I instructions
int addi_example(int x);
int slti_example(int x);
int sltiu_example(unsigned int x);
int andi_example(int x);
int ori_example(int x);
int xori_example(int x);
int slli_example(int x);
int srli_example(int x);
int srai_example(int x);
int lui_example(void);
int auipc_example(void);
int add_example(int x, int y);
int sub_example(int x, int y);
int slt_example(int x, int y);
int sltu_example(unsigned int x, unsigned int y);
int and_example(int x, int y);
int or_example(int x, int y);
int xor_example(int x, int y);
void nop_example(void);

// Function declarations for RV64I instructions
int addiw_example(int x);
int slliw_example(int x);
int srliw_example(int x);
int sraiw_example(int x);
int addw_example(int x, int y);
int subw_example(int x, int y);
int sll_example(int x, int y);
int srl_example(int x, int y);
int sra_example(int x, int y);
int sllw_example(int x, int y);
int srlw_example(int x, int y);
int sraw_example(int x, int y);

// Function declarations for single-precision floating-point instructions
float fadd_s_example(float x, float y);
float fsub_s_example(float x, float y);
float fmul_s_example(float x, float y);
float fdiv_s_example(float x, float y);
float fsqrt_s_example(float x);
float fmin_s_example(float x, float y);
float fmax_s_example(float x, float y);
float fmadd_s_example(float x, float y, float z);
float fmsub_s_example(float x, float y, float z);
float fnmsub_s_example(float x, float y, float z);
float fnmadd_s_example(float x, float y, float z);

// Function declarations for double-precision floating-point instructions
double fadd_d_example(double x, double y);
double fsub_d_example(double x, double y);
double fmul_d_example(double x, double y);
double fdiv_d_example(double x, double y);
double fsqrt_d_example(double x);
double fmin_d_example(double x, double y);
double fmax_d_example(double x, double y);
double fmadd_d_example(double x, double y, double z);
double fmsub_d_example(double x, double y, double z);
double fnmsub_d_example(double x, double y, double z);
double fnmadd_d_example(double x, double y, double z);

int main() {
    // RV32I instruction tests
    int x1, x2 = 5, x3 = 3;
    x1 = addi_example(x2);
    printk("Result of RV32I addi: %d\n", x1);

    x1 = slti_example(x2);
    printk("Result of RV32I slti: %d\n", x1);

    x1 = sltiu_example(x2);
    printk("Result of RV32I sltiu: %d\n", x1);

    x1 = andi_example(x2);
    printk("Result of RV32I andi: %d\n", x1);

    x1 = ori_example(x2);
    printk("Result of RV32I ori: %d\n", x1);

    x1 = xori_example(x2);
    printk("Result of RV32I xori: %d\n", x1);

    x1 = slli_example(x2);
    printk("Result of RV32I slli: %d\n", x1);

    x1 = srli_example(x2);
    printk("Result of RV32I srli: %d\n", x1);

    x1 = srai_example(x2);
    printk("Result of RV32I srai: %d\n", x1);

    x1 = lui_example();
    printk("Result of RV32I lui: %d\n", x1);

    x1 = auipc_example();
    printk("Result of RV32I auipc: %d\n", x1);

    x1 = add_example(x2, x3);
    printk("Result of RV32I add: %d\n", x1);

    x1 = sub_example(x2, x3);
    printk("Result of RV32I sub: %d\n", x1);

    x1 = slt_example(x2, x3);
    printk("Result of RV32I slt: %d\n", x1);

    x1 = sltu_example(x2, x3);
    printk("Result of RV32I sltu: %d\n", x1);

    x1 = and_example(x2, x3);
    printk("Result of RV32I and: %d\n", x1);

    x1 = or_example(x2, x3);
    printk("Result of RV32I or: %d\n", x1);

    x1 = xor_example(x2, x3);
    printk("Result of RV32I xor: %d\n", x1);

    nop_example();
    printk("RV32I nop executed successfully\n");

    // RV64I instruction tests
    x1 = addiw_example(x2);
    printk("Result of RV64I addiw: %d\n", x1);

    x1 = slliw_example(x2);
    printk("Result of RV64I slliw: %d\n", x1);

    x1 = srliw_example(x2);
    printk("Result of RV64I srliw: %d\n", x1);

    x1 = sraiw_example(x2);
    printk("Result of RV64I sraiw: %d\n", x1);

    x1 = addw_example(x2, x3);
    printk("Result of RV64I addw: %d\n", x1);

    x1 = subw_example(x2, x3);
    printk("Result of RV64I subw: %d\n", x1);

    x1 = sll_example(x2, x3);
    printk("Result of RV64I sll: %d\n", x1);

    x1 = srl_example(x2, x3);
    printk("Result of RV64I srl: %d\n", x1);

    x1 = sra_example(x2, x3);
    printk("Result of RV64I sra: %d\n", x1);

    x1 = sllw_example(x2, x3);
    printk("Result of RV64I sllw: %d\n", x1);

    x1 = srlw_example(x2, x3);
    printk("Result of RV64I srlw: %d\n", x1);

    x1 = sraw_example(x2, x3);
    printk("Result of RV64I sraw: %d\n", x1);

    // Single-precision floating-point instruction tests
    float f1 = 3.5f, f2 = 1.2f, f3;
    f3 = fadd_s_example(f1, f2);
    printk("Result of single-precision fadd.s: %.2f\n", f3);

    f3 = fsub_s_example(f1, f2);
    printk("Result of single-precision fsub.s: %.2f\n", f3);

    f3 = fmul_s_example(f1, f2);
    printk("Result of single-precision fmul.s: %.2f\n", f3);

    f3 = fdiv_s_example(f1, f2);
    printk("Result of single-precision fdiv.s: %.2f\n", f3);

    f3 = fsqrt_s_example(f1);
    printk("Result of single-precision fsqrt.s: %.2f\n", f3);

    f3 = fmin_s_example(f1, f2);
    printk("Result of single-precision fmin.s: %.2f\n", f3);

    f3 = fmax_s_example(f1, f2);
    printk("Result of single-precision fmax.s: %.2f\n", f3);

    f3 = fmadd_s_example(f1, f2, 1.0f);
    printk("Result of single-precision fmadd.s: %.2f\n", f3);

    f3 = fmsub_s_example(f1, f2, 1.0f);
    printk("Result of single-precision fmsub.s: %.2f\n", f3);

    f3 = fnmsub_s_example(f1, f2, 1.0f);
    printk("Result of single-precision fnmsub.s: %.2f\n", f3);

    f3 = fnmadd_s_example(f1, f2, 1.0f);
    printk("Result of single-precision fnmadd.s: %.2f\n", f3);

    // Double-precision floating-point instruction tests
    double d1 = 3.5, d2 = 1.2, d3;
    d3 = fadd_d_example(d1, d2);
    printk("Result of double-precision fadd.d: %.2lf\n", d3);

    d3 = fsub_d_example(d1, d2);
    printk("Result of double-precision fsub.d: %.2lf\n", d3);

    d3 = fmul_d_example(d1, d2);
    printk("Result of double-precision fmul.d: %.2lf\n", d3);

    d3 = fdiv_d_example(d1, d2);
    printk("Result of double-precision fdiv.d: %.2lf\n", d3);

    d3 = fsqrt_d_example(d1);
    printk("Result of double-precision fsqrt.d: %.2lf\n", d3);

    d3 = fmin_d_example(d1, d2);
    printk("Result of double-precision fmin.d: %.2lf\n", d3);

    d3 = fmax_d_example(d1, d2);
    printk("Result of double-precision fmax.d: %.2lf\n", d3);

    d3 = fmadd_d_example(d1, d2, 1.0);
    printk("Result of double-precision fmadd.d: %.2lf\n", d3);

    d3 = fmsub_d_example(d1, d2, 1.0);
    printk("Result of double-precision fmsub.d: %.2lf\n", d3);

    d3 = fnmsub_d_example(d1, d2, 1.0);
    printk("Result of double-precision fnmsub.d: %.2lf\n", d3);

    d3 = fnmadd_d_example(d1, d2, 1.0);
    printk("Result of double-precision fnmadd.d: %.2lf\n", d3);

    while (1) {
        // Infinite loop to prevent program termination
    }

    return 0;
}

