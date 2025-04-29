#include <iostream>
#include <cstring>
using namespace std;

// =============================
// Vehicle 클래스
// =============================
class Vehicle {
private:
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
class Car : public Vehicle {
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

    ~Car() override {
        delete[] manufacturer;
        delete[] model;
    }

    void show() const override {
        Vehicle::show();
        // cout<< engineSize;  //err vehicle private: 다룰려면 vehicle에서 //cf. protected으로 선언하면 자식이 접근가능
        cout << manufacturer << " " << model << " (" << madeYear << "), "
            << price << "만원 | ";
        cout << endl;
    }

    int getMadeYear() const { return madeYear; }
    int getPrice() const { return price; }
};

// =============================
// Truck 클래스
// =============================
class Truck : public Vehicle {
private:
    char* brand;
    double torque;       // Nm
    double loadCapacity; // ton

public:
    Truck(const char* b = "", double e = 0.0, int s = 0, double tq = 0.0, double lc = 0.0)
        : Vehicle(e, s), torque(tq), loadCapacity(lc) {
        brand = new char[strlen(b) + 1];
        strcpy(brand, b);
    }

    Truck(const Truck& other) : Vehicle(other) {
        torque = other.torque;
        loadCapacity = other.loadCapacity;
        brand = new char[strlen(other.brand) + 1];
        strcpy(brand, other.brand);
    }

    ~Truck() override {
        delete[] brand;
    }

    void show() const override {
        Vehicle::show();
        cout << brand << " Truck | ";
        cout << ", Torque: " << torque << "Nm, Load: " << loadCapacity << "ton" << endl;
    }
};

// =============================
// 중고차/트럭 통합 저장 클래스
// =============================
class UsedVehicleStore {
private:
    Vehicle** vehicles;//Car* stck;6장에서 class UsedCar와 구분     //*vehicles[]와 차이점 각주 확인
    int numberVehicles;

public:
    UsedVehicleStore(Vehicle** vList, int n) {
        numberVehicles = n;
        vehicles = new Vehicle * [n]; //동적 할당
        for (int i = 0; i < n; ++i) {
            vehicles[i] = vList[i];  // 얕은 복사 (객체는 main에서 생성/관리)
        }
    }

    ~UsedVehicleStore() {
        delete[] vehicles;
    }

    void showAll() const {
        cout << "\n[중고 차량/트럭 목록]" << endl;
        for (int i = 0; i < numberVehicles; ++i) {
            vehicles[i]->show();
            //vehicle->show() virtual선언했기에 동적바인딩: 타입car인 경우 car->show(),타입truck인 경우truck->show()
        }
    }

    void showCarsOverPrice(int minPrice, int currentYear) const {
        cout << "\n[고가 중고차 목록]" << endl;
        for (int i = 0; i < numberVehicles; ++i) {
            Car* car = dynamic_cast<Car*>(vehicles[i]); //down 캐스팅 !!동적 케스팅 연습 필요!!
            // vehicles[i]가 트럭이면 nullptr를 반환한다.
            if (car && car->getPrice() > minPrice && car->getMadeYear() <= currentYear - 5) {
                car->show();
            }
        }
    }
};
/*
class UsedVehicleStore {
private:
    Vehicle* vehicles[5];  // 고정 크기 배열
    int numberVehicles;    // 여전히 몇 개 들어있는지 세는 용도로 사용

public:
    UsedVehicleStore(Vehicle** vList, int n) {
        numberVehicles = n;
        for (int i = 0; i < n && i < 5; ++i) {
            vehicles[i] = vList[i];  // 얕은 복사
        }
    }

    // ✅ 소멸자 수정
    ~UsedVehicleStore() {
        // delete[] vehicles;  ❌ 제거 (정적 배열이므로 필요 없음)
    }

    void showAll() const {
        cout << "\n[중고 차량/트럭 목록]" << endl;
        for (int i = 0; i < numberVehicles; ++i) {
            vehicles[i]->show();
        }
    }

    void showCarsOverPrice(int minPrice, int currentYear) const {
        cout << "\n[고가 중고차 목록]" << endl;
        for (int i = 0; i < numberVehicles; ++i) {
            Car* car = dynamic_cast<Car*>(vehicles[i]);
            if (car && car->getPrice() > minPrice && car->getMadeYear() <= currentYear - 5) {
                car->show();
            }
        }
    }
};
*/
int main() {
    // Car 객체
    Car* c1 = new Car("Hyundai", "Grandeur", 2018, 3200, 2.4, 180);
    Car* c2 = new Car("Kia", "K5", 2019, 2500, 1.6, 170);
    Car* c3 = new Car("Renault", "SM6", 2021, 2300, 1.8, 160);

    // Truck 객체
    Truck* t1 = new Truck("Volvo", 5.0, 140, 1200, 15.0);
    Truck* t2 = new Truck("Hyundai", 3.5, 120, 950, 8.0);

    // Vehicle 포인터 배열로 묶기
    Vehicle* vehicles[5] = { c1, c2, c3, t1, t2 };
    //vehicle->show() virtual선언했기에 동적바인딩: 타입car인 경우 car->show(),타입truck인 경우truck->show()

    // 중고차 매장에 등록
    UsedVehicleStore store(vehicles, 5);

    store.showAll();
    store.showCarsOverPrice(3000, 2025);

    // 동적 메모리 해제
    delete c1;
    delete c2;
    delete c3;
    delete t1;
    delete t2;
    int choice;
    cin >> choice;
    return 0;
}
