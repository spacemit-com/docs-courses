#include "type.h"
#include "string.h"
#include "printk.h"
#include "asm/csr.h"
#include "asm/timer.h"
#include "asm/irq.h"

// Function declarations
int add(int x, int y);

float multiply(float x, float y);

int main() {
    int a0 = 2, a1 = 3;
    float fa0 = 2.6, fa1 = 3.2;
    a0 = add(a0, a1);
    fa0 = multiply(fa0, fa1);
    printk("add: %d\nmultiply: %.2f\n", a0, fa0);

    while (1) {
        // Infinite loop to prevent program termination
    }

    return 0;
}

