#include <iostream>


using namespace std;

// 자동차 클래스 (매우 단순한 버전)
class Car {
public:
    char * manufacturer; // 제조사
    char * model;        // 모델명
    double weight;       // 차중량 (kg)
    int length;          // 전장(mm)
    int width;           // 전폭(mm)
    int speed;           // 속도

    // 차급 세그먼트 분류
    char* getSegment() {
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
    void checkSpeeding(int speedLimit) {
        if (speed > speedLimit)
            cout << "과속 경고! (제한 속도: " << speedLimit << " km/h)" << endl;
        else
            cout << "정상 주행" << endl;
    }
};

int main() {
    Car car1, car2;//컴파일러가 제공한 생성자가 사용됨 - default 생성자라 한다.
    cout << "차량 모델: " << car1.model << endl; // 초기화되지 않은 값 (쓰레기 값)
    /*
    * 데이터 멤버가 public 이므로 main()에서 변경 처리 가능 > 매우 바람직하지 않다
    * 이유는 변수의 변경이 도처에서 가능
    * 데이터 변경이 localize되어야 한다.
    */
    car1.manufacturer = "Hyundai";
    car1.model = "Sonata";
    car1.weight = 1400;
    car1.length = 4600;
    car1.width = 1800;
    car1.speed = 95;

    car2.manufacturer = "BMW";
    car2.model = "M3";
    car2.weight = 1200;
    car2.length = 4500;
    car2.width = 1700;
    car2.speed = 110;

    // 제한 속도 설정
    int cityLimit = 50;    // 도심 제한 속도
    int highwayLimit = 100; // 고속도로 제한 속도

    // 과속 여부 확인
    cout << "도심 주행 테스트:" << endl;
    car1.checkSpeeding(cityLimit);
    car2.checkSpeeding(cityLimit);

    cout << "\n고속도로 주행 테스트:" << endl;
    car1.checkSpeeding(highwayLimit);
    car2.checkSpeeding(highwayLimit);

    // 차량 크기 분류 출력
    cout << "\n차량 크기 분류:" << endl;
    cout << car1.getSegment() << endl;
    cout << car2.getSegment() << endl;

    return 0;
}
