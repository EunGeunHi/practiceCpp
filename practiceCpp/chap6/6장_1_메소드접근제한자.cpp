//6장_1_메소드접근제한자.cpp

#include <iostream>
#include <cstring>

using namespace std;

class Car {
private:
    char* manufacturer;
    int speed;

    static int count;

    // [1] Private 메서드 추가: 속도 유효성 검사
    bool isValidSpeed(int speed) const {
        return speed >= 0 && speed <= 300;
    }

public:
    // [3] Getter 메서드
    const char* getManufacturer() const {
        return manufacturer;
    }

    int getSpeed() const {
        return speed;
    }

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

    // [2] Private 메서드 호출 적용
    Car& setSpeed(int speed) {
        if (isValidSpeed(speed)) {
            this->speed = speed;
        }
        else {
            cout << "유효하지 않은 속도입니다. (0~300 km/h)\n";
            this->speed = 0;  // 기본값
        }
        return *this;
    }

    void showCars() const {
        cout << "제조사: " << manufacturer
            << ", 속도: " << speed << " km/h"
            << ", 현재 Car 객체 수: " << count << endl;
    }
    void compareSpeed(const Car& other) const;
};
void Car::compareSpeed(const Car& other) const {
    if (this->speed > other.speed)
        cout << manufacturer << "가 " << other.getManufacturer() << "보다 빠릅니다.\n";
    else if (this->speed < other.speed)
        cout << manufacturer << "가 " << other.getManufacturer() << "보다 느립니다.\n";
    else
        cout << manufacturer << "와 " << other.getManufacturer() << "의 속도가 같습니다.\n";
}

int Car::count = 0;

int main() {
    const int SIZE = 5;

    Car* carSet = new Car[SIZE]; // Default Constructor 5번 호출

    carSet[0].setManufacturer("현대").setSpeed(100);
    carSet[1].setManufacturer("토요타").setSpeed(120);
    carSet[2].setManufacturer("기아").setSpeed(-50);  // 유효하지 않은 속도 → 경고 출력

    cout << "\n=== carSet[i].showCars() ===" << endl;
    for (int i = 0; i < SIZE; ++i) {
        carSet[i].showCars();
    }

    cout << "\n현재 전체 Car 객체 수: " << Car::getCarCount() << endl;

    //[추가] Getter 사용 예시
    cout << "\n--- Getter 메서드 사용 예시 ---\n";
    cout << "carSet[0] 제조사: " << carSet[0].getManufacturer() << endl;
    cout << "carSet[1] 속도: " << carSet[1].getSpeed() << " km/h" << endl;
    cout << "\n--- compareSpeed() 테스트 ---\n";
    carSet[0].compareSpeed(carSet[1]);  // 현대 vs 토요타
    carSet[1].compareSpeed(carSet[2]);  // 토요타 vs 기아

    //[추가] Setter 사용 예시
    cout << "\n--- Setter 메서드로 값 수정 ---\n";
    carSet[3].setManufacturer("BMW");
    carSet[3].setSpeed(250);
    carSet[4].setManufacturer("Tesla").setSpeed(280);

    cout << "\n=== 수정된 carSet[3]~[4] 출력 ===" << endl;
    carSet[3].showCars();
    carSet[4].showCars();

    // 객체 수 재확인
    cout << "\n현재 전체 Car 객체 수: " << Car::getCarCount() << endl;

    delete[] carSet;  // 소멸자 호출

    cout << "Car 객체 모두 삭제 후 수: " << Car::getCarCount() << endl;
    int choice;
    cin >> choice;
    return 0;
}