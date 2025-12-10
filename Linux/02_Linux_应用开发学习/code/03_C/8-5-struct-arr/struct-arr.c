#include <stdio.h>

struct Person {
    char name[50];
    int age;
    float height;
};

int main() {
    struct Person people[2] = {
        {"David", 22, 1.70},
        {"Eva", 27, 1.68}
    };

    for (int i = 0; i < 2; i++) {
        printf("Name: %s, Age: %d, Height: %.2f\n", people[i].name, people[i].age, people[i].height);
    }

    return 0;
}