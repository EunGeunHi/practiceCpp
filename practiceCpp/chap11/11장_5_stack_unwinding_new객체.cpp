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

    delete v;  // 이 줄은 실행되지 않음!
}

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
