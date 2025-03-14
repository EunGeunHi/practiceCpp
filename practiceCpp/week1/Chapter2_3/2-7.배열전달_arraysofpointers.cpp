//2-7. arr4.cpp
//array of pointers의 초기화 사용

#include <stdio.h>
#include <stdlib.h>

// 포인터 배열을 초기화하는 함수
void initializePointerArray(int* b, int** q, int qSize) {
    q[0] = b; // b의 시작 주소
    q[1] = b + 2;
    q[2] = b + 4;
    q[3] = b + 6;
    q[4] = b + 8;

    // 특정 위치에 값 변경
    q[3][2] = 55; // b[8]을 55로 변경
}

// 포인터 배열을 출력하는 함수
void printPointerArray(int** q, int qSize) {
    printf("------ 포인터 배열 출력 ------\n");
    printf("q[0]: %p, q[1]: %p, q[2]: %p, q[3]: %p, q[4]: %p\n",
        q[0], q[1], q[2], q[3], q[4]);

    printf("*q[0]: %d\n", *q[0]);
    printf("*q[1]: %d\n", *q[1]);
    printf("*q[2]: %d\n", *q[2]);
    printf("*q[3]: %d\n", *q[3]);
    printf("*q[4]: %d\n", *q[4]);
    printf("q[3][2]: %d, q[4][0]: %d\n", q[3][2], q[4][0]);
}

int main() {
    int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int* q[5]; // 포인터 배열 선언

    // 포인터 배열 초기화
    initializePointerArray(b, q, 5);

    // 포인터 배열 출력
    printPointerArray(q, 5);

    // b 배열 전체 출력
    printf("\n------ b 배열 출력 ------\n");
    for (int i = 0; i < 10; i++) {
        printf(" %d", b[i]);
    }
    printf("\n");

    system("pause");
    return 0;
}
