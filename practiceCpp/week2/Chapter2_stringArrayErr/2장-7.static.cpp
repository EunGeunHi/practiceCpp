// 2장-7 static.cpp
#include <stdio.h>
#include <stdlib.h>
static int total = 0;   // static definition, internal linkage, static storage duration
//**Internal linkage(내부 연결)**이란, 해당 변수가 선언된 파일 내에서만 접근할 수 있도록 제한하는 속성을 의미
//다른 파일에서 접근하려면 external 선언
void fcn(void);

void main() {
    fcn();
	fcn();
	fcn();
	printf("main():: total = %d\n", total);
	system("pause");
}

void fcn() {
    static int counter = 0;//static 변수로 데이터 영역에 저장된다 
    counter++;
	printf("fcn::counter = %d\n\n", counter);
	total += counter;
}