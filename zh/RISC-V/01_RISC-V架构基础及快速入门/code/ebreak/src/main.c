#include "asm/csr.h"
#include "asm/irq.h"
#include "asm/sbi.h"

extern void trap_init(void);

int main(void)
{
	trap_init();

	arch_local_irq_enable();

	asm volatile("ebreak");

	while (1) {}
	return 0;
}
