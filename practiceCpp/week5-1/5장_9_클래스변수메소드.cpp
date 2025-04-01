#include <iostream>
#include <cstring>

using namespace std;

class Car {
private:
    char* manufacturer;
    int speed;

    static int count;

public:
    static int getCarCount() {
        return count;
    }

    Car() {
        manufacturer = new char[8];
        strcpy(manufacturer, "Unknown");
        speed = 0;
        ++count;
        cout << "Default Constructor 호출" << endl;
    }

    Car(const char* manufacturer, int speed) {
        this->manufacturer = new char[strlen(manufacturer) + 1];
        strcpy(this->manufacturer, manufacturer);
        this->speed = speed;
        ++count;
        cout << "Parameterized Constructor 호출" << endl;
    }

    Car(const Car& other) {
        this->manufacturer = new char[strlen(other.manufacturer) + 1];
        strcpy(this->manufacturer, other.manufacturer);
        this->speed = other.speed;
        ++count;
        cout << "Copy Constructor 호출" << endl;
    }

    ~Car() {
        cout << "Destructor 호출: " << manufacturer << endl;
        delete[] manufacturer;
        --count;
    }

    Car& setManufacturer(const char* manufacturer) {
        delete[] this->manufacturer;
        this->manufacturer = new char[strlen(manufacturer) + 1];
        strcpy(this->manufacturer, manufacturer);
        return *this;
    }

    Car& setSpeed(int speed) {
        this->speed = speed;
        return *this;
    }

    void showCars() const {
        cout << "제조사: " << manufacturer
            << ", 속도: " << speed << " km/h"
            << ", 현재 Car 객체 수: " << count << endl;
    }
};

int Car::count = 0;

// ===================== main =====================
int main() {
    const int SIZE = 5;

    // Car 객체 배열을 포인터 변수로 관리 (heap에 배열 생성)
    Car* carSet = new Car[SIZE]; // Default Constructor 5번 호출됨

    // 일부 객체 정보 설정 및 출력
    carSet[0].setManufacturer("Hyundai").setSpeed(100);
    carSet[1].setManufacturer("Toyota").setSpeed(120);
    carSet[2].setManufacturer("Kia").setSpeed(90);

    cout << "\n=== carSet[i].showCars() ===" << endl;
    for (int i = 0; i < SIZE; ++i) {
        carSet[i].showCars();  // 객체 정보 및 전체 객체 수 출력
    }

    cout << "\n현재 전체 Car 객체 수: " << Car::getCarCount() << endl;

    // 메모리 해제
    delete[] carSet;  // 모든 객체의 소멸자 자동 호출됨

    cout << "Car 객체 모두 삭제 후 수: " << Car::getCarCount() << endl;

    return 0;
}
