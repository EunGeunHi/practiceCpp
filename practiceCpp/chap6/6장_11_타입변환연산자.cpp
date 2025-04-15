#include <iostream>
#include <cmath>   // std::abs
using namespace std;

class Complex {
private:
    float real;
    float imag;

public:
    // 기본 생성자
    Complex() : real(0.0f), imag(0.0f) {}

    // 비명시적 변환 생성자 (int → Complex)
    Complex(int r) : real(static_cast<float>(r)), imag(0.0f) {
        cout << "비명시적 변환 생성자(int): " << real << " + " << imag << "i" << endl;
    }

    // 명시적 변환 생성자 (float → Complex)
    explicit Complex(float r) : real(std::abs(r)), imag(0.0f) {
        cout << "명시적 변환 생성자(float): " << real << " + " << imag << "i" << endl;
    }

    // 타입 변환 함수: Complex → float
    operator float() const {
        cout << "타입 변환 함수 operator float() 호출됨" << endl;
        return std::abs(real);  // 실수부 절댓값 반환
    }

    void show() const {
        cout << "복소수: " << real << " + " << imag << "i" << endl;
    }
};

// Complex 객체를 매개변수로 받는 함수
void printComplex(Complex c) {
    cout << "[printComplex] ";
    c.show();
}

int main() {
    // 비명시적 변환 생성자 (int → Complex)
    Complex c1 = -7;    // Complex(int) 호출
    Complex c2;

    // 타입 변환 연산자 + std::abs → Complex → float → abs(float)
    Complex c3;
    c3 = std::abs(c1);  // operator float() 호출 → float 반환 → 다시 Complex(int) 생성자 호출

    // 출력 확인
    cout << "\n결과 복소수 c3 = abs(c1): ";
    c3.show();

    // 명시적 타입 변환 예제
    Complex c4 = Complex(-3.5f);  // explicit Complex(float) 호출

    cout << "\n명시적 타입 변환 c4 = Complex(-3.5f): ";
    c4.show();

    // 함수 호출 시 비명시적 변환
    printComplex(19);  // int → Complex 변환자 자동 호출

    return 0;
}