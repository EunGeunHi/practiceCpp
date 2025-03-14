//2-8. increase.cpp
// 1차원 배열, 2차원 배열의 값을 증가시키는 함수 호출 -skip
#include <stdio.h>
#include <stdlib.h>
#define ROW 3
#define COL 5
void increase(int (*a)[COL], int size);
void increaseArrayPtr(int* [], int);

void main(void)
{
	int a2[ROW][COL] = { {1,2,3,4,5}, {11,12,13,14,15}, {21,22,23,24,25} };

	increase(a2, ROW);// int (*)[] 형식의 parameter가 int []와 호환되지 않는다

	printf("\n");
	int a[2][3] = { 1,2,3,4,5,6 };
	int* b[2] = { a[0], a[1] };
	increaseArrayPtr(b, 2);
	printf("\n");
	//*/
	system("pause");
}
void increaseArrayPtr(int *x[], int n) //array of pointer를 사용한 parameter passing 
//int (*x)[]은 오류발생 
{
	printf("\narray of pointer를 사용한 출력\n");
	for (int i = 0; i < n; i++)
	{
		//printf(" %d", *(x[i] + 1));
		for (int j = 0; j < 3; j++)
			printf(" %d", *(x[i] + j));
		printf("\n");
	}

}
void increase(int (*a)[COL], int size) {
	printf("\npointer to array를 사용한 출력\n");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < COL; j++)
			printf(" %d", *(a[i] + j));
		printf("\n");
	}
}
