#include <riscv_vector.h>
#include <stdio.h>
#include <stdlib.h>

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

int main() {
    int32_t vec1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int32_t vec2[] = {8, 7, 6, 5, 4, 3, 2, 1};
    int32_t result[8];

    vector_add_rvv(vec1, vec2, result, 8);

    for (size_t i = 0; i < 8; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}