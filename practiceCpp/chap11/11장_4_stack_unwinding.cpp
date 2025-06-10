#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// ==============================
// 클래스 정의: 소멸자 출력용
// ==============================
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

// ==============================
// 함수 체인 정의
// ==============================
void showVehicle() {
    Vehicle v;
    cout << "[showVehicle] 동작 중..." << endl;

    // 예외 발생 지점
    throw runtime_error("showVehicle에서 예외 발생!");
}

void showAnimal() {
    Animal a;
    cout << "[showAnimal] 동작 중..." << endl;
    showVehicle(); // 예외 발생 지점으로 호출
}

void showPerson() {
    Person p;
    cout << "[showPerson] 동작 중..." << endl;
    showAnimal();
}

// ==============================
// main 함수: 최종 예외 처리
// ==============================
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
