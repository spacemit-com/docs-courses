#include <iostream>
#include <stdexcept>
using namespace std;

void throw_runtime_error() {
    throw runtime_error("Runtime error occurred");
}

int main() {
    try {
        throw_runtime_error();
    } catch (const runtime_error& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    return 0;
}