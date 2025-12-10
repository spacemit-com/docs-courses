.section ".text"

.globl read_sscratch
read_sscratch:
	csrr a0, sscratch
	ret

.globl write_sscratch
write_sscratch:
	csrw sscratch, a0
	ret
