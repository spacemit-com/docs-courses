#include <stdio.h>
#include "utils.h"  // 包含工具函数声明

int main() {
    int a, b;

    // 用户输入a和b的值
    printf("Enter two integers (a and b): ");
    scanf("%d %d", &a, &b);

    // 调用工具函数并输出结果
    printf("Sum: %d\n", add(a, b));         // 调用add函数
    printf("Difference: %d\n", subtract(a, b)); // 调用subtract函数

    return 0;
}
