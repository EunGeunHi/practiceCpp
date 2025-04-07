#include <iostream>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <windows.h>

struct Rectangle {
    int leftBottomX;
    int leftBottomY;
    int width;
    int height;
};

int compareRectangles(const struct Rectangle* a, const struct Rectangle* b) {
    return (a->leftBottomX - b->leftBottomX);
}
void showRectangle(struct Rectangle r) {
    printf("[%d, %d, %d, %d]\n", r.leftBottomX, r.leftBottomY, r.width, r.height);
}
void showRectangles(const char* message, struct Rectangle* rectangles[], int numRectangles) { // const char* message?
    printf("%s\n", message);
    for (int i = 0; i < numRectangles; i++)
        showRectangle(*rectangles[i]);//rectangles[i]은 주소값, showRectangle()은 파라미터로 값을 요구
}
void swap(struct Rectangle* rect[], int i, int j) {
    struct Rectangle* temp = rect[i];       //포인터 복사
    rect[i] = rect[j];
    rect[j] = temp;

    // struct Rectangle temp = *rect[i];    //구조체 복사는 temp를 위한 추가 메모리, 연산 더 많음, 외부참조가 깨질 수 있
    // *rect[i] = *rect[j];
    // *rect[j] = temp;
}
void selectionSortRectangles(struct Rectangle* rectangles[], int numRectangles) {
    for (int i = 0; i < numRectangles - 1; i++)
        for (int j = 0; j < numRectangles-1-i; j++)
            if (compareRectangles(rectangles[j], rectangles[j+1]) > 0)swap(rectangles, j, j+1);
}

int main(void) {
    SetConsoleOutputCP(CP_UTF8);//한글깨지는 문제 해결하기 위해 사용  
    const int numRectangles = 5;
    struct Rectangle r1 = { 3, 5, 10, 15 };
    struct Rectangle r2 = { 4, 5, 10, 12 };
    struct Rectangle r3 = { 3, 5, 6, 10 };
    struct Rectangle r4 = { 7, 5, 7, 8 };
    struct Rectangle r5 = { 1, 3, 9, 14 };
    struct Rectangle* rectangles[numRectangles] = { &r1,&r2,&r3,&r4,&r5 };
    //array of pointer // &:c에선 주소, cpp에선 참조변수

    showRectangles("정렬전:", rectangles, numRectangles);

    selectionSortRectangles(rectangles, numRectangles);

    showRectangles("정렬후:", rectangles, numRectangles);

    system("pause");
    return 0;
}