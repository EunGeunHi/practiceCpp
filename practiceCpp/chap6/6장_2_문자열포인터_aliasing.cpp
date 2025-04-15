//6장_2_문자열포인터_aliasing 
#include <iostream>
#include <cstring>
using namespace std;

class Car {
private:
    char* manufacturer;
    int speed;

public:
    Car(const char* m, int s) {
        manufacturer = new char[strlen(m) + 1];
        strcpy(manufacturer, m);
        speed = s;
    }

    ~Car() {
        delete[] manufacturer;
    }

    int getSpeed() const { return speed; }
    const char* getManufacturer() const { return manufacturer; }

    void setSpeed(int s) { speed = s; }

    void show() const {
        cout << "제조사: " << manufacturer << ", 속도: " << speed << " km/h" << endl;
    }
};

// [Side Effect 예제 함수]
void boostSpeed(Car& car, int factor) {
    int newSpeed = car.getSpeed() * factor;
    car.setSpeed(newSpeed);
    cout << "[boostSpeed()] 속도 상승! 현재 속도: " << car.getSpeed() << " km/h" << endl;
}
// Dangling reference example 1
Car& getNewCar1() {
    Car temp("Ford", 90);
    return temp;
}

// Dangling reference example 2
Car& getNewCar2() {
    Car* temp = new Car("Mazda", 110);
    delete temp;
    return *temp;
}

int main() {
    Car myCar("Hyundai", 100);

    cout << "🚗 원래 상태:\n";
    myCar.show();

    //side effects 문제 발생
    cout << "\n⚙️ boostSpeed() 호출: 속도 2배 상승\n";
    boostSpeed(myCar, 2);  // side effect: myCar 속도가 내부에서 수정됨

    cout << "\n🚗 변경 후 상태:\n";
    myCar.show();

    //aliasing 문제
    Car guestCar("기아", 120);
    Car& demoCar = myCar;
    demoCar = guestCar;//demoCar를 myCar에서 guestCar로 변경
    myCar.show();//myCar가 변경되는 aliasing 문제 발생 > 해결 방법은?


    // dangling reference
    cout << "\ndangling 참조 테스트 1 (지역 변수 반환):" << endl;
    Car& badRef1 = getNewCar1();  // 위험한 참조
    badRef1.show();

    cout << "\ndangling 참조 테스트 2 (delete 후 참조 반환):" << endl;
    Car& badRef2 = getNewCar2();  // 위험한 참조
    badRef2.show();
    return 0;
}
