#include <iostream>
#include <string>
using namespace std;

class Car {
private:
    string manufacturer;

public:
    Car(const string& manufacturer) : manufacturer(manufacturer) {}

    // 부작용 발생: 한 객체의 제조사를 다른 객체로 덮어씀
    void setManufacturerFrom(Car& other) {
        manufacturer = other.manufacturer;  // 다른 객체의 문자열을 직접 덮어씀
    }

    void show() const {
        cout << "제조사: " << manufacturer << endl;
    }
    const string& getManufacturer() const {
        return manufacturer;  // 문제 발생: 지역 객체의 참조 반환
    }
};

int main() {
    Car car1("Hyundai");
    Car car2("Toyota");

    car1.setManufacturerFrom(car2);  // car1 제조사가 car2의 제조사로 덮어짐 (side effect)

    car1.show();  // Toyota로 출력됨, car1이 car2의 제조사를 공유함

    Car& ref1 = car1;  // car1에 대한 참조
    Car& ref2 = car2;  // car2에 대한 참조

    ref1.setManufacturer("BMW");  // car1의 제조사 변경
    ref2 = ref1;  // ref2가 ref1을 참조하게 되어, car2의 제조사가 car1과 동일해짐

    car2.show();  // BMW로 출력됨, car2와 car1이 동일한 제조사 값을 가지게 됨

    const string& name = Car("Genesis").getManufacturer();  // 💥 참조가 죽을 때 오류 발생
    cout << "제조사: " << name << endl;  // 쓰레기 값이 출력됨
}


