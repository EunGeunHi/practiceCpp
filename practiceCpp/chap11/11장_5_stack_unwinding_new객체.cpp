#include <iostream>
#include <stdexcept>
using namespace std;

class Vehicle {
public:
    Vehicle() { cout << "🚗 Vehicle 객체 생성" << endl; }
    ~Vehicle() { cout << "🚗 Vehicle 객체 소멸" << endl; }
};

class Animal {
public:
    Animal() { cout << "🐶 Animal 객체 생성" << endl; }
    ~Animal() { cout << "🐶 Animal 객체 소멸" << endl; }
};

class Person {
public:
    Person() { cout << "👤 Person 객체 생성" << endl; }
    ~Person() { cout << "👤 Person 객체 소멸" << endl; }
};

// =========================
// 동적 객체를 사용하는 show 함수들
// =========================
void showVehicle() {
    Vehicle* v = new Vehicle();  // 동적 생성
    cout << "[showVehicle] 동작 중..." << endl;

    throw runtime_error("showVehicle에서 예외 발생!");

    delete v;  // 이 줄은 실행되지 않음!: 소멸자 호출 안됨
}//포인터 v는 반환하지만 new메모리 할당된 v*는 반환되지 않았음-> 힙에 남아 있

void showAnimal() {
    Animal* a = new Animal();  // 동적 생성
    cout << "[showAnimal] 동작 중..." << endl;

    showVehicle();  // 예외 발생 시 delete a는 호출되지 않음!

    delete a;
}

void showPerson() {
    Person* p = new Person();  // 동적 생성
    cout << "[showPerson] 동작 중..." << endl;

    showAnimal();  // 예외 발생 시 delete p는 호출되지 않음!

    delete p;
}

int main() {
    try {
        cout << "[main] 시작" << endl;
        showPerson();
    }
    catch (const exception& e) {
        cerr << "[예외 처리] " << e.what() << endl;
    }

    cout << "[main] 종료" << endl;
    return 0;
}

//해결법: 스마트 포인터
/*
Vehicle* v = new Vehicle();
수동으로 할당, 해제
=>
unique_ptr<Vehicle> v = make_unique<Vehicle>();
1.v가 스코프 벗어나면 자동으로 delete
2.단독 소유(하나의 포인터만 개체를 소유)
*/