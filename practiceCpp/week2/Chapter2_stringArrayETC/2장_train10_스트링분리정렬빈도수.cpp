/*
📌 C 스타일 문자열 변환 내용
C++ strtok(): **"string tokenize"**의 약어
    /*
    char *strtok(char *str, const char *delim);
        str: 분할할 문자열의 주소를 전달
        첫 호출에서는 문자열을 전달하고, 이후 호출에서는 NULL을 전달

        delim: 분할 기준이 되는 문자 집합(구분자, delimiter)을 전달합니다.


문자열 앞뒤 공백 제거
strtok()는 자동으로 공백을 제거하지 않으므로 공백을 제거하는 함수(trim())를 구현

정렬 C++ qsort() 사용
qsort()를 사용하여 사전순 정렬

특정 문자열 검색 strcmp() 사용
strcmp()를 사용하여 특정 문자열과 일치하는지 확인
*/
/*
C 코딩으로 스트링 split()하여 정수 처리 코드가 복잡 > 간결한 코딩이 필요 :
해법: string 클래스와 vector<string> 사용이 필요
*/
#include <iostream>
#include <cstring> // strtok, strcmp, qsort, strlen
#define SIZE 20
using namespace std;
char* trim(char*);
int splitStrings(char*, char* []);
int findAllString(char* array[], int size, const char* target);
char** bubbleSort(char* arr[5], int n);
void freeMemory(char** p, int n);
void freeStrdup(char* d[SIZE], int n);
void showData(char* message, char* data[SIZE], int n);
int main() {
    char s[] = "한국, 일본,미국,중국 , 미국 ,   독일   ,   프랑스, 미국 ";  // 원본 문자열 (배열 사용)
    char* sortedArray[SIZE]; // 분리된 문자열 저장 배열 (최대 20개까지 저장 가능)

    // 문자열을 분리하고 정렬
    int size = splitStrings(s, sortedArray);

    // 정렬된 배열 출력
    showData("Splited 문자열", sortedArray, size);
    //*
    char** result = bubbleSort(sortedArray, size);
    showData("정렬후 :: ", result, size);
    freeStrdup(sortedArray, size);
    // 특정 문자열 찾기
    //*
    const char* target = "미국";
    int frequency = findAllString(result, size, target);
    printf("빈도수 =  %d", frequency);
    freeMemory(result, size);
    // */
    system("pause");
    return 0;
}

