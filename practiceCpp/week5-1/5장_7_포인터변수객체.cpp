#include <iostream>
#include <cstring> // strcpy, strlen 사용

using namespace std;

class Car {
private:
    char* manufacturer;
    int speed;

public:
    // 기본 생성자 (Default Constructor)
    Car() {
        manufacturer = new char[8]; // "Unknown"을 저장할 충분한 크기
        strcpy(manufacturer, "Unknown");
        speed = 0;
        cout << "Default Constructor 호출" << endl;
    }

    // 일반 생성자 (Parameterized Constructor)
    Car(const char* manufacturer, int speed) {
        this->manufacturer = new char[strlen(manufacturer) + 1]; // 문자열 크기만큼 동적 할당
        strcpy(this->manufacturer, manufacturer);
        this->speed = speed;
        cout << "Parameterized Constructor 호출" << endl;
    }

    // 복사 생성자 (깊은 복사)
    Car(const Car& other) {
        this->manufacturer = new char[strlen(other.manufacturer) + 1]; // 새 메모리 할당
        strcpy(this->manufacturer, other.manufacturer);
        this->speed = other.speed;
        cout << "Copy Constructor 호출" << endl;
    }

    // 소멸자 (Destructor)
    ~Car() {
        cout << "Destructor 호출: " << manufacturer << endl;
        delete[] manufacturer; // 동적 할당된 메모리 해제
    }

    // Setter에서 this 포인터 사용 (Method Chaining)
    Car& setManufacturer(const char* manufacturer) {
        delete[] this->manufacturer; // 기존 메모리 해제
        this->manufacturer = new char[strlen(manufacturer) + 1]; // 새로운 메모리 할당
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
    Car* car1 = new Car(); // 기본 생성자 호출
    car1->printCarInfo();

    cout << "\n=== Parameterized Constructor 실습 ===" << endl;
    Car* car2 = new Car("Hyundai", 80); // 일반 생성자 호출
    car2->printCarInfo();

    cout << "\n=== Copy Constructor 실습 ===" << endl;
    Car* car3 = new Car(*car2); // 복사 생성자 호출
    car3->printCarInfo();

    cout << "\n=== Method Chaining 실습 ===" << endl;
    car2->setManufacturer("Toyota").setSpeed(100).printCarInfo();

    // 동적 할당된 객체를 삭제 (소멸자 호출됨)
    delete car1;
    delete car2;
    delete car3;

    //난이도 상 - 고급과정
    Car* carSet = new Car[10]; //10개의 객체를 생성 - Car()를 호출 //기본 생성자를 만들어둬야 가능 //point of array->포인터 하나
    carSet[0].setManufacturer("Toyota");
    carSet[1].setSpeed(120);
    carSet[2].printCarInfo();

    //Car* carSet = new Car[10]("Hyundai", 100); // 에러

    Car* carSet2[10];   //array of pointer->포인터 여러개
    for (int i = 0; i < 10; ++i) {
        carSet2[i] = new Car("Hyundai", 100 + i * 10); // 각각 생성자 호출
    }

    for (int i = 0; i < 10; ++i)
        delete carSet2[i];

    int num;
    cin >> num;

    return 0;
}

//Car carSet3[10];같은 경우 stack에 너무큰 공간 사용.피해야할 코드