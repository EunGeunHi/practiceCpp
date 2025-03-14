#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
* 스트링 배열을 함수로 전달할 때 이중포인터를 사용하는 방법
*/
void showData(char* message, char* data[5], int n);
void swap(char* p[5], int i, int j);
char** bubbleSort(char* arr[5], int n);
void freeMemory(char** p, int n);
int main() {
	char* strings[5] = { "복숭아", "포도", "감", "산딸기", "대추" };

	int n = sizeof(strings) / sizeof(strings[0]);

	showData("정렬전", strings, n);

	char** result = bubbleSort(strings, n);
	showData("정렬후", result, n);
	freeMemory(result, n);
	system("pause");
	return 0;
}



