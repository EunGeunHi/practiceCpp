//2-3. pointer_2dimensionArray.cpp: 실습예제 2.3

#include <stdio.h>
#include <stdlib.h>

void testPointers(int a[][4], int* b, int* c[], int(*d)[4]) { //int a[][]->오류: a[]는 포인터로(*a), 가르키는 cols을 지정해야함
	printf("*b : %d\n", *b);
	printf("b[0] : %d\n", b[0]);
	printf("*(++b) : %d\n", *(++b));
	printf("*(++b) : %d\n\n\n", *(++b));
	//주석1

	//c = a; // c는 식이 치환할 수 있는 lvalue가 아니다.
	c[0] = a[0];//c[0]는 pointer 변수이며 a[0]도 같은 pointer 변수이다.
	d = a;//d는 배열 [4]를 가리키는 pointer 변수이다.
	printf("d = %p, d+1 = %p, d[1] = %p\n", d, d + 1, d[1]);
	printf("d[0] = %p, d[0]+1 = %p\n", d[0], d[0] + 1);
	printf("*d = %p, *d+1 = %p\n", *d, *d + 1);
	printf("d[0][0] = %d, *d[0] = %d, **d = %d\n\n\n", d[0][0], *d[0], **d);

	c[0] = a[0];
	c[1] = a[1];
	c[2] = a[2];
	//주석1 실습에서 d[0], d[1]의 주소는 첫째, 둘째 row의 행을 가리키는 배열 이름 상수
	/*
	d[0] = a[0]; // 왼쪽 피연산자인 d[0]이 lvalue가 아니므로 error 발생
	d[1] = a[1]; // 왼쪽 피연산자인 d[0]이 lvalue가 아니므로 error 발생
	d[2] = a[2]; // 왼쪽 피연산자인 d[0]이 lvalue가 아니므로 error 발생
	*/
	printf("c[0] = %p, c[1] = %p\n", c[0], c[1]);
	printf("c[0]+1 = %p, *c[1] = %d\n\n", c[0] + 1, *c[1]);
}

int main(void) {
	int a[3][4] = { {11,12,13,14},{21,22,23,24},{31,32,33,34} };
	int* b;
	int* c[3]; // array of pointers
	int(*d)[4]; // pointer to array

	b = a[0];//2차원 배열을 단일 pointer 변수로 접근하는 사례
	d = a;
	//c = a; // c는 lvalue지만 수정할수 없는 lvalue임. 배열 이름이기 때문 

	testPointers(a, b, c, d);

	system("pause");
	return 0;
} 
