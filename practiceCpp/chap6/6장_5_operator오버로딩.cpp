//!!연산자 오버로딩!!
#include <iostream>
using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    // 생성자
    Complex(double r = 0.0, double i = 0.0) {
        real = r;
        imag = i;
    }

    // 복소수 X 복소수 연산자 오버로딩
    Complex operator*(const Complex& other) const {
        double r = real * other.real - imag * other.imag;
        double i = real * other.imag + imag * other.real;
        return Complex(r, i);
    }

    // 복소수 X 실수 (스칼라 곱) 연산자 오버로딩
    Complex operator*(double scalar) const {
        return Complex(real * scalar, imag * scalar);
    }

    // 실수 X 복소수 (friend 함수로 전역 연산자 오버로딩)
    friend Complex operator*(double scalar, const Complex& c) {
        return Complex(c.real * scalar, c.imag * scalar);
    }

    // 출력 함수
    void print() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex c1(3, 4);   // 3 + 4i
    Complex c2(1, 2);   // 1 + 2i

    Complex result1 = c1 * c2;     // 복소수 곱         //c1.operator*(C2)
    Complex result2 = c1 * 2.0;    // 복소수 * 실수     //c1.operator*(2.0)
    Complex result3 = 2.0 * c1;    // 실수 * 복소수     //2.0 .operator*(C1) ??--> 오퍼레이터 오버로딩이 아니다!

    cout << "복소수 * 복소수: ";
    result1.print();  // -5 + 10i

    cout << "복소수 * 실수: ";
    result2.print();  // 6 + 8i

    cout << "실수 * 복소수: ";
    result3.print();  // 6 + 8i

    return 0;
}
