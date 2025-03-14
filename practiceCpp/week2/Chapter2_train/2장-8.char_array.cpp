// 2장-8 char_array.cpp
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    char p2[] = "Good";//p2의 주소는 스택영역
    char* ptr2 = "Good";//포인터는 데이터영역

    printf(" % p\n", "Good");//string literal은 데이터 영역
    
    printf(" % s, % s\n", p2, ptr2);
    printf(" % p, % p, % p\n", p2, ptr2, "Good");

    char *num[5];
    char **p;
    char **q;
    char *t;
    //t = num;//char**을 char *에 치환할 수 없다
    //num = t;
	num[0] = "One";
    num[1] = "Two";
    num[2] = "Three";
    num[3] = "Four";
    num[4] = "Five";
	p = num;//이중 pointer를 사용하는 의미 파악 필요
	printf("*p = %s\n", *p);
    printf("Number\n");
    p = num + 4;
    for(q = num; q <= p; q++)
        printf("*q = %s\n", *q);
    char *ptr;
    char w[10];
    //ptr = w;
    printf("\n w[10] = string 입력값::");
    scanf("%s", ptr);
    printf("*ptr = %s\n", ptr);
	system("pause");
    return 0;
}
