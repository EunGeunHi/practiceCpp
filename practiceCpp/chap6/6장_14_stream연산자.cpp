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
ostream& operator<<(ostream& os, const Car& car);   //ostream& Car::operator<<(); 가 아님!
ostream& operator<<(ostream& os, const UsedCar& uc);    //반환값 ostream&인 이유: cout << c1 << c2 << c3 인 경우 앞에서부터 << c1 을 os로 반환, 이어서 c2 c3 캐스캐이팅

bool isExpensive(const Car&, int, int);

// =============================
// 클래스 정의
// =============================
class Car : public Vehicle {
private:
    char* manufacturer;
    char* model;
    int madeYear;
    int price;

    char* copyString(const char* s){ //deep copy중복 코드 줄임
        ret = new char[strlen(s) + 1];
        strcpy(ret, s);
        return ret;
    }
public:
    friend class UsedCar;
    friend ostream& operator<<(ostream& os, const Car& car);
    friend bool isExpensive(const Car&, int, int);

    Car(const char* m = "", const char* md = "", int y = 0, int p = 0,
        double e = 0.0, int s = 0)
        : Vehicle(e, s), madeYear(y), price(p) {
        manufacturer = copyString(m);
        model = copyString(md);
        /*
        manufacturer = new char[strlen(m) + 1];
        strcpy(manufacturer, m);
        model = new char[strlen(md) + 1];
        strcpy(model, md);
        */
        
    }

    Car(const Car& other) : Vehicle(other) {
        madeYear = other.madeYear;
        price = other.price;
        manufacturer = new char[strlen(other.manufacturer) + 1];
        strcpy(manufacturer, other.manufacturer);
        model = new char[strlen(other.model) + 1];
        strcpy(model, other.model);
    }
    /*
    //컴파일러가 만드는 치환연산자는 shallowcopy
    Car& operator = (const Car& other){
        if (this != &other){
        Vehicle::operator(other)
        }
    
    }
    ...
    
    
    */
    ~Car() {
        delete[] manufacturer;
        delete[] model;
    }

    void show() const {
        cout << manufacturer << " " << model << " (" << madeYear << "), "
            << price << "���� | ";
        showSpecs();
        cout << endl;
    }
};

// Car 출력 연산자 오버로딩 정의
ostream& operator<<(ostream& os, const Car& car) {
    os << car.manufacturer << " " << car.model
        << " (" << car.madeYear << "), " << car.price << "���� | ";
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
            stock[i] = cars[i]; //치환문 : deep copy 아니면 err
        }
    }

    ~UsedCar() {
        delete[] stock;
    }

    void showExpensiveOldCars(int minPrice, int currentYear) {
        cout << "\n[5년 이상 경과 & " << minPrice << "���� �ʰ� ����]" << endl;
        for (int i = 0; i < numberCars; ++i) {
            if (isExpensive(stock[i], minPrice, currentYear)) {
                cout << stock[i] << endl;
            }
        }
    }
};

// UsedCar ��� ������ �����ε� ����
ostream& operator<<(ostream& os, const UsedCar& uc) {
    os << "\n[UsedCar ��ü ���� ���]\n";
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

    cout << store;              // ��ü ���� ��� ���
    cout << "\n>> ù ��° ���� ����:\n" << cars[0] << endl;

    store.showExpensiveOldCars(3000, 2025);  // 5�� �̻� & ���� ���� ���

    return 0;
}


/*
파일 새로 다운받아서 비교


friend      사용
operator+   구현
operator=   구현
operator<<  구현

*/