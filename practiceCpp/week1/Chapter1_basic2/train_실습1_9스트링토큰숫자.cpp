/*
공백을 기준으로 문자열을 분리 : strtok()을 사용하여 공백(" ")을 기준으로 문자열을 분리
문자열 배열 정렬 : C++의 qsort()를 사용하여 사전순 정렬
문자열을 정수로 변환: atoi()를 사용하여 문자열을 정수로 변환
정수 배열 정렬 : qsort()를 사용하여 정수 배열을 오름차순 정렬
*/
#include <iostream>
#include <cstring>  // strtok, strcmp, atoi, qsort
#include <cstdlib>  // atoi

using namespace std;

// 문자열 비교 함수 (qsort용)
int compareStrings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

// 정수 비교 함수 (qsort용)
int compareIntegers(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// 문자열을 공백(" ")으로 분리하여 배열에 저장하고 정렬하는 함수
int splitSortString(char* input, char* stringArray[], int maxTokens) {
    int count = 0;
    //내부적으로 전역 또는 정적(static) 상태를 유지하는 방식으로 동작합니다.
    //strtok()를 호출할 때마다 이전 호출에서 분할된 위치를 기억하고, 
    //다음 호출에서 다음 토큰을 반환합니다.
    char* token = strtok(input, " ");  // 공백을 기준으로 문자열 분리

    while (token != nullptr && count < maxTokens) {
        stringArray[count++] = token;  // 분리된 문자열 저장
        token = strtok(nullptr, " ");  // 다음 토큰
    }

    // 문자열 배열 정렬 (사전순 정렬)
    qsort(stringArray, count, sizeof(char*), compareStrings);

    return count;  // 분리된 문자열 개수 반환
}

// 문자열 배열을 정수 배열로 변환하고 정렬하는 함수
void convertSortToIntArray(char* stringArray[], int intArray[], int size) {
    // 문자열 배열을 정수 배열로 변환
    //atoi() 사용

    // 정수 배열 정렬 (오름차순)

}



int main() {
    char input[] = "12 111 911 921 94 23 214 222";  // 원본 문자열
    char* sortedStringArray[20];  // 분리된 문자열 저장 배열 (최대 20개까지 저장 가능)
    int sortedIntArray[20];  // 정수 배열

    // 문자열을 공백으로 분리하고 정렬
    int size = splitSortString(input, sortedStringArray, 20);

    // 정렬된 문자열 배열 출력
    cout << "Sorted String Array:" << endl;
    printStringArray(sortedStringArray, size);

    // 문자열 배열을 정수 배열로 변환 및 정렬
    convertSortToIntArray(sortedStringArray, sortedIntArray, size);

    // 정렬된 정수 배열 출력
    cout << "Sorted Integer Array:" << endl;
    printIntArray(sortedIntArray, size);
    system("pause");
    return 0;
}
