/*
2차원 배열을 함수로 전달하여 함수에서 계산하여 전달하는 방식
=> 중복 코딩 발생: 간결한 코딩 개선이 필요
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define AROWS 3
#define ACOLS 4
#define BROWS 4
#define BCOLS 5
#define CROWS 3
#define CCOLS 5
#define DROWS 3
#define DCOLS 4
#define EROWS 5
#define ECOLS 4
void getMatrix(int matrix[][ACOLS], int rows);
void getMatrix_b(int matrix[][BCOLS], int rows);
void showMatrix(int matrix[][ACOLS], int rows);
void showMatrix_b(int matrix[][BCOLS], int rows);
void showMatrix_c(int matrix[][CCOLS], int rows);
void addMatrix(int a1[][ACOLS], int rows1, int a2[][ACOLS], int rows2, int a3[][ACOLS], int rows3);

void multiplyMatrix(int a[][ACOLS], int rows_a, int b[][BCOLS], int rows_b, int c[][CCOLS], int rows_c);
void transposeMatrix(int b[][BCOLS], int rows_b, int e[][ECOLS], int rows_e);
void multiplyTransposeMatrix(int a[][ACOLS], int rows_a, int e[][ECOLS], int rows_e, int c[][CCOLS], int rows_c);
int main() {
	srand(42);//seed 값이 주어지면 난수 생성 결과가 항상 같게 만들어짐

	int a[AROWS][ACOLS], a2[AROWS][ACOLS], b[BROWS][BCOLS], c[CROWS][CCOLS], d[DROWS][DCOLS], e[DROWS][DCOLS];

	getMatrix(a, AROWS);
	getMatrix(a2, AROWS);

	printf("Matrix A1:\n");
	showMatrix(a, AROWS);

	printf("Matrix A1:\n");
	showMatrix(a2, AROWS);
	addMatrix(a, AROWS, a2, AROWS, d, AROWS);
	//int(*result)[ACOLS] = addMatrix(a, AROWS, a2, AROWS);
	printf("Matrix E = A + A2:\n");

	printf("Matrix Result:\n");
	showMatrix(d, AROWS);

	getMatrix_b(b, BROWS);
	printf("Matrix B:\n");
	showMatrix_b(b, BROWS);
	multiplyMatrix(a, AROWS, b, BROWS, c, CROWS);
	printf("Matrix C = (A * B):\n");
	showMatrix_c(c, CROWS);

	transposeMatrix(b, BROWS, e, EROWS);
	printf("Transpose Matrix E = transpose(B)\n");
	showMatrix_c(e, EROWS);

	multiplyTransposeMatrix(a, AROWS, e, EROWS, c, CROWS);
	printf("Matrix C = (A * transpose(B)):\n");
	showMatrix_c(c, CROWS);

	system("pause");
	return 0;
}

