#include <iostream>
#include <cstring>

using namespace std;

// 자동차 클래스 (데이터 멤버를 private으로 변경)
class Car {
private:
    char manufacturer[50]; // 제조사 char *manufacturer; 구현할 줄 알아야 한다.
    char model[50];        // 모델명 char *model; 구현할 줄 알아야 한다.
    double weight;         // 차중량 (kg)
    int length;            // 전장(mm)
    int width;             // 전폭(mm)
    int speed;             // 속도

public:
    // 생성자 선언
    Car(const char* m, const char* mod, double w, int l, int wdt, int s);
    Car();

    // Getter & Setter
    void setManufacturer(const char* m);
    const char* getManufacturer() const;
    void setModel(const char* mod);
    const char* getModel() const;
    void setWeight(double w);
    double getWeight() const;
    void setLength(int l);
    int getLength() const;
    void setWidth(int w);
    int getWidth() const;
    void setSpeed(int s);
    int getSpeed() const;

    // 전장 기준으로 차급 세그먼트 분류
    const char* getSegment();

    // 과속 여부 판단 메소드
    void checkSpeeding(int speedLimit);
    void checkSpeeding();

    // 객체 정보를 출력하는 연산자 오버로딩
    friend ostream& operator<<(ostream& os, const Car& car);
};

// =============================
// 자동차 클래스 멤버 함수 구현
// =============================

// 생성자 정의
Car::Car(const char* m, const char* mod, double w, int l, int wdt, int s) {
    strncpy(manufacturer, m, sizeof(manufacturer) - 1);
    manufacturer[sizeof(manufacturer) - 1] = '\0';
    strncpy(model, mod, sizeof(model) - 1);
    model[sizeof(model) - 1] = '\0';
    weight = w;
    length = l;
    width = wdt;
    speed = s;
}

Car::Car() {
    manufacturer[0] = '\0';
    model[0] = '\0';
    weight = 0.0;
    length = 0;
    width = 0;
    speed = 0;
}

// Getter & Setter 구현
void Car::setManufacturer(const char* m) {
    strncpy(manufacturer, m, sizeof(manufacturer) - 1);
    manufacturer[sizeof(manufacturer) - 1] = '\0';
}
const char* Car::getManufacturer() const {
    return manufacturer;
}
void Car::setModel(const char* mod) {
    strncpy(model, mod, sizeof(model) - 1);
    model[sizeof(model) - 1] = '\0';
}
const char* Car::getModel() const {
    return model;
}
void Car::setWeight(double w) {
    weight = w;
}
double Car::getWeight() const {
    return weight;
}
void Car::setLength(int l) {
    length = l;
}
int Car::getLength() const {
    return length;
}
void Car::setWidth(int w) {
    width = w;
}
int Car::getWidth() const {
    return width;
}
void Car::setSpeed(int s) {
    speed = s;
}
int Car::getSpeed() const {
    return speed;
}

// 전장 기준으로 차급 세그먼트 분류
const char* Car::getSegment() {
    if (length < 4200)
        return "B-세그먼트 (소형차)";
    else if (length < 4600)
        return "C-세그먼트 (준중형, 소형 패밀리카)";
    else if (length < 4900)
        return "D-세그먼트 (중형차, 패밀리 세단)";
    else if (length < 5100)
        return "E-세그먼트 (대형차, 고급 세단)";
    else
        return "F-세그먼트 (초대형차, 플래그십 세단)";
}

// 과속 여부 판단
void Car::checkSpeeding(int speedLimit) {
    if (speed > speedLimit)
        cout << "과속 경고! (제한 속도: " << speedLimit << " km/h)" << endl;
    else
        cout << "정상 주행" << endl;
}
void Car::checkSpeeding() {
    checkSpeeding(60);
}

// 객체 정보를 출력하는 연산자 오버로딩
ostream& operator<<(ostream& os, const Car& car) {
    os << "제조사 = " << car.manufacturer
        << ", 모델 = " << car.model
        << ", 중량 = " << car.weight << " kg"
        << ", 전장 = " << car.length << " mm"
        << ", 전폭 = " << car.width << " mm"
        << ", 속도 = " << car.speed << " km/h";
    return os;
}

// =============================
// 메인 함수
// =============================
int main() {
    // 자동차 객체 생성
    Car car1("Hyundai", "Sonata", 1400, 4600, 1800, 95);
    Car car2("BMW", "M3", 1200, 4500, 1700, 110);

    // 객체 멤버 변경 (setter 사용)
    car1.setSpeed(80);
    car2.setManufacturer("Mercedes");

    cout << "수정된 차량 정보:" << endl;
    cout << car1 << endl;
    cout << car2 << endl;

    // 기본 생성자 사용
    Car c1;
    c1.setManufacturer("Toyota");
    c1.setModel("Camry");
    c1.setSpeed(70);

    cout << "기본 생성자로 생성된 차량 정보:" << endl;
    cout << c1 << endl;

    return 0;
}
