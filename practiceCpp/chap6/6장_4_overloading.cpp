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

    // [1] 복소수 × 복소수
    Complex multiply(const Complex& other) const {
        double r = real * other.real - imag * other.imag;
        double i = real * other.imag + imag * other.real;
        return Complex(r, i);
    }

    // [2] 복소수 × 실수 (스칼라 곱)
    Complex multiply(double factor) const {
        return Complex(real * factor, imag * factor);
    }

    // 결과 출력
    void print() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex c1(3, 4);          // 3 + 4i
    Complex c2(1, 2);          // 1 + 2i

    Complex result1 = c1.multiply(c2);   // 복소수 곱셈
    Complex result2 = c1.multiply(2.0);  // 실수 배 곱셈

    cout << "복소수 * 복소수 결과: ";
    result1.print(); // (3+4i)*(1+2i) = -5 + 10i

    cout << "복소수 * 2배 결과: ";
    result2.print(); // 6 + 8i

    return 0;
}
