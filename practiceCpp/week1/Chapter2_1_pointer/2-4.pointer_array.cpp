//2-4. pointer_array.cpp: 실습예제 2.4
/*
lvalue 특징 3가지:
 1) 메모리 주소를 갖는다
 2) &연산자를 적용할 수 있다 (expresion n+1은 &불가. rvalue)
 3) assign 문으로 값을 변경 가능

 배열이름 : '수정할 수 없는 lvalue'
*/
#include <stdio.h>
#include <stdlib.h>

void testPointers(int a1[], int a2[][4]) {//C에서는 다차원 배열을 함수로 전달할 때 첫 번째 차원만 포인터로 변환
    //함수 내에서 int *a1, int (*a2)[4]로 해석하기 때문에 a2[][]으로 사용됨
    int* ap1 = a1;
    //4개의 열을 가지는 배열을 가리키는 array to pointer 선언
    int(*ap2)[4];
    ap2 = a2;
    //*ap2 = a2; // *ap2는 배열 [5]을 가리키는 배열 이름 상수로 간주, lvalue가 아니다.
    //*ap2 = *a2; // 왼쪽 피연산자는 l-value이어야 합니다.
    *ap2[0] = 100;//*ap2는 rvalue이고 *ap2[0]은 lvalue이다

    // int *ap3; ap3 = *a2;와 같은 연산이다. ap3은 row 0의 시작주소를 갖는다.
    int* ap3 = *a2; //첫 row
    int* p = (*a2 + 1); //다음 column
    //int *q[3] = a2; //q는 array이므로 초기화하기 위한 {..}이 필요하다.
    int(*q)[4] = a2; //q는 pointer to array이므로 배열 상수 이름으로 초기화 가능
    ap3++;
    //1번 주석
    //*
    printf("a2 = %p, ap3 = %p, p = %p\n", a2, ap3, p);
    //pointer-to-array를 이용한 접근
    //배열명과 pointer-to-array로 access하는 것이 같다.

    printf("\n\n 배열명과 pointer를 사용한 접근:\n");
    printf("a1[0] : %d\n", a1[0]);
    // 배열의 주소를 가지고 있는 pointer로 선언된 변수 ap1를 배열 형태와 같이 
    //   사용하여 0번 째에 해당하는 배열 원소의 값을 가져올 수 있다.
    printf("ap1[0] : %d\n", ap1[0]);
   
    printf("*a1 : %d\n", *a1);//a1++는 허용된다  
    printf("*ap1 : %d\n", *ap1++); //ap1++는 가능> ++를 먼저 적용하고 다음에 * 연산을 적용한다 
    printf("*ap1++ : %d\n", *ap1);
    ap3++;

    printf("\n Array a2[][]에 대한 연산\n");
    printf("a2[0][0] : %d\n", a2[0][0]);
    printf("ap2[0][0] : %d\n", ap2[0][0]);
    printf("**a2 : %d\n", **a2);
    printf("**ap2 : %d\n", **ap2);
    printf("ap3[1] : %d\n", ap3[1]);
    printf("*p : %d\n", *p);
    printf("*(p+1) : %d\n", *(p + 1));
    printf("*q : %p\n", *q);
    printf("*q[0] : %d\n", *q[0]);

    printf("\n\n2번 주석\n\n");
    printf("a1 = %p, ap1 = %p\n", a1, ap1);
    printf("a2 = %p, ap2 = %p, ap3 = %p\n", a2, ap2, ap3);
    printf("ap1++  ap2++  ap3++ 실행 전\n");
    printf("*ap1 = %d\n", *ap1);
    printf("**ap2 = %d\n", **ap2);
    printf("*ap3 = %d\n", *ap3);
    ap1++;
    ap2++;//증가시 얼마나 증가하는지를 이해가 필요 
    ap3++;
    printf("\nap1++  ap2++  ap3++ 실행 후\n");
    printf("a1 = %p, ap1 = %p\n", a1, ap1);
    printf("a2 = %p, ap2 = %p, ap3 = %p\n", a2, ap2, ap3);
    printf("*ap1 = %d\n", *ap1);
    printf("**ap2 = %d\n", **ap2);
    printf("*ap3 = %d\n", *ap3);
}

int main() {
    int a1[4] = { 11,12,13,14 };
    int a2[3][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12} };

    testPointers(a1, a2);

    system("pause");

    return 0;
}
