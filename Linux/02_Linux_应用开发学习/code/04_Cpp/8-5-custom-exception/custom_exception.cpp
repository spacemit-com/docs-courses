#include <iostream>
#include <stdexcept>
using namespace std;

class MyException : public exception {
   public:
    const char* what() const noexcept override {
        return "My custom exception occurred";
    }
};

void test_custom_exception() {
    throw MyException();  // 抛出自定义异常
}

int main() {
    try {
        test_custom_exception();
    } catch (const MyException& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    return 0;
}