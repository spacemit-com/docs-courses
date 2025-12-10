#include <iostream>
using namespace std;

int main() {
    auto multiply = [](auto a, auto b) { return a * b; };
    cout << multiply(2, 3) << endl;      // 输出6
    cout << multiply(1.5, 2.5) << endl;  // 输出3.75
    return 0;
}