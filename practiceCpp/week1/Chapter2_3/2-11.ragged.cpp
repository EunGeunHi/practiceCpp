//2-11. ragged.cpp: 실습 예제 2.11
// 동적할당 받은 2차원 배열의 경우 1차원 배열을 먼저 해제한 후 double pointer를 free해야 함.
// raggedTable에 치환하는 문장을 실습 코드로 추가

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void raggedTable2();
void initializeRaggedArray(int**T1, int rows);
void freeRaggedArray(int** T1, int rows);

int main() {
	int* T1[4];
	int rows = 4;

	srand(time(NULL));
	initializeRaggedArray(T1, rows);

	int cnt = 1;
	printf("T1[][]의 원소 값\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cnt; j++) {
			printf("%d ", T1[i][j]);
		}
		printf("\n");
		cnt++;
	}
	printf("\n");

	printf("**T1 = %d\n", **T1);
	printf("**(T1+1) = %d\n", **(T1 + 1));
	printf("*(*(T1+1)+1) = %d\n", *(*(T1 + 1) + 1));

	freeRaggedArray(T1, rows);

	raggedTable2();
	system("pause");
	return 0;
}

void initializeRaggedArray(int**T1, int rows) {
	//T1 = (int**)malloc(rows * sizeof(int*));
	for (int i = 0; i < rows; i++) {
		T1[i] = (int*)malloc((i + 1) * sizeof(int));
		// ptr = (int*)malloc(10 * sizeof(int));
		//초기화되지 않음 (쓰레기 값)

		for (int j = 0; j < i + 1; j++) {
			T1[i][j] = rand() % 100;
		}
	}
}

void freeRaggedArray(int** T1, int rows) {
	for (int i = 0; i < rows; i++) {
		free(T1[i]);
	}
	//free(T1);
}

void raggedTable2() {
	char** T3;
	int row, col;
	int rowIndex;
	static char counter = 'A';
	printf("행의 수를 입력 :");
	scanf("%d", &row);
	T3 = (char**)calloc(row, sizeof(char*));
	for (rowIndex = 0; rowIndex < row; rowIndex++) {
		printf("%d행에 대한 열의 수 : ", rowIndex);
		scanf("%d", &col);
		T3[rowIndex] = (char*)calloc(col + 1, sizeof(char));
		//ptr = (int*)calloc(10, sizeof(int));
		//0으로 초기화

		for (int j = 0; j < col; j++) {
			T3[rowIndex][j] = counter++;
			printf("%d ", T3[rowIndex][j]);
		}
		printf("\n");
	}
	for (rowIndex = 0; rowIndex < row; rowIndex++) {
		free(T3[rowIndex]);
	}
	free(T3);
}
