#include "asm/csr.h"
#include "asm/irq.h"
#include "asm/sbi.h"
#include "printk.h"

extern void trap_init(void);

#define CSR_SCAUSE   0x142
#define __ASM_STR(x) #x

#define csr_read(csr)                                           \
({                                                              \
        register unsigned long __v;                             \
        __asm__ __volatile__ ("csrr %0, " __ASM_STR(csr)        \
                              : "=r" (__v) :                    \
                              : "memory");                      \
        __v;                                                    \
})

static inline void local_flush_icache_all(void)
{
        asm volatile ("fence.i" ::: "memory");
}

int main(void)
{
	trap_init();

	arch_local_irq_enable();

	unsigned long scause = csr_read(CSR_SCAUSE);

	printk("Inline ASM example: csr read scause 0x%lu\n", scause);

	printk("Inline ASM exmaple: flush icache\n");
	local_flush_icache_all();
	
	while (1) {}
	return 0;
}
