#include "type.h"
#include "string.h"
#include "printk.h"
#include "asm/csr.h"
#include "asm/timer.h"
#include "asm/irq.h"

// Function declarations
uint64_t read_sscratch(void);
void write_sscratch(uint64_t sscratch);

int main() {
	printk("sscratch value: 0x%llx\n", read_sscratch());
	write_sscratch(0xaabbccdd11223344);
	printk("sscratch value: 0x%llx\n", read_sscratch());

	while (1) {
		// Infinite loop to prevent program termination
	}

	return 0;
}

