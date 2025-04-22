#include <iostream>
#include <cstring>
using namespace std;

class Vehicle {
protected:
    double engineSize;
    int speed;

public:
    Vehicle(double e = 0.0, int s = 0) : engineSize(e), speed(s) {}

    // 복사 생성자
    Vehicle(const Vehicle& other) : engineSize(other.engineSize), speed(other.speed) {
        cout << "Vehicle 복사 생성자 호출됨" << endl;
    }

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
    // 일반 생성자
    Car(const char* m = "", const char* md = "", double e = 0.0, int s = 0)
        : Vehicle(e, s) {
        manufacturer = new char[strlen(m) + 1];
        strcpy(manufacturer, m);
        model = new char[strlen(md) + 1];
        strcpy(model, md);
        cout << "Car 생성자 호출됨: " << manufacturer << ", " << model << endl;
    }

    // 복사 생성자
    Car(const Car& other) : Vehicle(other) {
        manufacturer = new char[strlen(other.manufacturer) + 1];
        strcpy(manufacturer, other.manufacturer);
        model = new char[strlen(other.model) + 1];
        strcpy(model, other.model);
        cout << "Car 복사 생성자 호출됨" << endl;
    }

    // 복사 대입 연산자
    Car& operator=(const Car& other) {
        if (this != &other) {
            Vehicle::operator=(other);
            delete[] manufacturer;
            delete[] model;
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
        cout << "Car 소멸자 호출됨: " << manufacturer << ", " << model << endl;
        delete[] manufacturer;
        delete[] model;
    }

    void show() const {
        Vehicle::show();
        cout << ", Manufacturer: " << manufacturer
            << ", Model: " << model << endl;
    }
};

// 📌 Car 객체를 값으로 전달하고 반환 → 복사 생성자 호출 확인
Car NextTest(Car c) {   //call by value : 복사 생성자 호출
    cout << "[NextTest 함수 내부 실행 중]" << endl;
    c.show();
    return c;  // 복사 생성자 호출 가능 (컴파일러에 따라 생략될 수도 있음)
     //return by value : 복사 생성자 자동 호출
}
int main() {
    // [1] 일반 생성자
    Car c1("Hyundai", "Sonata", 2.0, 180);

    // [2] 복사 생성자
    Car c2 = c1;

    // [3] manufacturer만 주는 기본 생성자 (나머지 기본값)
    Car c3("Kia");

    // [4] NextTest 함수 테스트: 값 전달 + 값 반환 (복사 생성자 호출 1~2번)
    Car c4 = NextTest(c3);  // 복사 생성자 호출 (인자 전달 시) → 복사 생성자 or RVO (리턴 시)
   

    // [5] show로 객체 상태 확인
    c1.show(); c2.show(); c3.show(); c4.show();

    // [6] 대입 연산자 테스트: 임시 객체를 반환받아 기존 객체 c5에 대입
    Car c5;
    c5 = NextTest(c3);  // 복사 생성자 호출 (함수 인자) → 대입 연산자 호출 (함수 리턴 값 → c5)

    c5.show();
}
