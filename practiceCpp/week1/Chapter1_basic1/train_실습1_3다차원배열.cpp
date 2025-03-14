/*
* 다차원 배열 처리 함수 구현
*/
#include <iostream>
#include <cstdlib>  // rand()
#include <ctime>    // time()

#define ROWS_A 2
#define COLS_A 3
#define ROWS_B 3
#define COLS_B 4

using namespace std;




// 행렬 덧셈 - 이중 포인터에 대한 이해가 필요 => chap 2
int** addMatrix2(int X[][COLS_A], int Y[][COLS_A], int rows, int cols) {
    int** Z = new int* [rows];
    for (int i = 0; i < rows; i++) {
        Z[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            Z[i][j] = X[i][j] + Y[i][j];
        }
    }
    return Z;
}

void inputData(int (*a)[COLS_A], int ROWS_A, int COLS_A){
	
}



int main() {
    srand(time(0)); // 난수 초기화

    int A[ROWS_A][COLS_A]; // 2x3 행렬
    int B[ROWS_B][COLS_B]; // 3x4 행렬
    int C[ROWS_A][COLS_B]; // 2x4 행렬
    int D[ROWS_A][COLS_A]; // 2x3 복제 행렬
    int E[ROWS_A][COLS_A]; // 덧셈 결과 행렬
    int F[COLS_B][ROWS_B]; // 전치 행렬
    int G[ROWS_A][COLS_B]; // 전치 행렬 활용 곱셈 결과


    inputData(A, ROWS_A, COLS_A);
    inputData(B, ROWS_B, COLS_B);

    // 배열 복제 (수동 복사)
    for (int i = 0; i < ROWS_A; i++)
        for (int j = 0; j < COLS_A; j++)
            D[i][j] = A[i][j];

    cout << "A[2][3] = \n";
    showData("행렬 A", A, ROWS_A, COLS_A);

    cout << "D[2][3] = \n";
    showData("행렬 D", D, ROWS_A, COLS_A);

    cout << "B[3][4] = \n";
    showData("행렬 B", B, ROWS_B, COLS_B);

    addMatrix(A, D, E, ROWS_A, COLS_A);	// E=A+B
    /*
	 * 시험에서 어렵게 하면
	 * E = addMatrix(A,D)
	 * 이중포인터를 리턴해야 가능 
	 */
    cout << "E[2][3] = \n";
    showData("행렬 E", E, ROWS_A, COLS_A);

    int** H = addMatrix2(A, D, ROWS_A, COLS_A);
    cout << "H[2][3] = \n";
    showData2("행렬 H", H, ROWS_A, COLS_A);

    multiplyMatrix(A, B, C, ROWS_A, COLS_A, COLS_B);
    cout << "C[2][4] = \n";
    showData("행렬 C", C, ROWS_A, COLS_B);

    transposeMatrix(B, F, ROWS_B, COLS_B);
    cout << "F[4][3] = \n";
    showData("행렬 F (B의 전치)", F, COLS_B, ROWS_B);

    multiplyMatrixTransposed(A, F, G, ROWS_A, COLS_A, COLS_B);
    cout << "G[2][4] (전치 행렬을 활용한 곱셈 결과) = \n";
    showData("행렬 G", G, ROWS_A, COLS_B);

    if (equals(A, D, ROWS_A, COLS_A))
        cout << "행렬 A와 D는 동일합니다.\n";
    else
        cout << "행렬 A와 D는 동일하지 않습니다.\n";
    system("pause");
    return 0;
}
