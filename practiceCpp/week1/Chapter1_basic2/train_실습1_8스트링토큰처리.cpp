/*
📌 C 스타일 문자열 변환 내용
C++ strtok(): **"string tokenize"**의 약어
char* strtok(char* str, const char* delim);
strtok()을 사용하여 문자열을 "," 기준으로 분리

문자열 앞뒤 공백 제거
strtok()는 자동으로 공백을 제거하지 않으므로 공백을 제거하는 함수(trim())를 구현

정렬 C++ qsort() 사용
qsort()를 사용하여 사전순 정렬

특정 문자열 검색 strcmp() 사용
strcmp()를 사용하여 특정 문자열과 일치하는지 확인
*/
#include <iostream>
#include <cstring> // strtok, strcmp, qsort, strlen

using namespace std;

// 문자열 앞뒤 공백 제거 함수
void trim(char* str) {

}

// 문자열 비교 함수 (qsort용)
int compareStrings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

// 문자열을 콤마(,)로 분리하고 정렬하는 함수
int splitAndSort(char* baseString, char* list[], int maxTokens) {
    int count = 0;
    char* token = strtok(baseString, ",");  // 콤마를 기준으로 문자열 분리

    while (token != nullptr && count < maxTokens) {
        list[count] = token;
        trim(list[count]);  // 공백 제거

        count++;
        token = strtok(nullptr, ",");  // 다음 토큰
    }

    // 정렬 (사전순)
    qsort(list, count, sizeof(char*), compareStrings);

    return count;  // 분리된 문자열 개수 반환
}

// 배열에서 특정 문자열을 찾는 함수 (빈도수 반환)


int main() {
    char s[] = "한국, 일본,미국,중국 , 미국 ,   독일   ,   프랑스, 미국 ";  // 원본 문자열 (배열 사용)
    char* sortedArray[20]; // 분리된 문자열 저장 배열 (최대 20개까지 저장 가능)

    // 문자열을 분리하고 정렬
    int size = splitAndSort(s, sortedArray, 20);

    // 정렬된 배열 출력
    cout << "Sorted Array:\n";
    for (int i = 0; i < size; i++) {
        cout << sortedArray[i] << " ";
    }
    cout << "\nArray length = " << size << endl;

    // 특정 문자열 찾기
    const char* target = "미국";
    int frequency = findAllString(sortedArray, size, target);
    cout << "빈도수 = " << frequency << endl;
    system("pause");
    return 0;
}
