#include <stdio.h>

int main() {
    int a = 10;
    if (a > 5) {
        printf("a is greater than 5\n");
    } else if (a == 5) {
        printf("a is equal to 5\n");
    } else {
        printf("a is less than 5\n");
    }
    return 0;
}