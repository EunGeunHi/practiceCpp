#include <iostream>
#include <cstring>
using namespace std;

class Vehicle {
protected:
    double engineSize;
    int speed;

public:
    Vehicle(double e = 0.0, int s = 0) : engineSize(e), speed(s) {}
    virtual ~Vehicle() {  // 가상 소멸자
        cout << "Vehicle destroyed\n";
    }

    virtual void show() const {
        cout << "Vehicle - Engine: " << engineSize << "L, Speed: " << speed << "km/h" << endl;
    }
};

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
        cout << "Car destroyed\n";
    }

    void show() const override {
        cout << "Car - Model: " << model << ", Year: " << year << ", ";
        Vehicle::show();
    }
};

class Truck : public Vehicle {
private:
    double capacity;

public:
    Truck(double e, int s, double c)
        : Vehicle(e, s), capacity(c) {}

    ~Truck() override {
        cout << "Truck destroyed\n";
    }

    void show() const override {
        cout << "Truck - Capacity: " << capacity << " tons, ";
        Vehicle::show();
    }
};

// ✅ 동적 바인딩을 활용하여 객체 출력
void printVehicles(Vehicle* arr[], int size) {
    cout << "[Vehicle 목록 출력: 동적 바인딩]" << endl;
    for (int i = 0; i < size; ++i) {
        if (arr[i]) arr[i]->show();  // 🔥 부모 포인터가 자식 객체를 가리킴
    }
}

// ✅ 메모리 해제를 함수로 분리
void freeVehicles(Vehicle* arr[], int size) {
    for (int i = 0; i < size; ++i) {
        delete arr[i];  // 🔥 가상 소멸자가 제대로 작동해야 자식 소멸자도 호출됨
        arr[i] = nullptr;
    }
}

int main() {
    Vehicle* table[10] = { nullptr };

    table[0] = new Car("Avante", 2020, 1.6, 180);
    table[1] = new Car("K5", 2019, 2.0, 170);
    table[2] = new Truck(5.0, 140, 15.0);
    table[3] = new Truck(3.5, 120, 8.0);

    printVehicles(table, 4);   // 🔍 다형성 테스트
    freeVehicles(table, 4);    // ✅ 가상 소멸자 호출

    return 0;
}
