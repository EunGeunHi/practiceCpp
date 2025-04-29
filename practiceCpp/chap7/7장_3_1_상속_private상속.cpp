#include <iostream>
#include <cstring>
using namespace std;
class Vehicle {
public:
    void drive() { cout << "Driving...\n"; }
};

class Car : private Vehicle { // 🔒 private 상속
    //protected 상속도 upcasting 안됨
};
/*
private 상속이란?
Car 내부에서는 Vehicle을 사용할 수 있지만

Car 밖에서는 Car가 Vehicle이라는 사실을 감춘다.

즉, "Car is-a Vehicle"이 외부에서 보이지 않게 막힌 것이다.

upcasting(Car* → Vehicle*)은 "Car is-a Vehicle"이 전제 조건.
그런데 private 상속은 그 전제를 은닉하기 때문에 upcasting이 금지
*/
int main() {
    Car c;
     Vehicle* pv = &c; // ❌ 오류! private 상속이므로 upcasting 불가
                        // public상속은 가능
}
