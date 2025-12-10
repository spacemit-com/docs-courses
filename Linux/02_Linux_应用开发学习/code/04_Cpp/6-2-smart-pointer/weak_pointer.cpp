#include <iostream>
#include <memory>
using namespace std;

class MyClass {
   public:
    int value;
    shared_ptr<MyClass> next;
    weak_ptr<MyClass> prev;  // 使用weak_ptr避免循环引用

    MyClass(int val) : value(val) {}
    ~MyClass() {
        cout << "MyClass with value " << value << " destroyed" << endl;
    }
};

int main() {
    shared_ptr<MyClass> node1 = make_shared<MyClass>(1);
    shared_ptr<MyClass> node2 = make_shared<MyClass>(2);

    node1->next = node2;
    node2->prev = node1;  // 避免循环引用

    return 0;
}