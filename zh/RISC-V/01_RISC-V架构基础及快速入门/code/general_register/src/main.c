#include "type.h"
#include "string.h"
#include "printk.h"
#include "asm/csr.h"
#include "asm/timer.h"
#include "asm/irq.h"

// Function declarations
int example_function(int a0, int a1);

int main() {
    int a0 = 2, a1 = 3;
    a0 = example_function(a0, a1);
    printk("example_function result: %d\n", a0);

    while (1) {
        // Infinite loop to prevent program termination
    }

    return 0;
}

