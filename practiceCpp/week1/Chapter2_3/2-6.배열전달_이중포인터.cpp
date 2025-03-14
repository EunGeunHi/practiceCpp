//2-6. arr3.cpp - double pointer 사용: 실습예제 2.6
/*
*A의 사용 실습, *A +1 은 어디를 가리키나?
*/

#include <stdio.h>
#include <stdlib.h>

// 2차원 배열을 함수로 전달하여 출력하는 함수
void print2DArray(int(*arr)[4], int rows, int cols) {
	printf("\n------ 2차원 배열 -------\n");
	printf("A: %p\n", arr);
	printf("*A: %p\n", *arr);
	printf("*(A+1): %p\n", *(arr + 1));
	printf("*(*A+0): %d\n", *(*arr + 0));
	printf("*(*A+1): %d\n", *(*arr + 1));
	printf("**(A+1): %d\n", **(arr + 1));
	printf("**A: %d\n", **arr);
}

// 이중 포인터를 활용한 테스트 함수
void testDoublePointer(int** ptr, int cols) {
	printf("\n------ 이중 pointer: test = &p -------\n");
	printf("**ptr: %d\n", **ptr);
	printf("*(*ptr + 0): %d\n", *(*ptr + 0));
	printf("*(*ptr + 1): %d\n", *(*ptr + 1));
	printf("*(*ptr + 2): %d\n", *(*ptr + 2));
	printf("*(*ptr + 3): %d\n", *(*ptr + 3));
	printf("*(*ptr + 4): %d\n", *(*ptr + 4));
	printf("*(*ptr + 5): %d\n", *(*ptr + 5));
	printf("ptr[0][0]: %d\n", ptr[0][0]);
	printf("ptr[0][4]: %d\n", ptr[0][4]);
}

int main() {
	int A[3][4] = { {11,12,13,14}, {21,22,23,24}, {31,32,33,34} };
	int* p = *A; // *A는 첫 번째 행의 포인터
	//int *p = A; // error 'int (*)[4]'으로 'int *'을 초기화할  수 없다.
	//int* p = *A; // *A= int[4], A= int[3][4], p= int *
	// 2차원 배열을 함수에 전달하여 출력
	print2DArray(A, 3, 4);

	// 이중 포인터 활용 테스트
	int** test;
	test = &p; // p를 이중 포인터로 초기화
	//*test = *A;//variable 'test'가 초기화없이 사용할 수 없다
	testDoublePointer(test, 4);


	//주석3
	printf("\n------ 이중 pointer: p2 = &pt  -------\n");
	int* pt;
	int ar2[3][2] = { {1,3},{5,7},{9,11} };// int (*)[2]
	int** p2;  // a pointer to a pointer   
	//pt = &ar2[0][0];
	pt = ar2[0]; // both pointer-to-int
	//pt = ar2; // int (*)[3] 형식의 값을 int * 형식의 값으로 치환할 수 없다
	p2 = &pt;         // both pointer-to-int *
	//*p2 = ar2[0];     // both pointer-to-int *
	printf("*pt = %d, **p2 = %d\n\n", *pt, **p2);
	(*p2)++;
	printf("*pt = %d, **p2 = %d\n\n", *pt, **p2);
	//p2 = ar2; // int (*)[2] 형식의 값을 int ** 형식의 값으로 치환할 수 없다
	//*/
	/*
	int **p2 = (int **)malloc(3 * sizeof(int *)); // 행(3개) 할당

    for (int i = 0; i < 3; i++) {
        p2[i] = (int *)malloc(2 * sizeof(int));  // 각 행에 열(2개) 할당
		//p2는 arrays of pointers > p2[0],p2[1],...
		//*d[]와 호환된다 
    }
	*/
	system("pause");
	return 0;
}
