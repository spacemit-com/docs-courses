#include <iostream>
using namespace std;

void checkPointer(int* ptr) {
    if (ptr == nullptr) {
        cout << "Pointer is null" << endl;
    } else {
        cout << "Pointer is not null" << endl;
    }
}

int main() {
    int* p = nullptr;  // 使用nullptr初始化
    checkPointer(p);

    int value = 10;
    p = &value;
    checkPointer(p);

    return 0;
}