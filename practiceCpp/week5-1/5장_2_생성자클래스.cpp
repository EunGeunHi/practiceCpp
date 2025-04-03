#include <iostream>


using namespace std;

// 자동차 클래스 (모든 멤버를 public으로 변경)
class Car {
public:
    char* manufacturer; // 제조사
    char* model;        // 모델명
    double weight;       // 차중량 (kg)
    int length;          // 전장(mm)
    int width;           // 전폭(mm)
    int speed;           // 속도

    // 생성자 선언
    Car(char* m, char* mod, double w, int l, int wdt, int s);
    Car(char* m, char* mod);
    Car();
    // 전장 기준으로 차급 세그먼트 분류 (함수 선언)
    char* getSegment();

    // 과속 여부 판단 메소드 (제한 속도 입력받는 버전)
    void checkSpeeding(int speedLimit);

    // 과속 여부 판단 메소드 (기본 제한 속도 60km/h 적용, 오버로딩)
    void checkSpeeding();

    // 객체 정보를 출력하는 연산자 오버로딩 (선언)
    friend ostream& operator<<(ostream& os, const Car& car);
};

// =============================
// 자동차 클래스 멤버 함수 구현 (클래스 외부에서 구현)
// =============================

// 생성자 정의
Car::Car() {
    manufacturer = nullptr;
}
Car::Car(char* m, char* mod) {
    manufacturer = m;
    model = mod;
}
Car::Car(char* m, char* mod, double w, int l, int wdt, int s)
    : manufacturer(m), model(mod), weight(w), length(l), width(wdt), speed(s) {}

// 전장 기준으로 차급 세그먼트 분류 (함수 구현)
char* Car::getSegment() {
    if (length < 4200)
        return strdup("B-세그먼트 (소형차)");
    else if (length < 4600)
        return "C-세그먼트 (준중형, 소형 패밀리카)";
    else if (length < 4900)
        return "D-세그먼트 (중형차, 패밀리 세단)";
    else if (length < 5100)
        return "E-세그먼트 (대형차, 고급 세단)";
    else
        return "F-세그먼트 (초대형차, 플래그십 세단)";
}

// 과속 여부 판단 (제한 속도 입력받는 버전)
void Car::checkSpeeding(int speedLimit) {
    if (speed > speedLimit)
        cout << "과속 경고! (제한 속도: " << speedLimit << " km/h)" << endl;
    else
        cout << "정상 주행" << endl;
}

// 과속 여부 판단 (기본 제한 속도 60km/h 적용, 오버로딩)
void Car::checkSpeeding() {
    if (speed > 60)
        cout << "과속 경고! (제한 속도: 60 km/h)" << endl;
    else
        cout << "정상 주행" << endl;
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

    // 객체 멤버 변경
    car1.speed = 80; // 속도 변경 가능
    car2.manufacturer = "Mercedes"; // 제조사 변경 가능

    cout << "수정된 차량 정보:" << endl;
    cout << car1 << endl;
    cout << car2 << endl;

    // 사용자가 만든 생성자가 있을 때 기본 생성자가 없는 경우 오류 발생
    Car c1; //default 생성자가 없으면 오류

    return 0;
}
