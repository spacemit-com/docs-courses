#include <arm_neon.h>
#include <stdio.h>

void vector_add_neon(int32_t *vec1, int32_t *vec2, int32_t *result, int size)
{
    // 按照 4 个整数一组进行处理
    for (int i = 0; i < size / 4; ++i)
    {
        // 加载向量数据到 NEON 寄存器
        int32x4_t v1 = vld1q_s32(&vec1[i * 4]);
        int32x4_t v2 = vld1q_s32(&vec2[i * 4]);

        // 执行向量加法
        int32x4_t vresult = vaddq_s32(v1, v2);

        // 将结果存储回内存
        vst1q_s32(&result[i * 4], vresult);
    }
}

int main()
{
    int32_t vec1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int32_t vec2[] = {8, 7, 6, 5, 4, 3, 2, 1};
    int32_t result[8];

    vector_add_neon(vec1, vec2, result, 8);

    for (int i = 0; i < 8; ++i)
    {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}