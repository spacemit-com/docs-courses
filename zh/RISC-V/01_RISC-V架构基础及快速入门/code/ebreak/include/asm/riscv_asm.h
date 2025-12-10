#ifndef __RISCV_ASM_H__
#define __RISCV_ASM_H__

int pmp_set(unsigned int n, unsigned long prot, unsigned long addr,
	    unsigned long log2len);

#endif