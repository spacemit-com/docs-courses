#include <stdio.h>
#include <string.h>

struct Person {
    char name[50];
    int age;
    float height;
};

int main() {
    struct Person person1 = {"Alice", 30, 1.65};
    struct Person person2;
    person2.age = 25;
    strcpy(person2.name, "Bob");
    person2.height = 1.75;

    printf("Name: %s\n", person1.name);
    printf("Age: %d\n", person1.age);
    printf("Height: %.2f\n", person1.height);

    return 0;
}