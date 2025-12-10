#include "type.h"
#include "string.h"
#include "printk.h"
#include "asm/csr.h"
#include "asm/timer.h"
#include "asm/irq.h"
#include "asm/sbi.h"

extern void trap_init(void);

int main(void)
{
	trap_init();

	timer_init();
	printk("sstatus:0x%lx\n", read_csr(sstatus));
	arch_local_irq_enable();
	printk("sstatus:0x%lx\n", read_csr(sstatus));
	sbi_ecall_demo();
	while (1) {
		;
	}
	return 0;
}
