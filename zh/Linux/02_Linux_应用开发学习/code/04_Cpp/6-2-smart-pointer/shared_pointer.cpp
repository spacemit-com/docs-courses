#include <iostream>
#include <memory>
using namespace std;

class MyClass {
   public:
    MyClass() { cout << "占用内存" << endl; }
    ~MyClass() { cout << "释放内存" << endl; }
};

int main() {
    shared_ptr<MyClass> p1 = make_shared<MyClass>();
    cout << "Use count: " << p1.use_count() << endl;  // 输出1
    shared_ptr<MyClass> p2 = p1;                      // p1 和 p2 共享所有权
    cout << "Use count: " << p1.use_count() << endl;  // 输出2
    p2.reset();                                       // p2释放所有权
    cout << "Use count after reset: " << p1.use_count() << endl;  // 输出1
    return 0;
}