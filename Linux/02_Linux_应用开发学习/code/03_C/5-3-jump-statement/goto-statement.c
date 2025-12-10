#include <stdio.h>

int main() {
    int i = 0;
    label:
    printf("i = %d\n", i);
    i++;
    if (i < 5) {
        goto label;
    }
    return 0;
}