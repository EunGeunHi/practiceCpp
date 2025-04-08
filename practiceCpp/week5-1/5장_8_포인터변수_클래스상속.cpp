//맛보기
#include <iostream>
#include <cstring>

using namespace std;

// ===================== 상위 클래스 =====================
class Vehicle {
protected:
    string licensePlateNumber;
    double engineCapacity;

public:
    Vehicle(const string& plate = "Unknown", double capacity = 0.0)
        : licensePlateNumber(plate), engineCapacity(capacity) {
        cout << "Vehicle 생성자 호출" << endl;
    }

    virtual void show() {
        cout << "[Vehicle] 번호판: " << licensePlateNumber
            << ", 엔진 용량: " << engineCapacity << "L" << endl;
    }

    virtual ~Vehicle() {
        cout << "Vehicle 소멸자 호출" << endl;
    }
};

// ===================== 하위 클래스 =====================
class Car : public Vehicle {
private:
    char* manufacturer;
    int speed;

public:
    // 기본 생성자
    Car()
        : Vehicle("Unknown", 0.0), speed(0) {
        manufacturer = new char[8];
        strcpy(manufacturer, "Unknown");
        cout << "Car 기본 생성자 호출" << endl;
    }

    // 일반 생성자
    Car(const char* manufacturer, int speed, const string& plate, double capacity)
        : Vehicle(plate, capacity), speed(speed) {
        this->manufacturer = new char[strlen(manufacturer) + 1];
        strcpy(this->manufacturer, manufacturer);
        cout << "Car 생성자 호출" << endl;
    }

    // 복사 생성자
    Car(const Car& other)
        : Vehicle(other.licensePlateNumber, other.engineCapacity), speed(other.speed) {
        this->manufacturer = new char[strlen(other.manufacturer) + 1];
        strcpy(this->manufacturer, other.manufacturer);
        cout << "Car 복사 생성자 호출" << endl;
    }

    // 소멸자
    ~Car() override {
        cout << "Car 소멸자 호출: " << manufacturer << endl;
        delete[] manufacturer;
    }

    // 오버라이딩된 show 함수
    void show() override {
        cout << "[Car] 제조사: " << manufacturer
            << ", 속도: " << speed << " km/h, "
            << "번호판: " << licensePlateNumber
            << ", 엔진 용량: " << engineCapacity << "L" << endl;
    }
};

// ===================== 메인 =====================
int main() {
    const int SIZE = 3;
    Vehicle* vehicles[SIZE];

    vehicles[0] = new Car("Hyundai", 120, "123가4567", 1.6);
    vehicles[1] = new Car("Toyota", 140, "456나7890", 2.0);
    vehicles[2] = new Car("Kia", 100, "789다1234", 1.4);

    cout << "\n=== polymorphism 테스트: show() 호출 ===" << endl;
    for (int i = 0; i < SIZE; ++i) {
        vehicles[i]->show();  // 동적 바인딩 (Car::show)
    }

    cout << "\n=== 메모리 해제 ===" << endl;
    for (int i = 0; i < SIZE; ++i) {
        delete vehicles[i];
    }

    int num;
    cin >> num;
    return 0;
}
