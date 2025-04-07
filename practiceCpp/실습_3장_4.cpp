
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include <windows.h>

struct Matrix {
    int rows;
    int cols;
    int* Term;
};

void getData(struct Matrix* a);
void showData(struct Matrix* a);
void add(struct Matrix*, struct Matrix*, struct Matrix*);
void transpose(struct Matrix*, struct Matrix*);
void multiply(struct Matrix*, struct Matrix*, struct Matrix*);
void free(struct Matrix*);

int main()
{
    // SetConsoleOutputCP(CP_UTF8);//한글깨지는 문제 해결하기 위해 사용 
    struct Matrix a = { 2,3,0 }, b = { 2,3,0 }, c = { 2,3,0 }, d = { 3,4,0 }, e = { 2,4,0 };
    srand(42);
    printf("matrix a[2][3]의 입력: \n");
    getData(&a);//call by point
    //getData(a);의 경우 call by value-> 값 복사, 받는 함수 경우 포인터로 못받고 단순 변수로 받게됨
    showData(&a);
    printf("matrix b[2][3]의 입력: \n");
    getData(&b);
    showData(&b);

    printf("matrix c[2][3]의 입력, add(&a, &b, &c): \n");
    getData(&c);
    add(&a, &b, &c);
    showData(&c);

    printf("matrix d[3][4]의 입력: \n");
    getData(&d);
    showData(&d);

    printf("matrix e[2][4]의 입력, multiply(&a, &d, &e): \n");
    getData(&e);
    multiply(&a, &d, &e);
    showData(&e);

    free(&a); free(&b); free(&c); free(&d); free(&e);

    return 0;
}
void getData(struct Matrix* a) {//!!paramter passing!! eg)struct Matrix* p = &a;(함수 콜) 
    int rows = a->rows;
    int cols = a->cols;
    int** Term = &a->Term;

    *Term = (int*)calloc(rows * cols, sizeof(int));
    if (*Term == NULL) {
        printf("Memmory allocation failed\n");
        return;
    }
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            (*Term)[i * cols + j] = rand() % 10;
        }
}
void showData(struct Matrix* a) {
    int rows = a->rows; int cols = a->cols;
    if (a->Term == NULL) {
        printf("need to init\n");
        return;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", a->Term[i * cols + j]);
        }
        printf("\n");
    }
}
void add(struct Matrix* a, struct Matrix* b, struct Matrix* c) {
    if (a->rows != b->rows || a->cols != b->cols) {
        printf("a, b는 incompatiable matrix\n");
        return;
    }
    if (c->Term == NULL) {
        printf("need to init c Matrix\n");
        return;
    }
    for (int i = 0; i < c->rows; i++)
        for (int j = 0; j < c->cols; j++)
            c->Term[i * c->cols + j] = a->Term[i * c->cols + j] + b->Term[i * c->cols + j];
}

void transpose(struct Matrix* a, struct Matrix* a1) {
    for (int i = 0; i < a->rows; i++)
        for (int j = 0; j < a->cols; j++)
            // a1->Term[j*a->rows +i] = a->Term[i*a->cols +j];
            a1->Term[j * a1->cols + i] = a->Term[i * a->cols + j];
}
void multiply(struct Matrix* a, struct Matrix* b, struct Matrix* c) {
    if (a->cols != b->rows) {
        printf("incompatible matrices");
        return;
    }
    if (c->Term == NULL || c->rows != a->rows || c->cols != b->cols) {
        printf("need to correctly init c Matrix\n");
        return;
    }
    struct Matrix bXpose = { b->cols, b->rows };
    getData(&bXpose);
    transpose(b, &bXpose);
    printf("\t showData(&bXpose)\n");
    showData(&bXpose);

    for (int i = 0; i < c->rows; i++)
        for (int j = 0; j < c->cols; j++) {
            c->Term[i * c->cols + j] = 0;
            for (int k = 0; k < a->cols; k++)
                c->Term[i * c->cols + j] += a->Term[i * a->cols + k] * bXpose.Term[j * bXpose.cols + k];
        }

    free(&bXpose);
}
void free(struct Matrix* m) {
    free(m->Term);
    m->Term = NULL;
}
