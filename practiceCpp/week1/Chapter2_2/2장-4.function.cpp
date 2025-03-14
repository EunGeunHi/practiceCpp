// 2장-4 function.cpp: 함수 선언과 정의 
#include <stdio.h>
#include <stdlib.h>
// prototype declaration
#define COLS 4
#define ROWS 3
int sum(int a[][COLS], int rows);

void main () {
	int table[ROWS][COLS] = {1,2,3,4,5,6,7,8,9,10,11,12};
	int total;
	total = sum(table, ROWS);
	printf("total = %d\n", total);
	system("pause");
}
int sum(int ar[][COLS], int rows)//배열을 전달받는 parameter를 기억해야 한다.
// COLS를 지정해야 한다 - 각 행의 크기를 모르기 때문이다, 단순히 포인터 ar만 받는다 
//int sum(int (*ar)[COLS], int rows)
{
	int r, c;
	int total = 0;
	/*
	for (r = 0; r <rows; r++)
		for (c = 0; c <COLS; c++)
			total += ar[r][c];
	*/
	//pointer를 사용
	for (r = rows; r > 0; r--, ar++)
		for (c = 0; c < COLS; c++)
			total += (*ar)[c];
	return total;
}