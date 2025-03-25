//C 언어의 struct 사용
// struct을 사용한 좌표 객체 표현
#include <stdio.h>

// struct 멤버가 좌표
struct Point {
    int x;
    int y;
};

int main() {
    // struct 변수 선언
    struct Point p1;

    // struct 멤버 값을 초기화
    p1.x = 5;
    p1.y = 10;

    // struct 멤버 변수를 사용
    printf("점 좌표 = (%d, %d)\n", p1.x, p1.y);

    return 0;
}