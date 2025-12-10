#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;
    if (a > b) {
        cout << "a is greater than b";
    } else if (a == b) {
        cout << "a is equal to b";
    } else {
        cout << "b is greater than a";
    }
    return 0;
}
