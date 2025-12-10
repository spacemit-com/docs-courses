# 1. **ebreak工作原理**
## 1.1 **触发异常**
   当处理器执行到ebreak指令时，会触发一个BREAKPOINT异常。这个异常会导致处理器停止当前的程序执行流，并跳转到异常处理程序进行处理。
## 1.2 **调试模式**
   如果处理器配置了调试模式，并且ebreak指令被用于触发调试，那么处理器会进入调试模式。在调试模式下，调试器可以访问处理器的内部状态，如寄存器值、存储器内容等，从而进行详细的调试操作。
## 1.3 **功能**
   ebreak指令是RISC-V标准指令集中定义的一条特殊断点指令。当处理器运行到这条指令时，会自动跳转到异常模式或调试模式（具体取决于处理器的配置和调试环境的设置）。这使得调试器能够在特定的程序点设置断点，从而方便地检查和调试程序的运行状态。ebreak指令在RISC-V中用于触发断点。当CPU执行到ebreak指令时，它的行为取决于当前特权级别（User Mode, Supervisor Mode, Machine Mode）以及dcsr寄存器中相应的ebreak模式控制位（ebreakm, ebreaku, ebreaks）

- ebreakm：控制Machine Mode下的ebreak行为。
  
 - 当ebreakm为0时，ebreak在Machine Mode下会触发一个异常（通常是机器模式中断）。
 
 - 当ebreakm为1时，ebreak在Machine Mode下会使CPU进入调试模式。

- ebreaku：控制User Mode下的ebreak行为，类似ebreakm，但应用于User Mode。

- ebreaks：控制Supervisor Mode下的ebreak行为，类似ebreakm，但应用于Supervisor Mode。

# **2. DSCR寄存器与GDB命令**
  DCSR（Debug Control and Status Register）是RISC-V调试模块中的一个关键寄存器，用于控制调试行为，包括上述的ebreak模式控制位。
  GDB中，您可以使用monitor命令来直接操作RISC-V调试模块的相关寄存器，从而改变ebreak指令的行为。您提到的命令如下：

- **monitor target riscv set_ebreakm off**：将指定target的dcsr寄存器中的ebreakm位设置为0，即Machine Mode下的ebreak将触发异常而不是进入调试模式。

<div align=center>
<img src=./images/ebreak/ebreakm.png>
</div>

- **monitor target riscv set_ebreaks off**：将指定target的dcsr寄存器中的ebreaks位设置为0，即Supervisor Mode下的ebreak将触发异常而不是进入调试模式。

<div align=center>
<img src=./images/ebreak/ebreaks.png>
</div>

- **monitor target riscv set_ebreaku off**：将指定target的dcsr寄存器中的ebreaku位设置为0，即User Mode下的ebreak将触发异常而不是进入调试模式。

<div align=center>
<img src=./images/ebreak/ebreaku.png>
</div>

这些命令允许开发者在调试过程中灵活地控制ebreak指令的行为，从而根据需要选择进入调试模式或触发异常。
通过调整dcsr寄存器中的ebreak模式控制位，以及使用GDB中的相应命令，开发者可以精确控制RISC-V架构中ebreak指令的行为，这对于调试和验证程序逻辑至关重要。
# 3. **应用场景**

ebreak指令在RISC-V架构的调试过程中起着至关重要的作用。它允许开发者在程序的任意位置设置断点，从而方便地检查程序的执行流程、变量值以及内存状态等。这对于发现程序中的错误、优化程序性能以及理解程序的内部工作机制都是非常有帮助的。
# 4. **调试应用**

在调试过程中，ebreak指令的应用非常广泛。以下是一些常见的应用场景：
1. **设置断点**：调试器可以在需要暂停执行的代码位置插入ebreak指令，以便在处理器执行到该位置时自动暂停执行。这有助于开发人员分析程序的执行流程、变量值等信息。
2. **单步执行**：通过连续插入ebreak指令，并在每个断点处暂停执行，可以实现程序的单步执行。这有助于开发人员逐步跟踪程序的执行过程，找出潜在的问题。
3. **触发异常**：在某些情况下，开发人员可能需要故意触发异常以测试异常处理程序的正确性。此时，可以在代码中插入ebreak指令来触发调试异常。
# 5. **使用注意事项**

## 5.1 **调试环境配置**
  在使用ebreak指令进行调试之前，需要确保调试环境已经正确配置。这包括设置调试器、连接调试接口（如JTAG接口）以及配置处理器以支持调试模式等。
## 5.2 **异常处理程序**
  为了确保程序在触发BREAKPOINT异常后能够正确恢复执行，需要编写合适的异常处理程序。这个处理程序应该能够记录异常信息、保存现场上下文（如使用mscratch寄存器）并在处理完异常后使用mret指令返回到用户程序继续执行。
## 5.3 **避免滥用**
  虽然ebreak指令非常强大和灵活，但滥用它可能会导致程序执行效率低下或难以调试。因此，在使用ebreak指令时应该谨慎考虑其使用场景和必要性。
# 6. **示例**

````
#include "asm/csr.h"  // 包含RISC-V的控制和状态寄存器（CSR）相关的定义和函数。
#include "asm/irq.h"  // 包含与中断请求（IRQ）相关的定义和函数。
#include "asm/sbi.h"  // 包含与RISC-V的安全监督二进制接口（SBI）相关的定义和函数。

extern void trap_init(void); //声明一个外部函数trap_init，这个函数的作用是初始化陷阱处理机制。陷阱可以是异常（如除零错误）或中断（如来自外部设备的信号）。

int main(void)
{
        trap_init();   //初始化陷阱处理机制

        arch_local_irq_enable();  // 调用一个函数来启用本地中断。

        asm volatile("ebreak");  //使用内联汇编插入一条ebreak指令。

        while (1) {}
        return 0;
}
````
## 6.1 **进入示例**
[下载实验代码-ebreak](code/ebreak)

下载解压并进入示例目录

## 6.2 **编译**
````
make
````
## 6.3 **运行**
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
 stvec=0x80200938, 0x80200938
Handle breakpoint exception
````
详见请参考文档：实验环境搭建。
