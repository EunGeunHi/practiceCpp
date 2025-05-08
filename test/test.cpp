//6��_1_�޼ҵ�����������.cpp
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

using namespace std;
const int MAX_SIZE = 100;


class Vehicle{
private:
    char* manufacturer;
    char* model;
    int price;
protected:
    static char* copyString(const char* src);
public:
    Vehicle(const char* m = "", const char* md = "", int p = 0);
    Vehicle(const Vehicle& other);
    virtual~Vehicle();
    virtual void show() const;
};
class Car: virtual public Vehicle{
private:
    int passengers;
    double engineSize;
public:
    Car(const char* m, const char* md, int p, int people, double e)
        : Vehicle(m, md, p), passengers(people), engineSize(e) {
    }
    void show() const override;
};
class Truck:virtual public Vehicle {
private:
    double loadCapacity;
public:
    Truck(const char* m, const char* md, int p, double load):Vehicle(m,md,p), loadCapacity(load){}
    void show() const override;
};
class CarTruck: public Car,public Truck{
public:
    CarTruck(const char* m, const char* md, int p, int people, double e, double load):
    Vehicle(m, md, p),Car(m, md, p, people, e),Truck(m, md, p, load) {}
    void show() const override{
        Vehicle::show();
        cout << " | Passengers: ";
        Car::show();       // 이 부분에서 Vehicle 중복 방지
        cout << ", ";
        Truck::show();     // 추가 정보
    }
};
class Battery{};
class ElectricCar: public Vehicle, public Battery{};
class HybridCar: public Car, public Battery{};
class UsedVehicleStore {
private:
    Vehicle** table;
    int count;
public:
    UsedVehicleStore(Vehicle** t = new Vehicle * [MAX_SIZE], int c = 0);
    ~UsedVehicleStore();
    void add(Vehicle* v);
    void show() const;
};
int main() {
    UsedVehicleStore store;

    store.add(new Car("Hyundai", "Avante", 1800, 5, 1.6));
    store.add(new Truck("Kia", "Bongo", 2300, 1.5));
    store.add(new CarTruck("Hyundai", "Porter 2", 2500, 3, 2.0, 1.2));
    store.add(new ElectricCar("Tesla", "Model 3", 5500, 75));
    store.add(new HybridCar("Toyota", "Prius", 3200, 4, 1.8, 45));

    store.show();  // �����ε��� show ���

    int choice;
    cin >> choice;
    return 0;
}


UsedVehicleStore::UsedVehicleStore(Vehicle** t=new Vehicle*[MAX_SIZE], int c=0): count(c){
        table = new Vehicle * [c];
        for (int i = 0; i < c; ++i) 
            table[i] = t[i];    //shallow copy, delete at main()
    }
UsedVehicleStore::~UsedVehicleStore(){
        delete[] table;  //shallow copy, delete at main()
    }
void UsedVehicleStore:: add( Vehicle* v) {
        if (count < MAX_SIZE) {
            table[count] = v;
            ++count;
        }
    }
void UsedVehicleStore:: show() const{
        for (int i = 0; i < count; ++i) {
            table[i]->show();
            cout << endl;
        }
    }
};