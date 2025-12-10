#include <iostream>
#include <thread>
using namespace std;

void printMessage(const string& message) {
    cout << message << endl;
}

int main() {
    // 创建和管理线程
    thread t1(printMessage, "Hello from thread 1!");
    thread t2(printMessage, "Hello from thread 2!");
    // 等待线程完成
    t1.join();
    t2.join();
    return 0;
}