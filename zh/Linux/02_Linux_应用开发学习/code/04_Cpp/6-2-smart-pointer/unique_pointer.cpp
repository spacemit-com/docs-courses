#include <iostream>
#include <memory>
using namespace std;

class MyClass {
   public:
    MyClass() { cout << "占用内存" << endl; }
    ~MyClass() { cout << "释放内存" << endl; }
};

int main() {
    unique_ptr<MyClass> p1 = make_unique<MyClass>();  // 创建一个unique_ptr
    // unique_ptr不能被复制
    // unique_ptr<int> p2 = p1; // 错误！

    // 但可以转移所有权
    unique_ptr<MyClass> p2 = move(p1);
    return 0;
}