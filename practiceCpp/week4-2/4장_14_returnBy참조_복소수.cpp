//4장-12. Cascade.cpp   4.4.4 reference에 의한 함수 return 값
// return by reference의 전형적인 사례로서 6장 이후 학습할 주요 대상
//4장에서는 단순 실행하여 보는 것으로 실습함 - 4장의 실습 구현 대상이 아님 /맛보기 코드임 
#include <iostream>

using namespace std;

class Complex {
private:
    float real;
    float imaginary;
public:
    Complex() { real = 0.0; imaginary = 0.0; }
    Complex(float r, float i) : real(r), imaginary(i) { }

    void showComplex() const {
        cout << real << " + " << imaginary << "i" << endl;
    }

    // add() 함수 (Return by Reference)
    Complex& add(const Complex& T);
};

// add() 함수 정의 (Return by Reference)
Complex& Complex::add(const Complex& T) {
    //Complex result;
    this->imaginary = this->imaginary + T.imaginary;
    this->real = this->real + T.real;
    cout << "add(const Complex&):: ";
    this->showComplex();
    return *this;
    //return result;//오류 발생
}

int main(void) {
    Complex C1(1.1, 2.2);
    cout << "C1 = "; C1.showComplex();

    Complex C2(3.3, 4.4);
    cout << "C2 = "; C2.showComplex();

    Complex C3(7.7, 9.9);
    cout << "C3 = "; C3.showComplex();

    Complex C4;

    // 연산자 오버로딩 대신 add() 함수 사용
    C4 = C1.add(C2).add(C3);

    cout << "C4 = "; C4.showComplex();

    system("pause");
    return 0;
}

