# 1 从并行计算说起

使用RISC-V的Vector指令对程序进行优化，属于并行计算的范畴。并行计算（Parallel Computing）是一种通过分解任务、协同处理来提升计算效率的计算范式，其核心目标是通过最大限度利用计算资源，提升任务处理速度或解决更大规模的问题。它并非单纯的多任务执行，而是多层级协同的计算模式创新。

## 1.1 并行计算简介

### 1.1.1 硬件层次划分

级别 | 技术方案 | 典型案例
--- | --- | ---
指令级别并行| SIMD向量化 | RISC-V向量指令优化算法
线程级别并行| 多核CPU超线程 | OpenMP实现单机8核并行排序算法
进程级别并行| 分布式计算 | MPI集群完成气候模型的区域拆分求解
众核级别并行| GPU/TPU加速卡 | CUDA实现ResNet-50的层间并行推理

### 1.1.2 任务执行模式划分

- 数据并行
 同一操作应用在不同数据块（如深度学习数据分片训练）
- 任务并行
 多个独立任务同时执行（如Web服务器处理多用户请求）
- 流水线并行
 多阶段处理链式分解（如CPU指令流水线、渲染管线阶段的并行执行）

## 1.2 本文重点

本文主要介绍的指令级并行的优化。对程序进行指令级并行的优化，需要使用SIMD指令（ARM NEON，X86 SSE等）或者RISC-V Vector指令，其本质是一种通过单条指令并行处理多个数据元素的硬件加速技术。
使用指令级并行的优化的典型场景有：
- AI算法，如卷积、矩阵乘法、池化等
- 经典图像算法，如滤波算法，特征点提取等
- 基础数学计算，如对数，指数，快速傅里叶变换等

## 1.3 优化性能简单评估方法

优化的目的是提升计算性能，我们以K1为例，评估一下优化对这些数据密集型的计算的提升呢。基本计算公式为：倍数 = 256 / 数据位宽。以int8数据为例，一般的程序可以有接近16倍的提升。当然，也会因为算法的复杂度不同，性能会有波动。
- 比如求两个向量的最大值（一维向量优化案例），在并行化的基础上，省掉了判断语句（分支跳转），性能会有更大的提升。
- 比如向量加法，是一个访存密集型计算（简单理解就是在整个程序中，访存占比比计算占比高），访存性能对整体性能影响很大，性能提升一般达不到理论值，如语言说明章节中的例子。

# 2 优化技巧简介

在K1上，使用向量指令对计算进行优化，会有相应的技巧，主要有循环展开，数据局部性，时空转换策略等。并对循环展开做了详细的分析。其他策略，后面的介绍中会有涉及。

## 2.1 循环展开

循环展开是向量指令优化的基础，相比于标量值了的单调指令处理单条数据，向量指令每次计算多条数据，就是对循环的展开。我们以向量加法为例：

```
#define LEN 100
int a[LEN] = {};
int b[LEN] = {};
int c[LEN] = {};

// 原始代码
for (int i = 0; i < LEN; i++) {
    c[i] = a[i] + b[i];
    }
// 循环展开代码, 每次计算8个元素
for（int i = 0; i < LEN/8；i++）{
    c[8 * i] = a[8 * i] + b[8 * i];
    c[8 * i + 1] = a[8 * i + 1] + b[8 * i + 1];
    c[8 * i + 2] = a[8 * i + 2] + b[8 * i + 2];
    c[8 * i + 3] = a[8 * i + 3] + b[8 * i + 3];
    c[8 * i + 4] = a[8 * i + 4] + b[8 * i + 4];
    c[8 * i + 5] = a[8 * i + 5] + b[8 * i + 5];
    c[8 * i + 6] = a[8 * i + 6] + b[8 * i + 6];
    c[8 * i + 7] = a[8 * i + 7] + b[8 * i + 7];
}

// 基于循环展开代码, 使用向量指令（为了方便演示，以下向量指令使用伪码进行展示）
for（int i = 0; i < LEN/8；i++）{
    v_a = vload(&a[8 * i]);    // load 8个a数据
    v_b = vload(&b[8 * i]);    // load 8个b数据
    v_c = vadd（v_a, v_b）；    // 向量加法，将8个元素同时相加得到8个c数据
    vse(v_c，&c[8 * i]);        // store 8个c数据
}

```

## 2.2 数据局部性

内存层级结构的黄金法则：
- 循环分块技术（Blocking）：将大矩阵分块处理以适应L3缓存
- 访问模式改进：网络推理中的ping-pong buffer结构
- 内存对齐（64字节对齐策略）

## 2.3 时空转化策略

典型应用包括：
- SIMD查询表预计算（三角函数近似计算）
- RNN中的状态缓存重用
- 动画渲染的位图缓存策略

