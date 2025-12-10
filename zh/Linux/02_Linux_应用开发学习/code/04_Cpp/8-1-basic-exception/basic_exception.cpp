#include <iostream>
using namespace std;

int divide(int a, int b) {
    if (b == 0) {
        throw "Division by zero error";  // 抛出字符串类型的异常
    }
    return a / b;
}

int main() {
    try {
        cout << divide(10, 2) << endl;  // 正常除法
        cout << divide(10, 0) << endl;  // 会抛出异常
    } catch (const char* msg) {
        cout << "Caught an exception: " << msg << endl;
    }
    return 0;
}