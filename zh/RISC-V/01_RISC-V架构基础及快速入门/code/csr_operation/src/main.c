#include "type.h"
#include "printk.h"
#include "asm/csr.h"
//#include "asm/irq.h"

uint64_t read_sscratch(void);
void write_sscratch(uint64_t sscratch);

int main(void)
{
	printk("sscratch value: 0x%llx\n", read_sscratch());
	write_sscratch(0x1234567812345678);
	printk("sscratch value: 0x%llx\n", read_sscratch());

	while (1) {}
	return 0;
}
