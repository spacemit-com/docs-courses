.section ".text.boot"

.globl _start
_start:
    /* Disable interrupts */
    csrw sie, zero

    /* Set up stack, stack size 4KB */
    la sp, stacks_start
    li t0, 4096
    add sp, sp, t0

    /* Zero .bss section */
    lla t0, _bss
    lla t1, _ebss
bss_zero_loop:
    sd zero, (t0)
    add t0, t0, 8
    blt t0, t1, bss_zero_loop

    /* Initialize FPU by setting FCSR to zero */
    csrw fcsr, zero

    /* Jump to C main */
    tail main

.section ".data"
.align  12
.globl stacks_start
stacks_start:
    .skip 4096

