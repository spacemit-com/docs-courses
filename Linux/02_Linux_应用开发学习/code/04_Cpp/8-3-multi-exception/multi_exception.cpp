#include <iostream>
#include <stdexcept>
using namespace std;

void test_function(int val) {
    if (val == 0) {
        throw runtime_error("Runtime error");
    } else if (val < 0) {
        throw invalid_argument("Negative value error");
    } else {
        cout << "Value is " << val << endl;
    }
}

int main() {
    try {
        test_function(0);  // 将抛出 runtime_error
    } catch (const runtime_error& e) {
        cout << "Caught runtime_error: " << e.what() << endl;
    } catch (const invalid_argument& e) {
        cout << "Caught invalid_argument: " << e.what() << endl;
    }

    try {
        test_function(-5);  // 将抛出 invalid_argument
    } catch (const runtime_error& e) {
        cout << "Caught runtime_error: " << e.what() << endl;
    } catch (const invalid_argument& e) {
        cout << "Caught invalid_argument: " << e.what() << endl;
    }

    return 0;
}