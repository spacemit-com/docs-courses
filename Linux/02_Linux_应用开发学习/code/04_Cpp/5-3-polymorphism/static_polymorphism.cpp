#include <iostream>
using namespace std;

class Math {
   public:
    int add(int a, int b) { return a + b; }

    double add(double a, double b) { return a + b; }
};

int main() {
    Math math;
    cout << math.add(3, 4) << endl;      // 调用 int 版本
    cout << math.add(3.5, 4.5) << endl;  // 调用 double 版本
    return 0;
}