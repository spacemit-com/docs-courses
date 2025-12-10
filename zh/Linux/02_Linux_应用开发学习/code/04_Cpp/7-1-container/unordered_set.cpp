#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    unordered_set<int> us = {5, 1, 2, 4, 3};
    us.insert(6);

    for (int num : us) {
        cout << num << " ";  // 元素顺序不固定
    }
    return 0;
}