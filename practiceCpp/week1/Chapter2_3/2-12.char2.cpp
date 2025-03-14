//2-12. char2.cpp: 실습예제 2.12
/*
char p[10], char *q, char *r[10]의 차이점
메모리 할당 방식과 접근 방식이 다르다
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void strProcess(char* p[], char* q[], char r[], char s[]) {
    printf("*p = %s, *q = %s\n", *p, *q);
    printf("r = %s\n", r);

    strcpy(s, r);

    printf("\n\n*p[]->s[] 문자열 복사후\n");
    strcpy(s, *p);
    printf("s = %s, *p = %s\n", s, *p);
    printf("strcmp(s, *p) = %d (0->같다, 0아닌숫자->다르다)\n", strcmp(s, *p));
}

int main(void) {
    char* i = "monday";//데이터 영역내의 .rodata (read only 데이터 영역) 주소를 포인터 i가 가리킨다
    char* j;
    char* p[10];
    char* q[10];
    char r[10] = "sunday";//스택(Stack) 영역에 r이라는 배열을 생성하고, 문자열 "sunday"의 내용을 스택(Stack) 영역에 복사
    char s[10];
    //*i = "good";
    j = i;
    //s = r;//s는 lvalue가 아니다 배열 이름으로 상수이다.
    //strcpy(i, "saturday");//runtime 오류 발생, *i는 상수 값 "monday"를 가짐, 변경 불가
    strcpy(r, "friday");
    *p = "wednesday";//p는 array of pointer => p[0]이 포인터이고 wednesday를 가리킨다 
    *q = "thursday";

    strProcess(p, q, r, s);

    system("pause");
    return 0;
}
