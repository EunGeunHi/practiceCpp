#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

// =============================
// Vehicle 클래스 (공통 정보)
// =============================
class Vehicle {
private:
    char* manufacturer;
    char* model;
    int price;

public:
    Vehicle(const char* m = "", const char* md = "", int p = 0)
        : price(p) {
        manufacturer = new char[strlen(m) + 1];
        strcpy(manufacturer, m);
        model = new char[strlen(md) + 1];
        strcpy(model, md);
    }

    Vehicle(const Vehicle& other) : price(other.price) {
        manufacturer = new char[strlen(other.manufacturer) + 1];
        strcpy(manufacturer, other.manufacturer);
        model = new char[strlen(other.model) + 1];
        strcpy(model, other.model);
    }

    virtual ~Vehicle() {
        delete[] manufacturer;
        delete[] model;
    }

    virtual void show() const {
        cout << manufacturer << " " << model << ", " << price << "만원";
    }
};

// =============================
// Battery 클래스
// =============================
class Battery {
private:
    int capacity;  // kWh
    string mode;

public:
    Battery(int cap = 0, const string& m = "EV") : capacity(cap), mode(m) {}
    virtual ~Battery() {}

    virtual void showDetails() const {
        cout << " | Battery: " << capacity << "kWh, Mode: " << mode;
    }
};

// =============================
// Car 클래스
// =============================
class Car : virtual public Vehicle {
private:
    int passengers;
    double engineSize;

public:
    Car(const char* m, const char* md, int p, int people, double e)
        : Vehicle(m, md, p), passengers(people), engineSize(e) {}

    void show() const override {
        Vehicle::show();
        showDetails();
        cout << endl;
    }

    void showDetails() const {
        cout << " | Passengers: " << passengers << ", Engine: " << engineSize << "L";
    }
};

// =============================
// Truck 클래스
// =============================
class Truck : virtual public Vehicle {
private:
    double loadCapacity;

public:
    Truck(const char* m, const char* md, int p, double load)
        : Vehicle(m, md, p), loadCapacity(load) {}

    void show() const override {
        Vehicle::show();
        showDetails();
        cout << endl;
    }

    void showDetails() const {
        cout << " | Load Capacity: " << loadCapacity << " tons";
    }
};

// =============================
// CarTruck 클래스
// =============================
class CarTruck : public Car, public Truck {
public:
    CarTruck(const char* m, const char* md, int p, int people, double e, double load)
        : Vehicle(m, md, p),
        Car(m, md, p, people, e),
        Truck(m, md, p, load) {}

    void show() const override {
        Vehicle::show();  // Vehicle 정보는 한 번만 출력
        Car::showDetails();
        Truck::showDetails();
        cout << endl;
    }
};

// =============================
// ElectricCar 클래스
// =============================
class ElectricCar : public Vehicle, public Battery {
public:
    ElectricCar(const char* m, const char* md, int p, int cap)
        : Vehicle(m, md, p), Battery(cap, "EV") {}

    void show() const override {
        Vehicle::show();
        Battery::showDetails();
        cout << endl;
    }
};

// =============================
// HybridCar 클래스
// =============================
class HybridCar : public Car, public Battery {
public:
    HybridCar(const char* m, const char* md, int p, int people, double e, int cap)
        : Vehicle(m, md, p),
        Car(m, md, p, people, e),
        Battery(cap, "Hybrid") {}

    void show() const override {
        Vehicle::show();       // Vehicle 정보는 한 번만 출력
        Car::showDetails();    // Car 정보
        Battery::showDetails(); // 배터리 정보
        cout << endl;
    }
};

// =============================
// UsedVehicleStore 클래스
// =============================
class UsedVehicleStore {
private:
    vector<Vehicle*> vehicles;

public:
    ~UsedVehicleStore() {
        for (auto v : vehicles) delete v;
    }

    void add(Vehicle* v) {
        vehicles.push_back(v);
    }

    void showAll() const {
        cout << "\n[중고 차량 목록 출력]\n";
        for (auto v : vehicles) {
            v->show();
        }
    }
};

// =============================
// main()
// =============================
int main() {
    UsedVehicleStore store;

    store.add(new Car("Hyundai", "Avante", 1800, 5, 1.6));
    store.add(new Truck("Kia", "Bongo", 2300, 1.5));
    store.add(new CarTruck("Hyundai", "Porter 2", 2500, 3, 2.0, 1.2));
    store.add(new ElectricCar("Tesla", "Model 3", 5500, 75));
    store.add(new HybridCar("Toyota", "Prius", 3200, 4, 1.8, 45));

    store.showAll();
    return 0;
}
