#include <stdio.h>
#include <stdlib.h>

int global_initialized = 10;        // 初始化数据段
int global_uninitialized;           // 未初始化数据段

void memory_demo() {
    static int static_initialized = 20;   // 初始化数据段
    static int static_uninitialized;      // 未初始化数据段

    int local_var = 30;                   // 栈区
    int *dynamic_var = malloc(sizeof(int)); // 堆区
    *dynamic_var = 40;

    printf("Code Segment: %p\n", (void*)memory_demo);
    printf("Initialized Data Segment: %p\n", (void*)&global_initialized);
    printf("Uninitialized Data Segment (BSS): %p\n", (void*)&global_uninitialized);
    printf("Static Initialized Data Segment: %p\n", (void*)&static_initialized);
    printf("Static Uninitialized Data Segment (BSS): %p\n", (void*)&static_uninitialized);
    printf("Stack Segment: %p\n", (void*)&local_var);
    printf("Heap Segment: %p\n", (void*)dynamic_var);

    free(dynamic_var);
}

int main() {
    memory_demo();
    return 0;
}
