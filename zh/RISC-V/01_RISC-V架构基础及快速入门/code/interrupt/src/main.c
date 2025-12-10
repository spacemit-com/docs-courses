#include "type.h"
#include "string.h"
#include "printk.h"
#include "asm/csr.h"
#include "asm/timer.h"
#include "asm/irq.h"
#include "asm/plic.h"
#include "uart.h"

void trap_init(void);

int main(void)
{
	trap_init();

	timer_init();
	plic_init();
	enable_uart_plic();
	printk("sstatus:0x%lx\n", read_csr(sstatus));
	arch_local_irq_enable();
	printk("sstatus:0x%lx sie:0x%lx\n", read_csr(sstatus), read_csr(sie));

	while (1) {
		;
	}
	return 0;
}
