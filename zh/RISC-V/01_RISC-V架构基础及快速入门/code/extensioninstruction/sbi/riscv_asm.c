#include "asm/csr.h"
#include "asm/sbi.h"
#include "sbi_trap.h"

#define PMP_SHIFT			2
#define PMP_COUNT			64

#define PMP_R				(0x01)
#define PMP_W				(0x02)
#define PMP_X				(0x04)
#define PMP_A				(0x18)
#define PMP_A_TOR			(0x08)
#define PMP_A_NA4			(0x10)
#define PMP_A_NAPOT			(0x18)
#define PMP_L				(0x80)

unsigned long csr_read_num(int csr_num)
{
#define switchcase_csr_read(__csr_num, __val)		\
	case __csr_num:					\
		__val = read_csr(__csr_num);		\
		break;
#define switchcase_csr_read_2(__csr_num, __val)	\
	switchcase_csr_read(__csr_num + 0, __val)	\
	switchcase_csr_read(__csr_num + 1, __val)
#define switchcase_csr_read_4(__csr_num, __val)	\
	switchcase_csr_read_2(__csr_num + 0, __val)	\
	switchcase_csr_read_2(__csr_num + 2, __val)
#define switchcase_csr_read_8(__csr_num, __val)	\
	switchcase_csr_read_4(__csr_num + 0, __val)	\
	switchcase_csr_read_4(__csr_num + 4, __val)
#define switchcase_csr_read_16(__csr_num, __val)	\
	switchcase_csr_read_8(__csr_num + 0, __val)	\
	switchcase_csr_read_8(__csr_num + 8, __val)
#define switchcase_csr_read_32(__csr_num, __val)	\
	switchcase_csr_read_16(__csr_num + 0, __val)	\
	switchcase_csr_read_16(__csr_num + 16, __val)
#define switchcase_csr_read_64(__csr_num, __val)	\
	switchcase_csr_read_32(__csr_num + 0, __val)	\
	switchcase_csr_read_32(__csr_num + 32, __val)

	unsigned long ret = 0;

	switch (csr_num) {
	switchcase_csr_read_16(CSR_PMPCFG0, ret)
	switchcase_csr_read_64(CSR_PMPADDR0, ret)
	// switchcase_csr_read(CSR_MCYCLE, ret)
	// switchcase_csr_read(CSR_MINSTRET, ret)
	// switchcase_csr_read(CSR_MHPMCOUNTER3, ret)
	// switchcase_csr_read_4(CSR_MHPMCOUNTER4, ret)
	// switchcase_csr_read_8(CSR_MHPMCOUNTER8, ret)
	// switchcase_csr_read_16(CSR_MHPMCOUNTER16, ret)
	// switchcase_csr_read(CSR_MCOUNTINHIBIT, ret)
	// switchcase_csr_read(CSR_MHPMEVENT3, ret)
	// switchcase_csr_read_4(CSR_MHPMEVENT4, ret)
	// switchcase_csr_read_8(CSR_MHPMEVENT8, ret)
	// switchcase_csr_read_16(CSR_MHPMEVENT16, ret)
#if __riscv_xlen == 32
	switchcase_csr_read(CSR_MCYCLEH, ret)
	switchcase_csr_read(CSR_MINSTRETH, ret)
	switchcase_csr_read(CSR_MHPMCOUNTER3H, ret)
	switchcase_csr_read_4(CSR_MHPMCOUNTER4H, ret)
	switchcase_csr_read_8(CSR_MHPMCOUNTER8H, ret)
	switchcase_csr_read_16(CSR_MHPMCOUNTER16H, ret)
	/**
	 * The CSR range MHPMEVENT[3-16]H are available only if sscofpmf
	 * extension is present. The caller must ensure that.
	 */
	switchcase_csr_read(CSR_MHPMEVENT3H, ret)
	switchcase_csr_read_4(CSR_MHPMEVENT4H, ret)
	switchcase_csr_read_8(CSR_MHPMEVENT8H, ret)
	switchcase_csr_read_16(CSR_MHPMEVENT16H, ret)
#endif

	default:
		sbi_panic();
		break;
	};

	return ret;

#undef switchcase_csr_read_64
#undef switchcase_csr_read_32
#undef switchcase_csr_read_16
#undef switchcase_csr_read_8
#undef switchcase_csr_read_4
#undef switchcase_csr_read_2
#undef switchcase_csr_read
}

