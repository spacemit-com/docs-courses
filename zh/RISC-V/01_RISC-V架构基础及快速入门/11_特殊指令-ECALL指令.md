sidebar_position: 11

# 1. **ecall**
## 1.1 **功能**
ecall指令在RISC-V架构中被定义为环境调用指令，主要用于向系统发起一次系统调用。它类似于一个“呼唤”或“请求”，让操作系统执行一些特定的任务，如文件操作、网络通信等。当程序需要执行这些任务时，就会触发ecall指令，然后操作系统会根据指令的参数来执行相应的操作。其中，ecall用于标识具体的异常或系统调用类型，而ecall参数则用于传递额外的信息或数据。
## 1.2 **工作机制**
1. **触发异常**：ecall指令实际上被RISC-V定义为一种异常指令。当处理器执行到ecall指令时，会触发一个异常，导致处理器跳转到异常处理函数去执行。
2. **读取寄存器**：系统读取mcause寄存器（这个寄存器用于记录进入异常的原因），发现是ecall指令后，会进一步读取a7寄存器的值来确定系统调用的类型。
3. **执行系统调用**：操作系统根据a7寄存器的值，以及可能的其他参数（通过a0-a6寄存器传递），来执行对应的系统调用。
4. **返回继续执行**：系统调用执行完毕后，处理器会返回到原来的程序继续执行。  
RISC-V 定义了以下实际处理ecall的调用机制:

<div align=center>
<img src=./images/ecall/ecall.png>
</div>

# 2. **ecall的应用场景**
ecall指令在RISC-V架构中广泛应用于系统调用和异常处理。例如，在用户态下执行的应用程序可以通过ecall指令请求操作系统执行文件操作、网络通信等任务。操作系统内核则可以通过ecall指令触发进程管理、内存管理等系统调用。

RISC-V定义了三种特权等级：

用户态（User Mode）：这是权限最低的模式，通常用于运行用户级别的应用程序。在此模式下，程序无法直接访问硬件资源，也无法执行特权指令。所有对硬件资源的访问和特权操作都需要通过系统调用（system call）来实现，即用户程序通过系统调用接口请求操作系统内核代为执行。

超级用户态（Supervisor Mode）：这是介于用户态和机器态之间的模式，通常用于运行操作系统内核。在此模式下，程序可以访问部分硬件资源，并执行一些特权指令。但是，相比于机器态，超级用户态的权限仍然受到一定的限制。操作系统内核在超级用户态下运行，负责管理内存、进程、设备等资源，以及处理用户程序的请求。

机器态（Machine Mode）：这是权限最高的模式，也称为物理模式或特权模式。在此模式下，程序可以访问所有硬件资源，并执行所有特权指令。机器态通常用于运行处理器的固件（如BIOS或UEFI）以及低级别的系统引导程序。当处理器加电或复位时，它会首先进入机器态，并从预设的内存地址开始执行指令。
## 2.1 **Linux系统调用**
ecall指令通过触发异常、跳转到异常处理函数、保存上下文信息、修改状态寄存器、执行系统调用服务和恢复上下文信息等步骤，实现了从用户态到超级用户态的切换。这种机制使得用户程序能够请求操作系统内核的服务，并执行一些需要特权级别的操作。
## 2.2 **SBI系统的调用**
ecall指令通过触发异常、保存上下文信息、修改状态寄存器、执行核心操作和恢复上下文信息等步骤，实现了从超级用户态（S态）到机器态（M态）的切换。这种机制为操作系统和特权软件提供了一种安全、可靠的方式来执行核心级的操作。
# 3. sbi_ecall函数源码

````
struct sbiret __sbi_ecall(unsigned long arg0, unsigned long arg1,
                          unsigned long arg2, unsigned long arg3,
                          unsigned long arg4, unsigned long arg5,
                          int fid, int ext)
{
        struct sbiret ret;

        trace_sbi_call(ext, fid);

        register uintptr_t a0 asm ("a0") = (uintptr_t)(arg0);
        register uintptr_t a1 asm ("a1") = (uintptr_t)(arg1);
        register uintptr_t a2 asm ("a2") = (uintptr_t)(arg2);
        register uintptr_t a3 asm ("a3") = (uintptr_t)(arg3);
        register uintptr_t a4 asm ("a4") = (uintptr_t)(arg4);
        register uintptr_t a5 asm ("a5") = (uintptr_t)(arg5);
        register uintptr_t a6 asm ("a6") = (uintptr_t)(fid);
        register uintptr_t a7 asm ("a7") = (uintptr_t)(ext);
        asm volatile ("ecall"
        an'guan'tia              : "+r" (a0), "+r" (a1)
                      : "r" (a2), "r" (a3), "r" (a4), "r" (a5), "r" (a6), "r" (a7)
                      : "memory");
        ret.error = a0;
        ret.value = a1;

        trace_sbi_return(ext, ret.error, ret.value);

        return ret;
}
````
````
	函数代码摘抄自内核源码：arch/riscv/kernel/sbi_ecall.c
```` 
# 4. **示例**

```
#include "printk.h"      //包含printk函数的声明，用于在内核或裸机环境中打印信息。
#include "asm/csr.h"     //包含CSR（控制状态寄存器）相关操作的声明。
#include "asm/irq.h"	 //包含中断请求（IRQ）相关操作的声明。
#include "asm/sbi.h"	 //包含SBI环境调用相关操作的声明。

int main(void)
{

	printk("sstatus:0x%lx\n", read_csr(sstatus));
    arch_local_irq_enable();  //启用本地中断。这允许处理器接收和处理中断。
	printk("sstatus:0x%lx\n", read_csr(sstatus));
	sbi_ecall_demo();    //一个演示如何使用SBI环境调用的函数。SBI是RISC-V架构中用于在机器模式和监督器模式之间通信的一种机制。
	while (1) {
	}
	return 0;
}

```
- 使用printk打印sstatus寄存器的值。sstatus是一个系统控制状态寄存器，包含了许多关于处理器当前状态的信息，如中断启用状态。read_csr(sstatus)是一个宏或函数，用于读取sstatus寄存器的值。
## 4.1 **进入示例**
[下载实验代码-ecall](code/ecall)

下载解压并进入示例目录

## 4.2 **编译**
````
make
````
## 4.3 **运行**
````
make run
````
**运行后LOG如下**

````
qemu-system-riscv64 -nographic -machine virt -m 128M  -bios m_mode.bin  -device loader,file=s_mode.bin,addr=0x80200000  -kernel s_mode.elf
   _____ ____ _____
   / ____|  _ \_   _|
 | (___ | |_) || |
  \ \___ \|  _ < | |
  ____) | |_) || |_
 |_|_____/|____/_____|
 stvec=0x80200974, 0x80200974
sstatus:0x200000000
sstatus:0x200000002
sbi_ecall_handle get ecall demo
````
详见请参考文档：实验环境搭建。
