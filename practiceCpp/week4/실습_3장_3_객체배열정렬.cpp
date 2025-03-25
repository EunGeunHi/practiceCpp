/*
* C++ class 맛보기 예제 
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib> 
#include <windows.h>
/*
* C의 struct vs C++의 class 유사점
* 데이터 묶음>	둘 다 여러 개의 변수(데이터)를 하나로 묶을 수 있음  :데이터필드,멤버
* 인스턴스 생성> 변수 선언을 통해 인스턴스를 생성할 수 있음         :인스턴스=객체, 생성자->변수-인스턴트
* 멤버 접근> . 연산자 또는 -> 연산자를 통해 멤버 접근 가능          
* 포인터 사용 가능>	구조체/클래스를 포인터로 사용할 수 있음
*
* 차이점: C의 struct :: C++의 class
* struct: 기본 접근 제어자	없음 (모든 멤버는 public), class: private
* struct: 멤버 함수	지원 안 함 (함수 포인터로 우회 가능), class: 지원함
* struct: 상속 (Inheritance)	지원 안 함, class: 지원함
* struct: 캡슐화/다형성/추상화	불가능, class: 객체지향(OOP) 기능 완전 지원
* struct: 생성자/소멸자	없음, class: 있음 (constructor, destructor)
* struct: 연산자 오버로딩	없음, class: operator overloading 가능
* struct: template 사용	없음, class: template 가능
*/
using namespace std;
//Rectangle 이름은 Window.h에서 사용하므로 복수 클래스 이름 사용
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
    int LBXCompare = leftBottomX - b->leftBottomX;
    int LBYCompare = leftBottomY - b->leftBottomY;
    int widthCompare = width - b->width;
    int heightCompare = height - b->height;
    if (LBXCompare != 0)
        return LBXCompare;
    else if (LBYCompare != 0)
        return LBYCompare;
    else if (widthCompare != 0)
        return widthCompare;
    return heightCompare;
}
void Rectangles::swap(Rectangles* b) {
    std::swap(leftBottomX, b->leftBottomX);
    std::swap(leftBottomY, b->leftBottomY);
    std::swap(width, b->width);
    std::swap(height, b->height);
}
void showRectangless(string message, Rectangles* rectangles[], int numRectangless) {
    cout << message << ": " << endl;
    for (int i = 0; i < numRectangless; ++i) {
        rectangles[i]->showRectangles();
    }
    cout << endl;
}
void selectionSortRectangless(Rectangles* rectangles[], int numRectangless) {
    // int compareRectangless(const Rectangles* b);를 사용한 정렬
    for (int i = 0; i < numRectangless - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < numRectangless; ++j) {
            if (rectangles[j]->compareRectangless(rectangles[minIndex]) < 0) {
                minIndex = j;

            }
        }
        if (minIndex != i) {
            rectangles[i]->swap(rectangles[minIndex]);
        }
    }
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
/*new:
  1.heap에 메모리 공간 할당(타입을 보고, 구조체나 클래스의 경우 멤버를 보고)
  2.할당된 공간의 시작주소를 반환*/

    showRectangless("정렬전:", rectangles, numRectangless);

    selectionSortRectangless(rectangles, numRectangless);

    showRectangless("정렬후:", rectangles, numRectangless);

    for (int i = 0; i < numRectangless; ++i) {
        delete rectangles[i];
    }

    system("pause");
    return 0;
}
