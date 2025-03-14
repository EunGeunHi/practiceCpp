//2-5. arr2.cpp: 실습 예제 2.5
#include <stdio.h>
#include <stdlib.h>
//배열 이름에 대하여 pointer 표현식을 사용하여 접근

// 1차원 배열 출력 함수
void print1DArray(int* arr, int size) {
    printf("\n1차원 배열\n");
    printf("a1[0] = %d\n", arr[0]);
    printf("*(arr) = %d\n\n", *(arr));

    printf("a1[1] = %d\n", arr[1]); // 다음 element
    printf("*(arr+1) = %d\n\n", *(arr + 1)); // 다음 element
}

// 2차원 배열 출력 함수
void print2DArray(int(*arr)[5], int rows, int cols) {
    printf("\n2차원 배열\n");
    printf("a2[0][0] = %d\n", arr[0][0]);
    printf("(*arr)[0] = %d\n\n", (*arr)[0]);

    printf("a2[1][3] = %d\n", arr[1][3]);
    printf("(*(arr+1))[3] = %d\n\n", (*(arr + 1))[3]);

    printf("a2[1][2] = %d\n", arr[1][2]);
    printf("*(*(arr+1)+2) = %d\n\n", *(*(arr + 1) + 2));

    printf("a2[0][0] = %d\n", arr[0][0]);
    printf("**(arr+0) = %d\n\n", **(arr + 0));
}

int main() {
    // 1차원 배열 선언 및 초기화
    int a1[5] = { 5, 4, 3, 2, 1 };
    // 2차원 배열 선언 및 초기화
    int a2[3][5] = { {0, 5, 10, 15, 20}, {1, 6, 11, 16, 21}, {2, 7, 12, 17, 22} };

    printf("배열을 함수로 전달하여 테스트\n");

    // 1차원 배열 함수 호출
    print1DArray(a1, 5);

    // 2차원 배열 함수 호출
    print2DArray(a2, 3, 5);

    printf("\n포인터 주소의 증가와 값의 증가\n");
    printf("*(a1+1) = %d\n", *(a1 + 1));
    printf("*(*(a2+1)+1) = %d\n", *(*(a2 + 1) + 1));
    printf("\n");

    system("pause");
    return 0;
}
