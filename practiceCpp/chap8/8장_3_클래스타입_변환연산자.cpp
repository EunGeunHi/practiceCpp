#include <iostream>
using namespace std;

// forward 선언 (상호 참조 위해 필요)
class ComplexB;

class ComplexA {
private:
    float real, imag;

public:
    ComplexA(float r = 0.0, float i = 0.0) : real(r), imag(i) {}

    // ComplexB -> ComplexA 변환 생성자
    ComplexA(const ComplexB& b);

    // ComplexB -> ComplexA 대입 연산자
    ComplexA& operator=(const ComplexB& b);

    float getReal() const { return real; }
    float getImag() const { return imag; }

    void print() const {
        cout << "[A] " << real << " + " << imag << "i\n";
    }
};

class ComplexB {
private:
    float real, imag;

public:
    ComplexB(float r = 0.0, float i = 0.0) : real(r), imag(i) {}

    // ComplexA -> ComplexB 변환 생성자 
    ComplexB(const ComplexA& a) {
        real = a.getReal();
        imag = a.getImag();
        cout << "ComplexB 변환 생성자 호출됨\n";
    }

    // ComplexA -> ComplexB 대입 연산자
    ComplexB& operator=(const ComplexA& a) {
        real = a.getReal();
        imag = a.getImag();
        cout << "ComplexB 대입 연산자 호출됨\n";
        return *this;
    }

    float getReal() const { return real; }
    float getImag() const { return imag; }

    void print() const {
        cout << "[B] " << real << " + " << imag << "i\n";
    }
};

// ComplexA 멤버 함수 정의 (ComplexB 포함 이후에)
ComplexA::ComplexA(const ComplexB& b) {
    real = b.getReal();
    imag = b.getImag();
    cout << "ComplexA 변환 생성자 호출됨\n";
}

ComplexA& ComplexA::operator=(const ComplexB& b) {
    real = b.getReal();
    imag = b.getImag();
    cout << "ComplexA 변환 연산자 호출됨\n";
    return *this;
}

int main() {
    ComplexA a(1.0, 2.0);
    ComplexB b(3.0, 4.0);

    cout << "\n--- 초기 상태 ---\n";
    a.print();
    b.print();

    cout << "\n--- a = b 호출 ---\n";
    a = b; // ComplexB -> ComplexA

    cout << "\n--- b = a 호출---\n";
    b = a; // ComplexA -> ComplexB

    cout << "\n--- 최종 상태 ---\n";
    a.print();
    b.print();

    return 0;
}

/*
구조체는 지원안되지만
클래스는 재정의 하며 다른 타입으로도 가능
*/