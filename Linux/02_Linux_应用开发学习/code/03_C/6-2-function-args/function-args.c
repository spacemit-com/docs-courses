#include <stdio.h>

// 值传递
void printValue(int x) {
    printf("Value: %d\n", x);
}

// 引用传递
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int num = 10;
    printValue(num);

    int x = 5, y = 10;
    swap(&x, &y);
    printf("x: %d, y: %d\n", x, y);
    return 0;
}