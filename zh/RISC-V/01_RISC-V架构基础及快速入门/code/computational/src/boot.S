.section ".text.boot"

.globl _start
_start:
	/* 关闭中断 */
	csrw sie, zero

	/* 设置栈, 栈的大小为4KB */
	la sp, stacks_start
	li t0, 4096
	add sp, sp, t0

	lla t0, _bss
	lla t1, _ebss
_bss_zero:
	sd zero, (t0)
	add t0, t0, 8
	blt t0, t1, _bss_zero

	/* 跳转到C语言 */
	tail main


.section .data
.align  12
.global stacks_start
stacks_start:
	.skip 4096

