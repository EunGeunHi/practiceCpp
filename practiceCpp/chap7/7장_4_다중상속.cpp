#include <iostream>
#include <cstring>
using namespace std;

// =============================
// Vehicle 클래스
// =============================
class Vehicle {
private:
    char* manufacturer;
    char* model;
    int madeYear;
    int price;
    /*
    static char* copyString(const char* src) { // 코드 간결화에 사용
        char* dest = new char[strlen(src) + 1];
        strcpy(dest, src);
        return dest;
    }
    */
public:
    Vehicle(const char* m = "", const char* md = "", int y = 0, int p = 0)
        : madeYear(y), price(p) {
        manufacturer = new char[strlen(m) + 1];
        strcpy(manufacturer, m);
        model = new char[strlen(md) + 1];
        strcpy(model, md);
    }

    Vehicle(const Vehicle& other)
        : madeYear(other.madeYear), price(other.price) {
        manufacturer = new char[strlen(other.manufacturer) + 1];
        strcpy(manufacturer, other.manufacturer);
        model = new char[strlen(other.model) + 1];
        strcpy(model, other.model);
    }

    virtual ~Vehicle() {
        delete[] manufacturer;
        delete[] model;
    }

    friend ostream& operator<<(ostream& os, const Vehicle& v) {
        os << v.manufacturer << " " << v.model << " (" << v.madeYear << "), "
            << v.price << "만원";
        return os;
    }
};

// =============================
// Car 클래스 (내연기관 차량)
// =============================
class Car : public Vehicle {
private:
    double engineSize;
    int speed;

public:
    Car(const char* m, const char* md, int y, int p,
        double e, int s)
        : Vehicle(m, md, y, p), engineSize(e), speed(s) {}

    friend ostream& operator<<(ostream& os, const Car& c) {
        os << static_cast<const Vehicle&>(c)    //c를 vehicle로 바꾼후
            << " | Engine: " << c.engineSize << "L, Speed: " << c.speed << "km/h";
        return os;
    }
};

// =============================
// Battery 클래스
// =============================
class Battery {
private:
    int capacity;     // kWh
    string mode;      // "EV", "Hybrid", etc.

public:
    Battery(int cap = 0, const string& m = "EV")
        : capacity(cap), mode(m) {}

    friend ostream& operator<<(ostream& os, const Battery& b) {
        os << " | Battery: " << b.capacity << "kWh, Mode: " << b.mode;
        return os;
    }
};

// =============================
// HybridCar 클래스
// =============================
class HybridCar : public Car, public Battery {
public:
    HybridCar(const char* m, const char* md, int y, int p,
        double e, int s, int cap)
        : Car(m, md, y, p, e, s), Battery(cap, "Hybrid") {}

    friend ostream& operator<<(ostream& os, const HybridCar& h) {
        os << static_cast<const Car&>(h);       //캐스팅해서
        os << static_cast<const Battery&>(h);   //캐스팅해서
        return os;
    }
};

// =============================
// ElectricCar 클래스
// =============================
class ElectricCar : public Vehicle, public Battery {
public:
    ElectricCar(const char* m, const char* md, int y, int p,
        int cap)
        : Vehicle(m, md, y, p), Battery(cap, "EV") {}

    friend ostream& operator<<(ostream& os, const ElectricCar& e) {
        os << static_cast<const Vehicle&>(e);
        os << static_cast<const Battery&>(e);
        return os;
    }
};

// =============================
// main 함수
// =============================
int main() {
    HybridCar h1("Toyota", "Prius", 2018, 3500, 1.8, 170, 45);
    HybridCar h2("Hyundai", "Ioniq Hybrid", 2021, 3300, 1.6, 165, 42);

    ElectricCar e1("Tesla", "Model 3", 2022, 5500, 75);
    ElectricCar e2("Hyundai", "Ioniq 6", 2023, 4700, 77);

    cout << "[하이브리드 차량 목록]\n";
    cout << h1 << endl;
    cout << h2 << endl;

    cout << "\n[전기차 목록]\n";
    cout << e1 << endl;
    cout << e2 << endl;
    int choice;
    cin >> choice;
    return 0;
}
