#include <iostream>
using namespace std;

class Animal {
   public:
    virtual void speak() { cout << "Animal speaks" << endl; }
};

class Dog : public Animal {
   public:
    void speak() override { cout << "Dog barks" << endl; }
};

class Cat : public Animal {
   public:
    void speak() override { cout << "Cat meows" << endl; }
};

int main() {
    Animal* animal = new Dog();
    Animal* cat = new Cat();
    animal->speak();  // 调用 Dog 的 speak 实现
    cat->speak();     // 调用 Cat 的 speak 实现
    delete animal;
    delete cat;
    return 0;
}