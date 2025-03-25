#include <iostream>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <windows.h>

/* //c 구조체 형태
struct Rectangle {
    int leftBottomX;
    int leftBottomY;
    int width;
    int height;
};
*/

typedef struct Rectangle {
    int leftBottomX;
    int leftBottomY;
    int width;
    int height;
} Rectangle;

//기본적인 C 언어 문법에서는 struct Rectangle를 반드시 써야
int compareRectangles(const Rectangle* a, const Rectangle* b) {
    return (a->leftBottomX - b->leftBottomX);
}
void showRectangle(struct Rectangle r) {
    printf("[%d, %d, %d, %d]\n", r.leftBottomX, r.leftBottomY, r.width, r.height);
}
void showRectangles(char* message, Rectangle* rectangles[], int numRectangles) {

}
void swap(Rectangle* rect[], int i, int j) {

}
void selectionSortRectangles(Rectangle* rectangles[], int numRectangles) {
    // int compareRectangles(const Student* b);를 사용한 정렬
    // void swap(Rectangle * rect[], int i, int j) 사용
    //버블,셀렉 정렬(for 2번)
}

int main(void) {
    SetConsoleOutputCP(CP_UTF8);//한글깨지는 문제 해결하기 위해 사용 
    const int numRectangles = 5;
    struct Rectangle r1 = { 3, 5, 10, 15 };
    struct Rectangle r2 = { 3, 5, 10, 12 };
    struct Rectangle r3 = { 3, 5, 6, 10 };
    struct Rectangle r4 = { 3, 5, 7, 8 };
    struct Rectangle r5 = { 3, 3, 9, 14 };
    struct Rectangle* rectangles[numRectangles] = { &r1,&r2,&r3,&r4,&r5 };
    //array of pointer // &:c에선 주소, cpp에선 참조변수

    showRectangles("정렬전:", rectangles, numRectangles);

    selectionSortRectangles(rectangles, numRectangles);

    showRectangles("정렬후:", rectangles, numRectangles);

    system("pause");
    return 0;
}