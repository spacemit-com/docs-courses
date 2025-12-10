#include "type.h"
#include "string.h"
#include "printk.h"
#include "asm/csr.h"
#include "asm/timer.h"
#include "asm/irq.h"

int main(void)
{
	printk("Hello World!!!\n");

	while (1) {
		;
	}
	return 0;
}
