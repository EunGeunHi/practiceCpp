#include <iostream>
#include <cstring>
using namespace std;

class Vehicle {
protected:
    double engineSize;
    int speed;

public:
    Vehicle(double e = 0.0, int s = 0) : engineSize(e), speed(s) {}

    Vehicle& operator=(const Vehicle& other) {
        if (this != &other) {
            engineSize = other.engineSize;
            speed = other.speed;
        }
        cout << "Vehicle::operator= 호출됨" << endl;
        return *this;
    }

    void show() const {
        cout << "Engine: " << engineSize << "L, Speed: " << speed << "km/h";
    }
};

class Car : public Vehicle {
private:
    char* manufacturer;
    char* model;

public:
    Car(const char* m = "", const char* md = "", double e = 0.0, int s = 0)
        : Vehicle(e, s) {
        manufacturer = new char[strlen(m) + 1];
        strcpy(manufacturer, m);

        model = new char[strlen(md) + 1];
        strcpy(model, md);
    }

    // 얕은 복사: 포인터만 복사함 (dangling reference 위험)
    Car& operator=(const Car& other) {
        if (this != &other) {
            Vehicle::operator=(other);

            // ⚠ 기존 메모리 해제 없이 포인터만 복사
            manufacturer = other.manufacturer;
            model = other.model;
        }
        cout << "Car::얕은 복사 operator= 호출됨" << endl;
        return *this;
    }

    ~Car() {
        delete[] manufacturer;
        delete[] model;
    }

    void show() const {
        Vehicle::show();
        cout << ", Manufacturer: " << manufacturer
            << ", Model: " << model << endl;
    }
};

int main() {
    Car c1("Hyundai", "Sonata", 2.0, 180);
    Car c2("Kia", "K5", 1.6, 170);

    cout << "초기 상태:" << endl;
    c1.show();
    c2.show();

    cout << "\n얕은 복사 실행: c2 = c1;" << endl;
    c2 = c1;  // 얕은 복사 수행

    cout << "\n복사 후 상태:" << endl;
    c1.show();
    c2.show();

    cout << "\nmain 종료: 소멸자 실행" << endl;
    return 0;
}
