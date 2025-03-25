// C++ class를 사용한 좌표 객체
#include <iostream>

// class 정의(define)
class Point {
public:     //접근 제어자
// private: //x,y는 클래스 Point내부에서만 접근 가능 
    int x;
    int y;
public:
    // Constructor - 생성자
    Point(int x_val, int y_val) : x(x_val), y(y_val) {}
};//클래스 내에서는 함수 선언만, 바디나 구현은 따로 때서 작성해서 가독성 좋게

int main() {
    // class object을 생성하고 변수가 주소를 가리킴
    Point p1(5, 10);

    // class 멤버의 접근(access)
    std::cout << "점 좌표 = (" << p1.x << ", " << p1.y << ")\n";

    return 0;
}
