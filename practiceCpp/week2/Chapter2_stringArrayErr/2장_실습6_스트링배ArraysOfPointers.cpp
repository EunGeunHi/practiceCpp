#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 10
#define ROWS 5

/*
char  *strings[10] = { "apple", "banana", "orange", "grape", "kiwi" }; 
strcpy(strings[0],strings[1]); 오류가 나나? 이유는? 오류다 > 스트링 리터럴을 포인터가 가리킨다
char  (*strings)[10] = { "apple", "banana", "orange", "grape", "kiwi" };>> 포인터가 배열을 가리킨다 
*/
void bubbleSort(char* arr[ROWS], int n);
void showData(char* message, char* data[ROWS], int n);
int main() {
    //스트링 배열 초기화 방법 2가지 구분
    //char strings[ROWS][SIZE] = { "apple", "banana", "orange", "grape", "kiwi" };//실습5에서 연습
    char  *strings[ROWS] = { "apple", "banana", "orange", "grape", "kiwi" };//포인터가 스트링을 가리킬 때 주의할 점

    int n = sizeof(strings) / sizeof(strings[0]);
    printf("\nn=%d", n);//n = 5로 계산되는 이유를 알아야 한다

    showData("정렬전", strings, ROWS);

    bubbleSort(strings, ROWS);
    showData("정렬gn", strings, ROWS);

    system("pause");
    return 0;
}
void bubbleSort(char* arr[ROWS], int n) { //char **arr와 같다. 
    // char arr[][10] 표현은 char (*arr)[SIZE]와 같다
    char temp[10];
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            if (strcmp(arr[i], arr[j]) > 0) {
                strcpy(temp, arr[i]);
                strcpy(arr[i], arr[j]);
                strcpy(arr[j], temp);//access 위반 에러 발생
            }
        }
    }
}
void showData(char* message, char* data[ROWS], int n) {
    printf("%s\n", message);
    for (int i = 0; i < n; i++) {
        printf("%s\n", *(data + i));
    }
}