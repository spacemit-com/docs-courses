#include <deque>
#include <iostream>
using namespace std;

int main() {
    deque<int> dq = {1, 2, 3, 4};
    dq.push_front(0);  // 在前端插入
    dq.push_back(5);   // 在后端插入

    for (int num : dq) {
        cout << num << " ";
    }
    return 0;
}
