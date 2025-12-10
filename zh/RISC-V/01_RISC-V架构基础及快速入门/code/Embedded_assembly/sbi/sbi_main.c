#include "asm/csr.h"
#include "asm/sbi.h"
#include "uart.h"
#include "sbi_trap.h"
#include "printk.h"

#define FW_JUMP_ADDR 0x80200000

#define BANNER \
	"   _____ ____ _____\n"     \
	"   / ____|  _ \\_   _|\n"  \
	" | (___ | |_) || |\n"      \
	"  \\ \\___ \\|  _ < | |\n" \
	"  ____) | |_) || |_\n"     \
	" |_|_____/|____/_____|\n"  \
	" "


/*
 * 运行在M模式
 */
void sbi_main(void)
{
	unsigned long val;

	uart_init();

	printk(BANNER);

	sbi_trap_init();

	/* 设置跳转模式为S模式 */
	val = read_csr(mstatus);
	val = INSERT_FIELD(val, MSTATUS_MPP, PRV_S);
	val = INSERT_FIELD(val, MSTATUS_MPIE, 0);
	write_csr(mstatus, val);

	delegate_traps();

	pmp_set(0, 7, 0, 0x40);

	/* 设置M模式的Exception Program Counter，用于mret跳转 */
	write_csr(mepc, FW_JUMP_ADDR);
	/* 设置S模式异常向量表入口*/
	write_csr(stvec, FW_JUMP_ADDR);
	/* 关闭S模式的中断*/
	write_csr(sie, 0);
	/* 关闭S模式的页表转换 */
	write_csr(satp, 0);

	/* 切换到S模式 */
	asm volatile("mret");
}
