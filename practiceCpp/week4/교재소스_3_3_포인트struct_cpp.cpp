//C++의 struct 사용
#include <iostream>

// 멤버 함수를 갖는 struct 정의
struct Point {
    int x;
    int y;

    // 생성자의 초기화 방법: initialization list 사용
    Point(int x_val, int y_val) : x(x_val), y(y_val) {}

    // 좌표를 출력하는 멤버 함수
    void printCoordinates() {
        std::cout << "점 좌표 = (" << x << ", " << y << ")\n";
    }

    // 좌표를 이동하는 Member function
    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }
};

int main() {
    // struct object의 생성
    Point p1(5, 10);

    // struct member functions 사용
    p1.printCoordinates();

    // 멤버 함수 호출에 의한 struct 객체 변경
    p1.move(3, -2);

    // 변경된 좌표를 출력
    p1.printCoordinates();

    return 0;
}