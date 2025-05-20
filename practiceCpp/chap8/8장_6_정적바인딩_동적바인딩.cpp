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

    virtual void show() const = 0; //  동적 바인딩
    void print() const { //  정적 바인딩
        cout << "[Vehicle] Engine: " << engineSize << "L, Speed: " << speed << "km/h\n";
    }
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

    void show() const override { //  동적 바인딩
        cout << " Car - Model: " << model << ", Year: " << year
            << ", Engine: " << engineSize << "L, Speed: " << speed << "km/h\n";
    }

    void print() const { //  정적 바인딩
        cout << "[Car] Model: " << model << ", Year: " << year << '\n';
    }
};

// =========================
// Truck 클래스
// =========================
class Truck : public Vehicle {
private:
    double capacity;

public:
    Truck(double e, int s, double c)
        : Vehicle(e, s), capacity(c) {}

    void show() const override { //  동적 바인딩
        cout << " Truck - Capacity: " << capacity << " tons, Engine: "
            << engineSize << "L, Speed: " << speed << "km/h\n";
    }

    void print() const { // 정적 바인딩
        cout << "[Truck] Capacity: " << capacity << " tons\n";
    }
};

// class Bus : public Vehicle { //subclassing
// private:
//     char* company;
//     int passengers

// public:
//     Bus(double e, int s, char* co, int p)
//         : Vehicle(e, s), passengers(p) {
//         company = new char[strlen(co)+1];
//         strcpy(model,m);   
//         }
//     ~Bus()override{
//         delete[] company;
//     }

//     void show() const override { //  동적 바인딩
//         cout << " Bus - company: " << company << " tons, Engine: "
//             << engineSize << "L, Speed: " << speed << "km/h\n";
//     }

//     void print() const { // 정적 바인딩
//         cout << "[Truck] Capacity: " << capacity << " tons\n";
//     }
// };

// =========================
// 차량 저장소 클래스
// =========================
class UsedVehicleStore {
private:
    Vehicle* table[10];
    int count;

public:
    UsedVehicleStore() : count(0) {
        for (int i = 0; i < 10; ++i)
            table[i] = nullptr;
    }

    ~UsedVehicleStore() {
        for (int i = 0; i < count; ++i)
            delete table[i];
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
        cout << "\n [동적 바인딩: show() 호출 결과]\n";
        for (int i = 0; i < count; ++i)
            table[i]->show();  // 동적 바인딩
    }

    void printAll() const {
        cout << "\n [정적 바인딩: print() 호출 결과]\n";
        for (int i = 0; i < count; ++i)
            table[i]->print();  // 정적 바인딩 (Vehicle::print 호출됨!)
    }


    bool VehicleDelete(char*name);
    bool update(char*carname, char* newName);
    Vehicle& search(char* name);
};

// =========================
// 메인 함수
// =========================
int main() {
    UsedVehicleStore store;

    store.add(new Car("Avante", 2020, 1.6, 180));
    store.add(new Car("K5", 2018, 2.0, 170));
    store.add(new Truck(5.0, 140, 12.0));
    store.add(new Truck(3.5, 130, 8.5));
    //store.add(new Bus())  //subcalssing

    store.showAll();   //  동적 바인딩으로 Car::show(), Truck::show()   //compile타임에 결정됨
    store.printAll();  //  정적 바인딩으로 Vehicle::print()만 호출됨

    return 0;
}