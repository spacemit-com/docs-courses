#include <arm_sve.h>
#include <stdio.h>
#include <stdlib.h>

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

int main() {
    // 初始化测试数据
    int32_t vec1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int32_t vec2[] = {8, 7, 6, 5, 4, 3, 2, 1};
    int32_t result[8];

    // 调用 SVE 向量加法函数
    vector_add_sve(vec1, vec2, result, 8);

    // 打印结果
    for (size_t i = 0; i < 8; i++) {
        printf("%d ", result[i]);
    }
    printf("\n"); // 输出: 9 9 9 9 9 9 9 9

    return 0;
}