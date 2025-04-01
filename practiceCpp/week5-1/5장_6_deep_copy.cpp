#include <iostream>
#include <cstring>

using namespace std;
class Car {
private:
    char* manufacturer;
    int speed;

public:
    // 기본 생성자 (Default Constructor)
    Car() {
        manufacturer = new char[8];
        strcpy(manufacturer, "Unknown");
        speed = 0;
        cout << "Default Constructor 호출" << endl;
    }

    // 일반 생성자 (Parameterized Constructor)
    Car(const char* manufacturer, int speed) {
        this->manufacturer = new char[strlen(manufacturer) + 1];
        strcpy(this->manufacturer, manufacturer);
        this->speed = speed;
        cout << "Parameterized Constructor 호출" << endl;
    }

    // 복사 생성자 (Deep Copy Implementation)
    Car(const Car& other) {
        this->manufacturer = new char[strlen(other.manufacturer) + 1];
        strcpy(this->manufacturer, other.manufacturer);
        this->speed = other.speed;
        cout << "Copy Constructor 호출 (Deep Copy)" << endl;
    }

    // 소멸자 (Destructor)
    ~Car() {
        cout << "Destructor 호출: " << manufacturer << endl;
        delete[] manufacturer;
    }

    // Setter에서 this 포인터 사용 (Method Chaining)
    Car& setManufacturer(const char* manufacturer) {
        delete[] this->manufacturer; // 기존 메모리 해제
        this->manufacturer = new char[strlen(manufacturer) + 1];
        strcpy(this->manufacturer, manufacturer);
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
    cout << "=== Default Constructor 실습 ===" << endl;
    Car car1; // 기본 생성자 호출
    car1.printCarInfo();

    cout << "\n=== Parameterized Constructor 실습 ===" << endl;
    Car car2("Hyundai", 80); // 일반 생성자 호출
    car2.printCarInfo();

    cout << "\n=== Copy Constructor 실습 ===" << endl;
    Car car3 = car2; // 복사 생성자 호출 (Deep Copy)
    car3.printCarInfo();

    cout << "\n=== Method Chaining 실습 ===" << endl;
    car2.setManufacturer("Toyota").setSpeed(100).printCarInfo();

    int num;
    cin >> num;
    return 0; // 소멸자 자동 호출
}
