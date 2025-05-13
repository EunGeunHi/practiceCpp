#include <iostream>
#include <cstring>
using namespace std;

// =========================
// Vehicle 추상 클래스
// =========================
class Vehicle {
protected:
    double engineSize;
    int speed;

public:
    Vehicle(double e = 0.0, int s = 0) : engineSize(e), speed(s) {}
    virtual ~Vehicle() {}
    virtual void show() const = 0;  // 순수 가상 함수 pure virtual function
    // =0 표기: 가상함수 선언만 하고 가상함수 body는 이 클래스에서 구현하지 않음
    // -> Vehicle 객체 생성할 수 없음! 즉 Vehicle을 추상 class로 한다는 것(9장)
};

// =========================
// Car 클래스
// =========================
class Car : public Vehicle {
private:
    char* model;
    int year;

public:
    Car(const char* m, int y, double e, int s)
        : Vehicle(e, s), year(y) {
        model = new char[strlen(m) + 1];
        strcpy(model, m);
    }

    ~Car() override {
        delete[] model;
    }

    void show() const override {    // virtual void show() //virtual void show() override //가능은하지만 헷갈리기에 virtual 선언은 base class에! 
        cout << "🚗 Car - Model: " << model << ", Year: " << year
            << ", Engine: " << engineSize << "L, Speed: " << speed << "km/h\n";
    }
};

// =========================
// Truck 클래스
// =========================
class Truck : public Vehicle {
private:
    double capacity;
    //동적 할당한것 없음 --> 소멸자 따로 필요 x
public:
    Truck(double e, int s, double c)
        : Vehicle(e, s), capacity(c) {}

    void show() const override {
        cout << "🚚 Truck - Capacity: " << capacity << " tons, Engine: "
            << engineSize << "L, Speed: " << speed << "km/h\n";
    }
};

// =========================
// 차량 저장소 클래스 (정적 배열 사용)
//   --> 중고차 등록, 삭제, 조회, 출력 하는 관리sw개발 == 클래스 구현
// =========================
class UsedVehicleStore {
private:
    Vehicle* table[10];  // 최대 10대 저장 -> 컨테이너  //정적할당..->stack영역 메모리 
    int count;

public:
    UsedVehicleStore() : count(0) {
        for (int i = 0; i < 10; ++i)
            table[i] = nullptr;
    }

    ~UsedVehicleStore() {
        for (int i = 0; i < count; ++i)
            delete table[i];  // 객체 메모리 해제
    }

    void add(Vehicle* v) {
        if (count < 10) {
            table[count++] = v;
        }
        else {
            cout << "저장소가 가득 찼습니다.\n";
        }
    }

    void showAll() const {
        cout << "\n[전체 차량 목록]\n";
        for (int i = 0; i < count; ++i) {
            table[i]->show();  // 🔥 동적 바인딩
        }
    }
    
    void delet(char* key);
    Vehicle* search(char* key);
};

// =========================
// 메인 함수
// =========================
int main() {
    UsedVehicleStore store;

    store.add(new Car("Avante", 2020, 1.6, 180));   //new-> heap영역 메모리
    store.add(new Car("K5", 2018, 2.0, 170));
    store.add(new Truck(5.0, 140, 12.0));
    store.add(new Truck(3.5, 130, 8.5));

    store.showAll();

    store.delet("현대");
    store.showAll();

    store.search("K5")->show();

    return 0;
}
//store 지역 변수-> 함수 종료후 메모리 해제 (stack은 자동반납. heap을 수동으로 반납해야함)


void UsedVehicleStore::delet(){

}
Vehicle* UsedVehicleStore::search(char* key){

}



/*
enum Menu{}
main에서 switch-case문
스켈레톤 코드 없을 것

main에서 사용할 함수로 구현(4)

class에서 멤버함수 구현(5)- 객체 지향


class Person{
    char*name
    int id
}
class Student: Peron{
    char* dept;
}
class Employee: Person{
    char*work;
    int salary;
}
class Work-Student: Student, Employee{
    int month;
}
    //다야몬드 상속-> virtual class 유의

*/