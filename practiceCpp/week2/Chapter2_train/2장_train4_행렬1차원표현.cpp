
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define AROWS 3
#define ACOLS 4
#define BROWS 4
#define BCOLS 5
#define CROWS 3
#define CCOLS 5
#define DROWS 3
#define DCOLS 4


int main() {
    srand(23);

    int a[AROWS][ACOLS], b[BROWS][BCOLS], c[CROWS][CCOLS], d[DROWS][DCOLS], e[DROWS][DCOLS];

    getMatrix((int*)a, AROWS, ACOLS);//(int*)a는 **형 변환(type casting)**
    getMatrix((int*)b, BROWS, BCOLS);
    getMatrix((int*)d, DROWS, DCOLS);

    printf("Matrix A:\n");
    showMatrix((int*)a, AROWS, ACOLS);
    printf("Matrix B:\n");
    showMatrix((int*)b, BROWS, BCOLS);
    printf("Matrix D:\n");
    showMatrix((int*)d, DROWS, DCOLS);

    int* result = addMatrix((int*)a, (int*)d, AROWS, ACOLS);
    printf("Matrix E = A + D:\n");
    showMatrix(result, AROWS, ACOLS);
    // Cascading Addition Example

    //addMatrix2() 중복 코딩이 필요 > 간결한 코딩 안됨
    int* result2 = addMatrix(addMatrix((int*)a, (int*)d, AROWS, ACOLS), (int*)d, AROWS, ACOLS); // E = (A + D) + A

    printf("Matrix E = ((A + D) + D):\n");
    showMatrix(result2, AROWS, ACOLS);

    int* result3 = multiplyMatrix((int*)a, AROWS, ACOLS, (int*)b, BROWS, BCOLS);
    printf("Matrix C = (A * B):\n");
    showMatrix(result3, CROWS, CCOLS);

    int* transResult = transposeMatrix((int*)b, BROWS, BCOLS);
    printf("Transpose Matrix E = transpose(B)\n");
    showMatrix(transResult, BCOLS, BROWS);

    int* product = multiplyTransposeMatrix((int*)a, AROWS, ACOLS, transResult, BCOLS, BROWS);
    printf("Matrix product = (A * transpose(B)):\n");
    showMatrix(product, AROWS, BROWS);

    free(result);
    free(result2);
    free(result3);
    free(transResult);
    system("pause");

    return 0;
}
