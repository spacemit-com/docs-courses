# 1. **CSR概述**   

系统指令用于访问那些可能需要特权访问的系统功能，以I类指令格式编码。这可以分为两类：一类是原子性读-修改-写控制和状态寄存器（CSR）的指令，另一类是其他特权指令。

所有的CSR指令都会对CSR进行读——改——写操作。CSR指令中共有12位（20-31位）用来指示被“读改写”的是哪一个寄存器。
<div align='center'>
<img src=./images/csr/csr0.png>
</div>
<div align='center'>
表1.1：CSR指令的编码
</div>
<div align='center'>
<img src=./images/csr/csr2.2.png>
</div>
<div align='center'>
表1.2：当前已分配的RISC-V用户级CSR地址
</div>
<div align='center'>
<img src=./images/csr/csr2.3.png>
</div>
<div align='center'>
表1.3：当前已分配的RISC-V管理员级CSR地址
</div>
<div align='center'>
<img src=./images/csr/csr3.png>
</div>
<div align='center'>
表1.4：当前已分配的RISC-V Hypervisor级CSR地址
</div>
<div align='center'>
<img src=./images/csr/csr4.png>
</div>
<div align='center'>
表1.5：当前已分配的RISC-V机器级CSR地址
</div>
控制和状态寄存器,RISC-V中特殊的一类寄存器，用于存储与CPU状态和控制相关的信息。CSR操作指令包括以下几类。

## 1.1 **CSRRW**
**名称：**
  读后立即写控制状态寄存器

**指令格式：**
````
csrrw rd,csr,rs1
````
**功能：**
将指定的CSR寄存器中的值读出并赋值到目的寄存器rd中，然后将源寄存器rs1中的值写入该CSR寄存器。

**示例：**
``` 
csrrw x13,mie,x12 #将mie寄存器中的值读出并赋值给x13寄存器，然后将x12寄存器中的值按位或的结果写入mie寄存器。
```
## 1.2 **CSRRS**
**名称：**
  读后置位控制状态寄存器

**指令格式：**
````
csrrs rd,csr,rs1
````
**功能：**
将指定的CSR寄存器中的值读出并赋值到目的寄存器rd中，然后将CSR寄存器中的值和寄存器rs1中的值按位或（bitwise OR）的结果写入CSR寄存器。这相当于将rs1中所有为1的位所对应的CSR中的位都置为1。

**示例：**
```
csrrs x13,mie,x12 #将mie寄存器中的值读出并赋值给x13寄存器，然后将mie寄存器中的值和x12寄存器中的值按位或的结果写入mie寄存器。
```
## 1.3 **CSRRC**
**名称：**
  读后清除控制状态寄存器

**指令格式：**
````
csrrc rd,csr,rs1
````
**功能：**
 将指定的CSR寄存器中的值读出并赋值到目的寄存器rd中，然后将CSR寄存器中的值和寄存器rs1中的值取反后按位与（bitwise AND NOT）的结果写入CSR寄存器。这相当于将rs1中所有为1的位所对应的CSR中的位都清零。

**示例：**
```
csrrc x13,mie,x12  #将mie寄存器中的值读出并赋值给x13寄存器，然后将mie寄存器中的值和x12寄存器中的值取反后按位与的结果写入mie寄存器。
```
## 1.4 **CSRRWI**
**名称：**
  立即数读后写控制状态寄存器

**指令格式：**
````
csrrwi rd, csr, uimm
````
**功能：**
 将指定的CSR寄存器中的值读出并赋值到目的寄存器rd中，然后将一个5位的无符号立即数（uimm）扩展为32位后写入该CSR寄存器。

**示例：**
```
csrrwi x13,mie,5   #将mie寄存器中的值读出并赋值给x13寄存器，然后将5（扩展为32位的0000_0005）写入mie寄存器。
```
## 1.5 **CSRRSI**
**名称：**
  立即数读后设置控制状态寄存器

**指令格式：**
````
csrrsi rd, csr, uimm
````
**功能：**
功能类似与CSRRS，但不同之处在于源值是一个立即数而不是寄存器值。

**示例：**
```
csrrsi t0, mstatus, 0b0000_0100  // 立即数为0b0000_0100，表示要将第3位设置为1
```
## 1.6 **CSRRCI**
**名称：**
  立即数读后清除控制状态寄存器

**指令格式：**
````
csrrci rd, csr, uimm
````
**功能：**
与功能类似CSRRC，但不同之处在于源值是一个立即数而不是寄存器值。

**示例：**
```
csrrci t1, mstatus, 0b0000_0010  // 立即数为0b0000_0010，表示要清除第2位
```

# 2. **示例**
````
#include "type.h"       //包含类型定义，如uint64_t等。
#include "printk.h"    //包含printk函数的声明，该函数用于在内核或裸机环境中打印信息。
#include "asm/csr.h"   //包含CSR（控制状态寄存器）相关操作的声明。这包括读取和写入CSR寄存器的函数或宏。

uint64_t read_sscratch(void); //声明一个函数，用于读取sscratch寄存器的值。
void write_sscratch(uint64_t sscratch); //声明一个函数，用于将指定的值写入sscratch寄存器。

int main(void)
{
        printk("sscratch value: 0x%llx\n", read_sscratch()); //printk打印当前sscratch寄存器的值。这通过调用read_sscratch()函数实现。
        write_sscratch(0x1234567812345678);  //特定的值写入sscratch寄存器。
        printk("sscratch value: 0x%llx\n", read_sscratch()); //重新打印sscratch寄存器的值，以验证写入是否成功。
        while (1) {}
        return 0;
}
````
## 2.1 **进入示例**

[下载实验代码-csr](code/csr_operation)

下载解压并进入示例目录

## 2.2 **编译**
````
make
````
## 2.3 **运行**
````
make run
````
**运行LOG如下**
````
qemu-system-riscv64 -nographic -machine virt -m 128M  -bios m_mode.bin  -device loader,file=s_mode.bin,addr=0x80200000  -kernel s_mode.elf
   _____ ____ _____
   / ____|  _ \_   _|
 | (___ | |_) || |
  \ \___ \|  _ < | |
  ____) | |_) || |_
 |_|_____/|____/_____|

sscratch value: 0x0
sscratch value: 0x1234567812345678
````
详见请参考文档：实验环境搭建。
