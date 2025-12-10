#include <stdio.h>
#include <string.h>

int main() {
    struct Address {
        char city[50];
        char street[50];
        int zipCode;
    };

    struct Person {
        char name[50];
        int age;
        float height;
        struct Address address;
    };

    struct Person person3 = {"Charlie", 28, 1.80, {"New York", "5th Avenue", 10001}};
    printf("City: %s\n", person3.address.city);

    return 0;
}