

#include <iostream>
#include <string>

using namespace std;

class Car {
private:
    string manufacturer;
    string licensePlate;
    int speed;

    static int count;

public:
    Car() {
        manufacturer = "Unknown";
        licensePlate = "None";
        speed = 0;
        ++count;
        cout << "Default Constructor 호출" << endl;
    }

    Car(string manufacturer, string licensePlate, int speed) {
        this->manufacturer = manufacturer;
        this->licensePlate = licensePlate;
        this->speed = speed;
        ++count;
        cout << "Parameterized Constructor 호출" << endl;
    }

    ~Car() {
        cout << "Destructor 호출: " << manufacturer << " (" << licensePlate << ")" << endl;
        --count;
    }

    // setters
    Car& setManufacturer(const string& m) {
        manufacturer = m;
        return *this;
    }

    Car& setLicensePlate(const string& l) {
        licensePlate = l;
        return *this;
    }

    Car& setSpeed(int s) {
        speed = s;
        return *this;
    }

    void show() const {
        cout << "제조사: " << manufacturer
            << ", 번호판: " << licensePlate
            << ", 속도: " << speed << " km/h"
            << ", 전체 객체 수: " << count << endl;
    }

    static int getCount() {
        return count;
    }
};

// static 변수 정의
int Car::count = 0;

// ===================== main =====================
int main() {
    const int SIZE = 3;
    Car* carSet = new Car[SIZE];  // 힙에 Car 객체 배열 생성

    carSet[0].setManufacturer("Hyundai").setLicensePlate("12가3456").setSpeed(100);
    carSet[1].setManufacturer("Toyota").setLicensePlate("78나9012").setSpeed(120);
    carSet[2].setManufacturer("Kia").setLicensePlate("34다5678").setSpeed(90);

    cout << "\n=== Car 객체 정보 출력 ===" << endl;
    for (int i = 0; i < SIZE; ++i) {
        carSet[i].show();
    }

    cout << "\n현재 전체 Car 객체 수: " << Car::getCount() << endl;

    delete[] carSet;  // 소멸자 자동 호출

    cout << "\n객체 삭제 후 수: " << Car::getCount() << endl;

    return 0;
}