# 3 实现语言说明

使用K1的vector指令，可以有两种方式，intrinsic和纯汇编。Intrinsic是编译器对汇编指令的封装，可以使用类C的语法，进行向量编程，不用关注寄存器等硬件信息，门槛较低，推荐初学者使用。而使用纯汇编优化，就需要了解寄存器、硬件流水线等新建信息，有一定门槛。
还是以向量加法为例，分别使用intrinsic和汇编，进行展示。

[原始代码下载](code/chap01/example.tar.gz)

## 3.1 原始C代码

```
#include <stdio.h>
#include <sys/time.h>

#define LEN (512)
int a[LEN] = {};
int b[LEN] = {};
int c[LEN] = {};

struct timeval start, end;

int main ()
{
    int length = LEN;

    gettimeofday(&start, NULL);
    for (int m = 0; m < 1000; m++) {
        for (int i = 0; i < length; i++) {
            c[i] = a[i] + b[i];
        }
    }
    gettimeofday(&end, NULL);
    long long int time = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    printf("the total time is %lld.\n", time);

    return 0;
}
```

编译运行：
```bash
riscv64-unknown-linux-gnu-gcc vadd_example.c -march=rv64gc_zba -o vadd_example -static -O2
./vadd_example
```
## 3.2 Intrinsic代码

```
#include <stdio.h>
#include <sys/time.h>
#include <riscv_vector.h>

#define LEN (512)
int a[LEN] = {};
int b[LEN] = {};
int c[LEN] = {};

struct timeval start, end;

int main ()
{

    gettimeofday(&start, NULL);
    for (int m = 0; m < 1000; m++) {
        int length = LEN;
        int *pa = a;
        int *pb = b;
        int *pc = c;

        while (length > 0) {
            size_t gvl = __riscv_vsetvl_e32m4(length);
            vint32m4_t v_a = __riscv_vle32_v_i32m4(pa, gvl); // load 8个a数据
            vint32m4_t v_b = __riscv_vle32_v_i32m4(pb, gvl); // load 8个b数据
            vint32m4_t v_c = __riscv_vadd_vv_i32m4(v_a, v_b, gvl); // 向量加法，将8个元素同时相加得到8个c数据
            __riscv_vse32_v_i32m4(pc, v_c, gvl);  // store 8个c数据
            pa += gvl;
            pb += gvl;
            pc += gvl;
            length -= gvl;
        }
    }

    gettimeofday(&end, NULL);
    long long int time = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    printf("the total time is %lld.\n", time);

    return 0;
}
```

编译运行：
```bash
riscv64-unknown-linux-gnu-gcc vadd_example_intrinsic.c -march=rv64gcv_zba -o vadd_example_intrinsic -static -O2
./vadd_example_instrinsic
```
## 3.3 汇编代码

```
#include <stdio.h>
#include <sys/time.h>
#include <riscv_vector.h>

#define LEN (512)
int a[LEN] = {};
int b[LEN] = {};
int c[LEN] = {};

struct timeval start, end;

int main ()
{
    int length = LEN;

    gettimeofday(&start, NULL);
    for (int m = 0; m < 1000; m++) {
        int *pa = a;
        int *pb = b;
        int *pc = c;

        asm volatile(
          "mv             t1, %[LENGTH]   \n\t"
          "LOOP:                          \n\t"
          "vsetvli        t0, t1, e32, m4 \n\t"
          "vle32.v        v0, (%[A])      \n\t"
          "sh2add         %[A], t0, %[A]  \n\t"
          "vle32.v        v4, (%[B])      \n\t"
          "sh2add         %[B], t0, %[B]  \n\t"
          "vadd.vv        v8, v0, v4      \n\t"
          "vse32.v        v8, (%[C])      \n\t"
          "sh2add         %[C], t0, %[C]  \n\t"
          "sub            t1, t1, t0      \n\t"
          "bgtz           t1, LOOP        \n\t"
          :[A] "+r" (pa), [B] "+r" (pb), [C] "+r" (pc)
          :[LENGTH] "r"(length)
          :"t0", "t1", "v0", "v1", "v2", "v3", "v4", "v5",
           "v6", "v7", "v8", "v9", "v10", "v11"
          );
    }

    gettimeofday(&end, NULL);
    long long int time = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    printf("the total time is %lld.\n", time);

    return 0;
}
```

编译运行：
```bash
riscv64-unknown-linux-gnu-gcc vadd_example_asm.c -march=rv64gcv_zba -o vadd_example_asm -static -O2
./vadd_example_asm
```

## 3.4 运行结果对比

各程序性能对比如下表所示（会有一定的波动）：

版本| 时间（us）
--- | ---
vadd_example | 1359
vadd_example_intrinsic | 377
vadd_example_asm | 375

