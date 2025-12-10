#include <iostream>
using namespace std;

int main() {
    int x = 10, y = 20;

    auto add = [x, y]() { return x + y; };  // 捕获x和y
    cout << "Captured Sum: " << add() << endl;

    auto modify = [&x]() { x += 5; };  // 按引用捕获x
    modify();
    cout << "Modified x: " << x << endl;

    return 0;
}