#include <stdio.h>   // 预处理指令，用于包含标准输入输出库

#define PI 3.14159    // 宏定义，定义了一个常量 PI

// 函数声明
int add(int a, int b);  // 函数声明，int 是关键字，add 是标识符，a 和 b 是参数标识符

int main() {         // 主函数，int 是关键字，main 是标识符
    // 变量声明
    int num1, num2, sum;  // 变量声明，int 是关键字，num1, num2, sum 是标识符

    // 用户输入
    // 函数调用，printf 是标识符，"Enter two integers: " 是字符串字面量
    printf("Enter two integers: ");
    // 函数调用，scanf 是标识符，"%d %d" 是字符串字面量，&num1 和 &num2 是地址运算符和标识符 
    scanf("%d %d", &num1, &num2);

    // 函数调用
    // 函数调用，add 是标识符，num1 和 num2 是标识符，sum 是标识符
    sum = add(num1, num2);

    // 输出结果
    // 函数调用，printf 是标识符，"Sum: %d\n" 是字符串字面量，sum 是标识符
    printf("Sum: %d\n", sum);

    return 0;  // 返回语句，return 是关键字，0 是常量
}

// 函数定义
// 函数定义，int 是关键字，add 是标识符，a 和 b 是参数标识符
int add(int a, int b) {
    // 返回语句，return 是关键字，a 和 b 是标识符，+ 是运算符
    return a + b;
}