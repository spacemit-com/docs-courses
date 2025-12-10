#include <iostream>
using namespace std;
class Vehicle {
   public:
    int wheels;

    void showWheels() { cout << "Wheels: " << wheels << endl; }
};

class Car : public Vehicle {
   public:
    string brand;

    void showBrand() { cout << "Brand: " << brand << endl; }
};

int main() {
    Car myCar;
    myCar.wheels = 4;
    myCar.brand = "Toyota";
    myCar.showWheels();
    myCar.showBrand();
    return 0;
}