#include <stdio.h>

int multiply(int a, int b) {
    return a * b;
}

float divide(float a, float b) {
    if (b != 0) {
        return a / b;
    } else {
        printf("Error: Division by zero\n");
        return 0;
    }
}

int main() {
    int product = multiply(4, 5);
    printf("Product: %d\n", product);

    float quotient = divide(10.0, 2.0);
    printf("Quotient: %.2f\n", quotient);
    return 0;
}