void csr_write_num(int csr_num, unsigned long val)
{
#define switchcase_csr_write(__csr_num, __val)		\
	case __csr_num:					\
		write_csr(__csr_num, __val);		\
		break;
#define switchcase_csr_write_2(__csr_num, __val)	\
	switchcase_csr_write(__csr_num + 0, __val)	\
	switchcase_csr_write(__csr_num + 1, __val)
#define switchcase_csr_write_4(__csr_num, __val)	\
	switchcase_csr_write_2(__csr_num + 0, __val)	\
	switchcase_csr_write_2(__csr_num + 2, __val)
#define switchcase_csr_write_8(__csr_num, __val)	\
	switchcase_csr_write_4(__csr_num + 0, __val)	\
	switchcase_csr_write_4(__csr_num + 4, __val)
#define switchcase_csr_write_16(__csr_num, __val)	\
	switchcase_csr_write_8(__csr_num + 0, __val)	\
	switchcase_csr_write_8(__csr_num + 8, __val)
#define switchcase_csr_write_32(__csr_num, __val)	\
	switchcase_csr_write_16(__csr_num + 0, __val)	\
	switchcase_csr_write_16(__csr_num + 16, __val)
#define switchcase_csr_write_64(__csr_num, __val)	\
	switchcase_csr_write_32(__csr_num + 0, __val)	\
	switchcase_csr_write_32(__csr_num + 32, __val)

	switch (csr_num) {
	switchcase_csr_write_16(CSR_PMPCFG0, val)
	switchcase_csr_write_64(CSR_PMPADDR0, val)
	// switchcase_csr_write(CSR_MCYCLE, val)
	// switchcase_csr_write(CSR_MINSTRET, val)
	// switchcase_csr_write(CSR_MHPMCOUNTER3, val)
	// switchcase_csr_write_4(CSR_MHPMCOUNTER4, val)
	// switchcase_csr_write_8(CSR_MHPMCOUNTER8, val)
	// switchcase_csr_write_16(CSR_MHPMCOUNTER16, val)
#if __riscv_xlen == 32
	switchcase_csr_write(CSR_MCYCLEH, val)
	switchcase_csr_write(CSR_MINSTRETH, val)
	switchcase_csr_write(CSR_MHPMCOUNTER3H, val)
	switchcase_csr_write_4(CSR_MHPMCOUNTER4H, val)
	switchcase_csr_write_8(CSR_MHPMCOUNTER8H, val)
	switchcase_csr_write_16(CSR_MHPMCOUNTER16H, val)
	switchcase_csr_write(CSR_MHPMEVENT3H, val)
	switchcase_csr_write_4(CSR_MHPMEVENT4H, val)
	switchcase_csr_write_8(CSR_MHPMEVENT8H, val)
	switchcase_csr_write_16(CSR_MHPMEVENT16H, val)
#endif
	// switchcase_csr_write(CSR_MCOUNTINHIBIT, val)
	// switchcase_csr_write(CSR_MHPMEVENT3, val)
	// switchcase_csr_write_4(CSR_MHPMEVENT4, val)
	// switchcase_csr_write_8(CSR_MHPMEVENT8, val)
	// switchcase_csr_write_16(CSR_MHPMEVENT16, val)

	default:
		sbi_panic();
		break;
	};

#undef switchcase_csr_write_64
#undef switchcase_csr_write_32
#undef switchcase_csr_write_16
#undef switchcase_csr_write_8
#undef switchcase_csr_write_4
#undef switchcase_csr_write_2
#undef switchcase_csr_write
}
int pmp_set(unsigned int n, unsigned long prot, unsigned long addr,
	    unsigned long log2len)
{
	int pmpcfg_csr, pmpcfg_shift, pmpaddr_csr;
	unsigned long cfgmask, pmpcfg;
	unsigned long addrmask, pmpaddr;

	/* check parameters */
	if (n >= PMP_COUNT || log2len > __riscv_xlen || log2len < PMP_SHIFT)
		return -1;

	/* calculate PMP register and offset */
#if __riscv_xlen == 32
	pmpcfg_csr   = CSR_PMPCFG0 + (n >> 2);
	pmpcfg_shift = (n & 3) << 3;
#elif __riscv_xlen == 64
	pmpcfg_csr   = (CSR_PMPCFG0 + (n >> 2)) & ~1;
	pmpcfg_shift = (n & 7) << 3;
#else
# error "Unexpected __riscv_xlen"
#endif
	pmpaddr_csr = CSR_PMPADDR0 + n;

	/* encode PMP config */
	prot &= ~PMP_A;
	prot |= (log2len == PMP_SHIFT) ? PMP_A_NA4 : PMP_A_NAPOT;
	cfgmask = ~(0xffUL << pmpcfg_shift);
	pmpcfg	= (csr_read_num(pmpcfg_csr) & cfgmask);
	pmpcfg |= ((prot << pmpcfg_shift) & ~cfgmask);

	/* encode PMP address */
	if (log2len == PMP_SHIFT) {
		pmpaddr = (addr >> PMP_SHIFT);
	} else {
		if (log2len == __riscv_xlen) {
			pmpaddr = -1UL;
		} else {
			addrmask = (1UL << (log2len - PMP_SHIFT)) - 1;
			pmpaddr	 = ((addr >> PMP_SHIFT) & ~addrmask);
			pmpaddr |= (addrmask >> 1);
		}
	}

	/* write csrs */
	csr_write_num(pmpaddr_csr, pmpaddr);
	csr_write_num(pmpcfg_csr, pmpcfg);

	return 0;
}
