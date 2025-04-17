#include <iostream>
#include <cstring>
using namespace std;

class Vehicle {
protected:
    double engineSize;
    int speed;

public:
    Vehicle(double e = 0.0, int s = 0) : engineSize(e), speed(s) {}

    // 복사 대입 연산자
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
        manufacturer = new char[strlen(m) + 1]; //deep copy
        strcpy(manufacturer, m);

        model = new char[strlen(md) + 1];
        strcpy(model, md);
    }

    // 복사 대입 연산자
    Car& operator=(const Car& other) {
        if (this != &other) {
            Vehicle::operator=(other);  // 🔸 기본 클래스 부분 복사

            // 기존 메모리 해제
            delete[] manufacturer;
            delete[] model;

            // 문자열 깊은 복사
            manufacturer = new char[strlen(other.manufacturer) + 1];
            strcpy(manufacturer, other.manufacturer);

            model = new char[strlen(other.model) + 1];
            strcpy(model, other.model);
        }
        cout << "Car::operator= 호출됨" << endl;
        return *this;
    }

    // 소멸자
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

    cout << "\n대입 연산 실행: c2 = c1;" << endl;
    c2 = c1;  // 복사 대입 연산자 호출

    cout << "\n복사 후 상태:" << endl;
    c1.show();
    c2.show();

    return 0;
}
