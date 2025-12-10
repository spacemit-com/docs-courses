RISC-V Vector扩展（RVV）和ARM SVE/SVE2都是现代处理器中用于加速向量计算的指令集扩展，但它们在设计理念、架构实现和应用场景上有显著差异。以下从技术角度进行对比分析：

# 1 共同点

## 1.1 可伸缩的矢量设计

两者均支持可变矢量长度（Vector Length Agnostic, VLA），即代码无需绑定固定矢量长度，可适配不同硬件实现（如128位、256位或更长）。

AI 运算单元的位宽远大于之前使用的位宽。若依据传统SIMD 的理念，每当位宽变化一次，便需增添成千上万条指令，这对于处理器的设计以及编译器的开发而言，负担极为沉重。然而，Vector 指令的思路在于将软件需处理的单元位宽与硬件实际的运算单元位宽进行分离。相同的程序，在具有 128 位向量寄存器的 CPU 上能够运行，在具备 2048 位向量寄存器的 CPU 上同样可以运行。显然，这种方式更具灵活性，也更能满足当前 AI 运算对于宽运算单元的需求。

## 1.2 面向高性能计算

目标应用场景高度重叠，包括机器学习、科学计算、图像处理等数据密集型任务。

## 1.3 灵活的寄存器分配

均采用动态寄存器分配机制，允许编译器或硬件根据操作数长度自动分配寄存器资源，提高资源利用率。

## 1.4 掩码（Masking）支持

均支持条件掩码操作，可对矢量中的部分元素进行条件执行，减少分支预测开销。

# 2 不同点

特性 | SVE（ARM） | RVV（RISC-V）
--- | --- | ---
指令集架构 | ARM v8/v9 的扩展 | RISC-V 的官方矢量扩展（V 扩展）
设计哲学 | 硬件透明性优先，强调代码兼容性 | 灵活性与可配置性优先，允许硬件定制
寄存器结构 | 独立的谓词寄存器（P0-P15）+ Z 寄存器 | 通用寄存器复用为掩码，矢量寄存器可配置，简化设计
最小实现要求 | 必须支持 128 位矢量 | 无固定最小长度，支持从 128 位到任意扩展
编程模型 | 强调编译器自动优化（如自动矢量化） | 更多暴露硬件细节，支持手动优化
数据类型支持 | 支持 FP32/FP64、INT8/16/32/64 等 | 支持 FP16/32/FP64、INT8/16/32/64 等，允许配置裁剪
内存访问模式 | 支持复杂寻址 | 更强调显式内存操作
应用场景 | ARM生态的高性能计算（服务器、超算） | RISC-V的定制化场景（AIoT、边缘计算）

# 3 代码示例

代码下载：[add-examples](code/chap0203/add-examples.tar.gz)

以向量加法为例：

## 3.1 SVE实现

> 代码可参考：

````c
void vector_add_sve(int32_t* vec1, int32_t* vec2, int32_t* result, size_t size) {
    // 获取当前硬件支持的向量长度（以int32_t元素数量为单位）
    size_t vl = svcntw();

    for (size_t i = 0; i < size; i += vl) {
        // 生成谓词掩码（pg），标记 i 到 size 之间的有效元素
        svbool_t pg = svwhilelt_b32(i, size);
        // 加载向量数据（仅处理掩码标记的有效元素）
        svint32_t v1 = svld1(pg, &vec1[i]);
        svint32_t v2 = svld1(pg, &vec2[i]);
        // 执行向量加法（掩码外元素清零）
        svint32_t vresult = svadd_z(pg, v1, v2);
        // 存储结果（仅写入掩码标记的位置）
        svst1(pg, &result[i], vresult);
    }
}
````

> 此代码仅供参考，旨在展示两种指令集在实际使用时的不同

这里的代码实现仅供参考，旨在展示两种指令集在使用时的不同之处。

## 3.2 RVV实现

> 代码可参考：

````c
void vector_add_rvv(int32_t* vec1, int32_t* vec2, int32_t* result, size_t size) {
    // 设置向量长度
    size_t vl;

    for (size_t i = 0; i < size; i += vl) {
        // 动态设置向量长度，如果__riscv_vsetvlmax_e32m4()>size-i，长度会被设置为size-i，否则会被设置为__riscv_vsetvlmax_e32m4()
        vl = __riscv_vsetvl_e32m4(size - i);  
        vint32m4_t v1 = __riscv_vle32_v_i32m4(&vec1[i], vl);  // 加载 vec1
        vint32m4_t v2 = __riscv_vle32_v_i32m4(&vec2[i], vl);  // 加载 vec2
        vint32m4_t vresult = __riscv_vadd_vv_i32m4(v1, v2, vl);  // 向量加法
        __riscv_vse32_v_i32m4(&result[i], vresult, vl);  // 存储结果
    }
}
````

下面介绍用到的指令：

```c
vl = __riscv_vsetvl_e32m4(size - i);
```


- **功能**：动态设置向量寄存器组的有效长度
- **参数说明**：
  - `e32`：每个元素32位
  - `m4`：使用4个向量寄存器组(LMUL=4)
  - `size - i`：剩余要处理的元素数量
- **返回值**：实际设置的向量长度(vl)


```c
vint32m4_t v1 = __riscv_vle32_v_i32m4(&vec1[i], vl);
```

- **功能**：从内存加载数据到向量寄存器
- **参数说明**：
  - `vle32`：加载32位元素
  - `v_i32m4`：目标为4倍宽度的32位整数向量
  - `&vec1[i]`：内存源地址
  - `vl`：本次加载的元素数量

```c
vint32m4_t vresult = __riscv_vadd_vv_i32m4(v1, v2, vl);
```

- **功能**：执行向量-向量加法运算
- **参数说明**：
  - `vadd_vv`：向量-向量加法操作
  - `i32m4`：4倍宽度的32位整数向量
  - `v1, v2`：两个源操作数
  - `vl`：参与计算的元素数量

```c
__riscv_vse32_v_i32m4(&result[i], vresult, vl);
```

- **功能**：将向量寄存器中的数据存储到内存
- **参数说明**：
  - `vse32`：存储32位元素
  - `v_i32m4`：4倍宽度的32位整数向量
  - `&result[i]`：目标内存地址
  - `vresult`：源向量寄存器
  - `vl`：本次存储的元素数量


编译运行：

```bash
riscv64-unknown-linux-gnu-gcc riscv_vector_add.c -march=rv64gcv -o ins.out -static
./ins.out
```

运行结果：

```text
9 9 9 9 9 9 9 9
```
