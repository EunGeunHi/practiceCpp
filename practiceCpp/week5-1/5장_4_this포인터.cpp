#include <iostream>
#include <string>

using namespace std;

class Car {
private:
    string manufacturer;    //char* manufacturer 과 차이점 
    int speed;

public:
    // 생성자에서 this 포인터 사용
    Car(string manufacturer, int speed) {
        this->manufacturer = manufacturer;  // this-> 사용
        this->speed = speed;
    }

    // Setter에서 this 포인터 사용
    Car& setManufacturer(string manufacturer) {
        this->manufacturer = manufacturer;
        return *this;  // this 포인터를 사용하여 객체 자신을 반환
    }

    Car& setSpeed(int speed) {
        this->speed = speed;
        return *this;
    }

    // 멤버 함수에서 this 포인터 사용
    void printCarInfo() {
        cout << "제조사: " << this->manufacturer << ", 속도: " << this->speed << " km/h" << endl;
    }
};

int main() {
    Car car1("Hyundai", 80);

    car1.setSpeed(100);
    // this 포인터 활용: Method Chaining
    car1.setManufacturer("Toyota").setSpeed(100).printCarInfo();

    return 0;
}
