#include <iostream>
using namespace std;

class ComplexX {
private:
    float real, imag;

public:
    ComplexX(float r = 0.0, float i = 0.0) : real(r), imag(i) {}

    void print() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

class ComplexY {
private:
    float real, imag;

public:
    ComplexY(float r = 0.0, float i = 0.0) : real(r), imag(i) {}

    void print() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    ComplexX cx(1.0, 2.0);
    ComplexY cy(3.0, 4.0);

    // cx = cy; // ❌ 컴파일 오류! ComplexX와 ComplexY는 서로 다른 타입

    return 0;
}