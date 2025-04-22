#include <iostream>
#include <cstring>
using namespace std;

// =============================
// Vehicle 클래스
// =============================
class Vehicle {
protected:  // ← HybridCar에서 접근 가능하도록
    double engineSize;
    int speed;

public:
    Vehicle(double e = 0.0, int s = 0) : engineSize(e), speed(s) {}
    virtual ~Vehicle() {}

    virtual void show() const {
        cout << "Engine: " << engineSize << "L, Speed: " << speed << "km/h";
    }
};

// =============================
// Car 클래스
// =============================
class Car : private Vehicle {  // ← private 상속
protected:  // ← HybridCar에서 직접 접근하기 위해 private → protected 변경
    char* manufacturer;
    char* model;
    int madeYear;
    int price;

public:
    Car(const char* m = "", const char* md = "", int y = 0, int p = 0,
        double e = 0.0, int s = 0)
        : Vehicle(e, s), madeYear(y), price(p) {
        manufacturer = new char[strlen(m) + 1];
        strcpy(manufacturer, m);
        model = new char[strlen(md) + 1];
        strcpy(model, md);
    }

    Car(const Car& other) : Vehicle(other) {
        madeYear = other.madeYear;
        price = other.price;
        manufacturer = new char[strlen(other.manufacturer) + 1];
        strcpy(manufacturer, other.manufacturer);
        model = new char[strlen(other.model) + 1];
        strcpy(model, other.model);
    }

    virtual ~Car() {
        delete[] manufacturer;
        delete[] model;
    }

    virtual void show() const {
        cout << manufacturer << " " << model << " (" << madeYear << "), "
            << price << "만원 | ";
        Vehicle::show();
        cout << endl;
    }

    // 다형성 처리를 위해 friend 선언
    friend class HybridCar;
    friend class UsedVehicleStore;
};

// =============================
// HybridCar 클래스
// =============================
class HybridCar : private Car {
private:
    int batteryCapacity;  // kWh
    string mode;          // "EV", "Engine", "Hybrid"

public:
    HybridCar(const char* m, const char* md, int y, int p,
        double e, int s, int battery, const string& driveMode)
        : Car(m, md, y, p, e, s), batteryCapacity(battery), mode(driveMode) {}

    void show() const {
        // Car 멤버 직접 접근 (protected이므로 가능)
        cout << manufacturer << " " << model << " (" << madeYear << "), "
            << price << "만원 | ";
        cout << "Engine: " << engineSize << "L, Speed: " << speed << "km/h | ";
        cout << "Battery: " << batteryCapacity << "kWh, Mode: " << mode << endl;
    }

    friend class UsedVehicleStore;
};

// =============================
// UsedVehicleStore 클래스
// =============================
class UsedVehicleStore {
private:
    void** vehicles;  // Vehicle 포인터가 아님! 다형성이 깨졌기 때문에 void*로 처리
    int numberVehicles;

public:
    UsedVehicleStore(void** vList, int n) {
        numberVehicles = n;
        vehicles = new void* [n];
        for (int i = 0; i < n; ++i) {
            vehicles[i] = vList[i];
        }
    }

    ~UsedVehicleStore() {
        delete[] vehicles;
    }

    void showAll() const {
        cout << "\n[중고 차량 목록 출력]\n";
        for (int i = 0; i < numberVehicles; ++i) {
            // Vehicle* 로 형변환 불가하므로 실제 타입에 따라 분기
            if (i < 2) // 앞 2개는 Car
                ((Car*)vehicles[i])->show();
            else       // 뒤 2개는 HybridCar
                ((HybridCar*)vehicles[i])->show();
        }
    }
};

// =============================
// main 함수
// =============================
int main() {
    Car* c1 = new Car("Hyundai", "Avante", 2020, 2000, 1.6, 160);
    Car* c2 = new Car("Kia", "K5", 2019, 2500, 2.0, 180);
    HybridCar* h1 = new HybridCar("Toyota", "Prius", 2018, 3500, 1.8, 170, 45, "Hybrid");
    HybridCar* h2 = new HybridCar("Hyundai", "Ioniq", 2021, 3300, 1.6, 165, 42, "EV");

    // Vehicle 포인터 배열을 사용할 수 없음 (private 상속이기 때문에)
    void* vList[4] = { c1, c2, h1, h2 };

    UsedVehicleStore store(vList, 4);
    store.showAll();

    delete c1;
    delete c2;
    delete h1;
    delete h2;

    return 0;
}
