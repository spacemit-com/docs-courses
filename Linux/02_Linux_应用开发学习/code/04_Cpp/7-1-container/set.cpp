#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s = {5, 1, 2, 4, 3};
    s.insert(6);  // 插入元素
    for (int num : s) {
        cout << num << " ";  // 自动按升序排列
    }
    cout << endl;

    s.erase(1);  // 删除元素
    for (int num : s) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}