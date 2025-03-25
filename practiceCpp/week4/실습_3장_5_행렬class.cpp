/*
* 맛보기 코드 : 클래스 사용 예, 3장에서는 클래스 구현할 단계가 아님, 단지 사용 예만 보는 것으로 학습
*/
// matrixMultiplication.cpp - 2차원 행렬을 1차원으로 저장, + 구현 
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include "time.h"
using namespace std;
// 보통 행렬에 대하여add, sub, mult, transpose 구현하는 코딩
class Matrix {
public:
	Matrix(int row, int col) : rows(row), cols(col) { //생성자
		Term = new int[row * col];
	}
	Matrix(const Matrix&);//복사 생성자
	~Matrix() { delete[]Term; } //소멸자가 add()에서 호출되어 할당된 배열을 반환하여 런타임 오류가 발생함 
	int GetData();
	Matrix Transpose();
	int Display(); // 행렬 모양: A[rows][cols] 출력
	Matrix Add(Matrix b);
	Matrix Multiply(Matrix b);
	Matrix& operator=(const Matrix&);//치환연산자 

private:
	int rows, cols;
	//int Term[rows][cols];
	int* Term;// a[i][j] = i * cols + j
};
// 복사 생성자
Matrix::Matrix(const Matrix& m) : rows(m.rows), cols(m.cols) {
	Term = new int[rows * cols];
	for (int i = 0; i < rows * cols; ++i)
		Term[i] = m.Term[i];
}

// 대입 연산자
Matrix& Matrix::operator=(const Matrix& m) {
	if (this == &m) return *this; // 자기 자신은 무시

	delete[] Term;

	rows = m.rows;
	cols = m.cols;
	Term = new int[rows * cols];
	for (int i = 0; i < rows * cols; ++i)
		Term[i] = m.Term[i];
	return *this;
}


int Matrix::GetData() {
	int r = this->rows; int c = this->cols;
	Term = (int*)calloc(r * c, sizeof(int));

	printf("rows = %d cols = %d\n", rows, cols);
	for (int j = 0; j < rows * cols; j++)
	{
		Term[j] = rand() % (r * c);//수정 필요
	}
	return 0;
}

Matrix Matrix::Add(Matrix b) {
	Matrix* a = this;
	Matrix temp(rows, cols);
	if (a->rows != b.rows || a->cols != b.cols) {
		printf("a, b는 incompatiable matrix\n");
		return temp;
	}
	for (int i = 0; i < a->rows * a->cols; i++) {
		temp.Term[i] = a->Term[i] + b.Term[i];
	}
	return temp;
}

Matrix Matrix::Transpose() {
	Matrix b(cols, rows), * temp = this;
	for (int i = 0; i < temp->rows; i++)
		for (int j = 0; j < temp->cols; j++)
			b.Term[j * b.cols + i] = temp->Term[i * temp->cols + j];

	return b;
}

Matrix Matrix::Multiply(Matrix b) {
	if (cols != b.rows) {
		cout << "Incompatible matrices" << endl;
		return b;
	}
	Matrix bXpose = b.Transpose();
	Matrix d(rows, b.cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < b.cols; j++) {
			int sum = 0;
			for (int k = 0; k < b.rows; k++) {
				sum += (Term[i * cols + k]) * (bXpose.Term[j * b.rows + k]);
			}
			d.Term[i * b.cols + j] = sum;
		}
	}
	return d;
}

int Matrix::Display() {
	int n;
	n = rows * cols;
	for (int i = 0; i < rows; i++)
	{
		cout << endl;
		for (int j = 0; j < cols; j++)
			cout << Term[i * cols + j] << " ";
	}
	cout << endl << endl;
	return 0;
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);//한글깨지는 문제 해결하기 위해 사용 
	Matrix a(2, 3); Matrix a1(2, 3); Matrix a2(2, 3);
	Matrix b(3, 4);
	Matrix c(2, 4);
	srand(49);
	cout << "matrix a[2][3]의 입력: " << endl;
	a.GetData();
	a.Display();

	cout << "matrix a1[2][3]의 입력: " << endl;
	a1.GetData();
	a1.Display();
	//*
	a2 = a.Add(a1);
	cout << "a2 = a + a1" << endl;
	a2.Display();

	cout << "matrix b[3][4]의 입력: " << endl;
	b.GetData();
	b.Display();

	Matrix d(4, 3);
	d = b.Transpose();
	cout << "Transpose() of Matrix b" << endl;
	d.Display();

	cout << "Multiply of Matrix a,b" << endl;
	c = a.Multiply(b);
	c.Display();
	//*/
	system("pause");
	return 0;
}

