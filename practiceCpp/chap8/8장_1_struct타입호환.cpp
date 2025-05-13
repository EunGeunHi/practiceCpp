#include <iostream>
using namespace std;

// 복소수 타입 A
struct ComplexA {
    float real;
    float imag;
};

// 복소수 타입 B
struct ComplexB {
    float real;
    float imag;
};

int main() {
    ComplexA a = { 1.0, 2.0 };
    ComplexB b = { 3.0, 4.0 };

    // a = b; // ❌ 컴파일 오류! ComplexA와 ComplexB는 이름이 달라서 호환되지 않음

    return 0;
}