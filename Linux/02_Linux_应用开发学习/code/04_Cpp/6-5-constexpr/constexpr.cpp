#include <iostream>
using namespace std;

constexpr int square(int x) {
    return x * x;
}

int main() {
    constexpr int value = square(5);  // 在编译期计算
    cout << "Square: " << value << endl;
    return 0;
}