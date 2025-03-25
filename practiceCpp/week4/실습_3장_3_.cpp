/*
vs에는 포함안돼있음
5,6장 학습후 아래 실습 코드를 완성할 수 있는 스킬을 확보해야 한다.
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib> 
#include <windows.h>

using namespace std;

class Rectangles { //맛보기 예제
private:
    int leftBottomX;
    int leftBottomY;
    int width;
    int height;
public:
    //생성자
    Rectangles(int x, int y, int w, int h) :
        leftBottomX(x), leftBottomY(y), width(w), height(h) {}
    void showRectangles();
    int compareRectangless(const Rectangles* b);
    void swap(Rectangles* b);
};

void Rectangles::showRectangles() {
    printf("[%d, %d, %d, %d]\n", leftBottomX, leftBottomY, width, height);
}

int Rectangles::compareRectangless(const Rectangles* b) {

}
void Rectangles::swap(Rectangles* b) {

}
void showRectangless(string message, Rectangles* rectangles[], int numRectangless) {

}
void selectionSortRectangless(Rectangles* rectangles[], int numRectangless) {

}
int main(void) {
    SetConsoleOutputCP(CP_UTF8);//한글깨지는 문제 해결하기 위해 사용 
    const int numRectangless = 5;
    Rectangles* rectangles[numRectangless] = {
        new Rectangles(3, 5, 10, 15),
        new Rectangles(3, 5, 10, 12),
        new Rectangles(3, 5, 6, 10),
        new Rectangles(3, 6, 7, 8),
        new Rectangles(2, 3, 9, 14)
    };

    showRectangless("정렬전:", rectangles, numRectangless);

    selectionSortRectangless(rectangles, numRectangless);

    showRectangless("정렬후:", rectangles, numRectangless);

    for (int i = 0; i < numRectangless; ++i) {
        delete rectangles[i];
    }

    system("pause");
    return 0;
}
