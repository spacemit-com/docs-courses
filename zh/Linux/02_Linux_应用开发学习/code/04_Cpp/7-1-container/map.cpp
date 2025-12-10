#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string, int> m;
    // 插入元素
    m["apple"] = 3;
    m["banana"] = 5;
    for (auto& pair : m) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // 删除元素
    m.erase("apple");
    for (auto& pair : m) {
        cout << pair.first << ": " << pair.second << endl;
    }
    return 0;
}