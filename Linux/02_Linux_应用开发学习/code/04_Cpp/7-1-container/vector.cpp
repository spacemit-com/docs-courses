#include <iostream>
#include <vector>
using namespace std;

int main() {
    // 创建一个空的vector
    vector<int> nums;

    // 向vector中添加元素
    nums.push_back(10);
    nums.push_back(20);
    nums.push_back(30);

    // 访问元素
    cout << "First element: " << nums[0] << endl;
    cout << "Second element: " << nums.at(1) << endl;

    // 输出所有元素
    for (int num : nums) {
        cout << num << " ";
    }
    return 0;
}
