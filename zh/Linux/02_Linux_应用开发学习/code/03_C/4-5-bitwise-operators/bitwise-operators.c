#include <stdio.h>

int main() {
    int a = 5;      // 0101
    int b = 3;      // 0011
    int result1 = a & b;  // 0001 = 1
    int result2 = a | b;  // 0111 = 7
    int result3 = a ^ b;  // 0110 = 6
    int result4 = ~a;     // 1010 (取决于整数的位数)
    int result5 = a << 1; // 1010 = 10
    int result6 = a >> 1; // 0010 = 2

    printf("result1 = %d\n", result1);
    printf("result2 = %d\n", result2);
    printf("result3 = %d\n", result3);
    printf("result4 = %d\n", result4);
    printf("result5 = %d\n", result5);
    printf("result6 = %d\n", result6);

    return 0;
}