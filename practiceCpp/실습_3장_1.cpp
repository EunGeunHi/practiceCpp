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
        showRectangle(*rectangles[i]);//rectangles[i]�� �ּҰ�, showRectangle()�� �Ķ���ͷ� ���� �䱸
}
void swap(struct Rectangle* rect[], int i, int j) {
    struct Rectangle* temp = rect[i];       //������ ����
    rect[i] = rect[j];
    rect[j] = temp;

    // struct Rectangle temp = *rect[i];    //����ü ����� temp�� ���� �߰� �޸�, ���� �� ����, �ܺ������� ���� �� ��
    // *rect[i] = *rect[j];
    // *rect[j] = temp;
}
void selectionSortRectangles(struct Rectangle* rectangles[], int numRectangles) {
    for (int i = 0; i < numRectangles - 1; i++)
        for (int j = 0; j < numRectangles-1-i; j++)
            if (compareRectangles(rectangles[j], rectangles[j+1]) > 0)swap(rectangles, j, j+1);
}

int main(void) {
    SetConsoleOutputCP(CP_UTF8);//�ѱ۱����� ���� �ذ��ϱ� ���� ���  
    const int numRectangles = 5;
    struct Rectangle r1 = { 3, 5, 10, 15 };
    struct Rectangle r2 = { 4, 5, 10, 12 };
    struct Rectangle r3 = { 3, 5, 6, 10 };
    struct Rectangle r4 = { 7, 5, 7, 8 };
    struct Rectangle r5 = { 1, 3, 9, 14 };
    struct Rectangle* rectangles[numRectangles] = { &r1,&r2,&r3,&r4,&r5 };
    //array of pointer // &:c���� �ּ�, cpp���� ��������

    showRectangles("������:", rectangles, numRectangles);

    selectionSortRectangles(rectangles, numRectangles);

    showRectangles("������:", rectangles, numRectangles);

    system("pause");
    return 0;
}