#include <stdio.h>

int main() {
    int *ptr = NULL;  // 定义一个空指针，未指向任何有效地址

    *ptr = 10;  // 尝试通过空指针访问内存，这会导致段错误
    printf("Value: %d\n", *ptr);  // 这行代码不会被执行

    return 0;
}
