#include <iostream>
using namespace std;

int main() {
    for (int i = 0; i < 5; i++) {
        if (i == 3)
            break;  // 跳出循环
        if (i == 1)
            continue;  // 跳过1的迭代
        cout << i << " ";
    }
    return 0;
}