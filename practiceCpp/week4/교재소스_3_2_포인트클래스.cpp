/ C++ class를 사용한 좌표 객체
#include <iostream>

// class 정의(define)
class Point {
public:
    int x;
    int y;

    // Constructor - 생성자
    Point(int x_val, int y_val) : x(x_val), y(y_val) {}
};

int main() {
    // class object을 생성하고 변수가 주소를 가리킴
    Point p1(5, 10);

    // class 멤버의 접근(access)
    std::cout << "점 좌표 = (" << p1.x << ", " << p1.y << ")\n";

    return 0;
}