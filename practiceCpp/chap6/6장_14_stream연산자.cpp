#include <iostream>
#include <cstring>
using namespace std;

// =============================
// Vehicle 클래스
// =============================
class Vehicle {
protected:
    double engineSize;
    int speed;

public:
    Vehicle(double e = 0.0, int s = 0) : engineSize(e), speed(s) {}
    void showSpecs() const {
        cout << "Engine: " << engineSize << "L, Speed: " << speed << "km/h";
    }
};

// forward 선언
class UsedCar;
class Car;

// =============================
// 출력 연산자 friend 선언
// =============================
ostream& operator<<(ostream& os, const Car& car);
ostream& operator<<(ostream& os, const UsedCar& uc);
bool isExpensive(const Car&, int, int);

// =============================
// Car 클래스 정의
// =============================
class Car : public Vehicle {
private:
    char* manufacturer;
    char* model;
    int madeYear;
    int price;

public:
    friend class UsedCar;
    friend ostream& operator<<(ostream& os, const Car& car);
    friend bool isExpensive(const Car&, int, int);

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

    ~Car() {
        delete[] manufacturer;
        delete[] model;
    }

    void show() const {
        cout << manufacturer << " " << model << " (" << madeYear << "), "
            << price << "만원 | ";
        showSpecs();
        cout << endl;
    }
};

// Car 출력 연산자 오버로딩 정의
ostream& operator<<(ostream& os, const Car& car) {
    os << car.manufacturer << " " << car.model
        << " (" << car.madeYear << "), " << car.price << "만원 | ";
    os << "Engine: " << car.engineSize << "L, Speed: " << car.speed << "km/h";
    return os;
}

// =============================
// UsedCar 클래스 정의
// =============================
class UsedCar {
private:
    Car* stock;
    int numberCars;

public:
    friend ostream& operator<<(ostream& os, const UsedCar& uc);

    UsedCar(Car* cars, int n) {
        numberCars = n;
        stock = new Car[numberCars];
        for (int i = 0; i < numberCars; ++i) {
            stock[i] = cars[i];
        }
    }

    ~UsedCar() {
        delete[] stock;
    }

    void showExpensiveOldCars(int minPrice, int currentYear) {
        cout << "\n[5년 이상 경과 & " << minPrice << "만원 초과 차량]" << endl;
        for (int i = 0; i < numberCars; ++i) {
            if (isExpensive(stock[i], minPrice, currentYear)) {
                cout << stock[i] << endl;
            }
        }
    }
};

// UsedCar 출력 연산자 오버로딩 정의
ostream& operator<<(ostream& os, const UsedCar& uc) {
    os << "\n[UsedCar 전체 차량 목록]\n";
    for (int i = 0; i < uc.numberCars; ++i) {
        os << uc.stock[i] << endl;
    }
    return os;
}

// =============================
// friend 함수 정의
// =============================
bool isExpensive(const Car& c, int priceThreshold, int currentYear) {
    return (c.price > priceThreshold) && (c.madeYear <= currentYear - 5);
}

// =============================
// main 함수
// =============================
int main() {
    Car cars[5] = {
        Car("Hyundai", "Grandeur", 2018, 3200, 2.4, 180),
        Car("Kia", "K5", 2019, 2500, 1.6, 170),
        Car("Renault", "SM6", 2021, 2300, 1.8, 160),
        Car("GM", "Malibu", 2017, 3100, 2.0, 175),
        Car("KGM", "Torres", 2020, 3600, 1.5, 165)
    };

    UsedCar store(cars, 5);

    cout << store;              // 전체 차량 목록 출력
    cout << "\n>> 첫 번째 차량 정보:\n" << cars[0] << endl;

    store.showExpensiveOldCars(3000, 2025);  // 5년 이상 & 고가 차량 출력

    return 0;
}
