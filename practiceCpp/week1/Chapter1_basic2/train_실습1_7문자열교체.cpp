/*
strstr()은 "string search" 또는 **"string string"**의 약자
*/

#include <iostream>
#include <cstring>  // strcat, strcpy, strncpy, strstr

using namespace std;



// 문자열 교체 함수 
void replaceString(char* baseString, const char* target, const char* replacement, char* result) {
    char* pos = baseString;
    int targetLen = strlen(target);
    int replacementLen = strlen(replacement);

    result[0] = '\0';  // 결과 문자열 초기화


}

int main() {
    char s[100] = "자바 코딩, 파이썬 코딩, C 코딩, C# 코딩"; // 원본 문자열
    char newString[150];  // 문자열 추가 후 저장할 공간
    char finalString[200];  // 문자열 교체 후 저장할 공간

    // 서브스트링 추가
    strcpy(newString, s);  // 원본 복사
    addSubstring(newString, " PCCP 시험: 11월 23일");

    // 문자열 교체
    replaceString(newString, "코딩", "프로그래밍", finalString);

    // 결과 출력
    cout << finalString << endl;
    system("pause");
    return 0;
}
