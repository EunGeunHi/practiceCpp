//2-2. pointerArray.cpp: 실습 예제 2.2	::주석풀고 달면서 실행하고 에러를 이해할 것 

#include <stdio.h>
#include <stdlib.h>

void testPointers(int a[], int* b, int* c[]) {
	// 주석1
	//*
	//*b = 10;//pointer 변수b의 값은 run-time에 초기화될 수 없다 - 이해 필요
	b = a;
	*b = 10;
	//*b = a; // int * 형식의 값을 int으로 (entity로) 치환할 수 없다
	printf("a의 주소: %p\n", a);
	printf("b의 주소: %p\n", b);
	printf("a[0] = %d\n", a[0]);
	printf("*b = %d\n\n", *b);

	printf("&a[0]: %p\n", &a[0]);
	printf("c[0]: %p\n", c[0]);
	printf("&a[4]: %p\n", &a[4]);
	printf("c[1]: %p\n", c[1]);
	printf("*c[0] = %d, *(c[0]+1) = %d, *(c[1]+1) = %d\n\n", *c[0], *(c[0] + 1), *(c[1] + 1));
}

int main(void) {
	int a[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	int* b;
	int* c[3]; //array of pointers - 연산자 우선 순위: [] 연산이 * 보다 높다

	b = a;		//주소 할당 
	*b = 10;	//값 할당 

	//c = a; // c는 lvalue가 아니다(정확히는 맞는데 변경할수 있는 lvalue가 아님, 배열 이름은 상수). c는 pointer들의 array 이름으로 상수이다
	//*c = a; // 주석을 풀고 실행시에는 다음 line 을 주석 처리하여 실행-비정상 동작을 확인
	//주석 해제시에는 line 26을 주석처리하여 실행
	c[0] = &a[0];
	c[1] = &a[4];
	c[2] = &a[8];

	testPointers(a, b, c);

	system("pause");
	return 0;
}
