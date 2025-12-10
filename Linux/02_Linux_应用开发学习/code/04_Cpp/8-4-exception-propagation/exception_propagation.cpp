#include <iostream>
#include <stdexcept>
using namespace std;

void f() {
    throw runtime_error("Error in f");
}

void g() {
    f();  // 抛出异常
}

int main() {
    try {
        g();  // 捕获异常
    } catch (const runtime_error& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    return 0;
}