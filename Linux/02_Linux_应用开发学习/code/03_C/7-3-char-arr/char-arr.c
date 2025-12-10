#include <stdio.h>

int main() {
    char str[] = "Hello, World!";
    size_t length = sizeof(str);  // length 将会等于 14
    printf("String: %s，length of str is %zu\n", str, length);
    return 0;
}