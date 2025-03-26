#include <iostream>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <windows.h>
using namespace std;

typedef struct Rect {
    int leftBottomX;
    int leftBottomY;
    int width;
    int height;
    char* name;
}Rectangle1;


int compareRectangles(const Rectangle1* a, const Rectangle1* b) { //1순위 x좌표 > y > width > height > name 비교
    int x_compare = a->leftBottomX - b->leftBottomX;
    int y_compare = a->leftBottomY - b->leftBottomY;
    int width_compare = a->width - b->width;
    int height_compare = a->height - b->height;
    int name_compare = strcmp(a->name, b->name);

    if (x_compare != 0)
        return x_compare;
    else if (y_compare != 0)
        return y_compare;
    else if (width_compare != 0)
        return width_compare;
    else if (height_compare != 0)
        return height_compare;
    else
        return name_compare;
}

void showRectangle(Rectangle1 r) {
    printf("[%d, %d, %d, %d, %s]\n", r.leftBottomX, r.leftBottomY, r.width, r.height, r.name);
}
void showRectangles(string message, Rectangle1* rectangles[], int numRectangles) {
    cout << message << endl;
    for (int i = 0; i < numRectangles; i++)
        showRectangle(*rectangles[i]);
}

void changeRectangle(Rectangle1* r, char* newName) {
    cout << "r1 name is changed" << endl;
    r->name = strdup(newName);
}

void swap(Rectangle1* rect[], int i, int j) {
    Rectangle1* temp = rect[i];
    rect[i] = rect[j];
    rect[j] = temp;
}
void selectionSortRectangles(Rectangle1* rectangles[], int numRectangles) {
    for (int i = 0; i < numRectangles - 1; i++) {
        int temp = i;
        for (int j = i + 1; j < numRectangles; j++)
            if (compareRectangles(rectangles[temp], rectangles[j]) < 0) temp = j;
        swap(rectangles, i, temp);
    }

}
int main(void) {
    SetConsoleOutputCP(CP_UTF8);//한글깨지는 문제 해결하기 위해 사용 
    const int numRectangles = 5;
    Rectangle1 r1 = { 3, 5, 10, 15,"r1" };
    Rectangle1 r2 = { 1, 2, 8, 12 ,"r2" };
    Rectangle1 r3 = { 1, 2, 8, 10,"r3" };
    Rectangle1 r4 = { 3, 5, 10, 15 ,"r4" };
    Rectangle1 r5 = { 3, 5, 10, 14,"r5" };
    Rectangle1* rectangles[numRectangles] = { &r1,&r2,&r3,&r4,&r5 };

    showRectangles("정렬전:", rectangles, numRectangles);
    changeRectangle(&r1, "square");


    showRectangle(r1);
    showRectangles("변경후:", rectangles, numRectangles);
    selectionSortRectangles(rectangles, numRectangles);

    showRectangles("정렬후:", rectangles, numRectangles);

    system("pause");
    return 0;
}