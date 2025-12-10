#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> lst = {1, 2, 3, 4};
    lst.push_back(5);
    lst.push_front(0);

    for (int num : lst) {
        cout << num << " ";
    }
    return 0;
}
