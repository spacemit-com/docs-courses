#include <iostream>
#include <vector>
using namespace std;

int main() {
    auto x = 10;       // 推导为int
    auto y = 3.14;     // 推导为double
    auto z = "Hello";  // 推导为const char*

    cout << x << ", " << y << ", " << z << endl;

    vector<int> vec = {1, 2, 3};
    for (auto elem : vec) {
        cout << elem << " ";
    }

    return 0;
}