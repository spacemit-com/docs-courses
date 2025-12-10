	.file	"1.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	func
	.type	func, @function
func:
	fld	fa0,0(a0)
	ret
	.size	func, .-func
	.ident	"GCC: (g) 12.2.1 20230312"
	.section	.note.GNU-stack,"",@progbits
