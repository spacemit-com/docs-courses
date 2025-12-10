#include <iostream>
using namespace std;

int main() {
    // 等价于：auto add = [](int a, int b) -> int { return a + b; };
    auto add = [](int a, int b) { return a + b; };
    cout << "Sum: " << add(10, 20) << endl;
    return 0;
}