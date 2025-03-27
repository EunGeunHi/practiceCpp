#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct complex {
    float real;
    float imaginary;
};

// 난수를 사용하여 복소수를 생성하는 함수 (Call by Value 반환)
complex getComplex() {
    complex c;
    c.real = (rand() % 100) / 10.0;      // 0.0 ~ 9.9
    c.imaginary = (rand() % 100) / 10.0; // 0.0 ~ 9.9
    return c;
}

// 두 개의 복소수를 더하는 함수 (Call by Value)
complex addComplex(complex c1, complex c2) {
    complex result;
    result.real = c1.real + c2.real;
    result.imaginary = c1.imaginary + c2.imaginary;
    return result;
}

// 복소수를 출력하는 함수
void showComplex(complex c) {
    cout << c.real;
    if (c.imaginary >= 0) cout << " + " << c.imaginary << "i" << endl;
    else cout << " - " << -c.imaginary << "i" << endl;
}

int main() {
    srand(time(0)); // 난수 시드 초기화

    // 두 개의 복소수를 난수로 생성
    complex num1 = getComplex();
    complex num2 = getComplex();

    // 두 복소수를 출력
    cout << "Complex Number 1: ";
    showComplex(num1);

    cout << "Complex Number 2: ";
    showComplex(num2);

    // 두 복소수를 더함
    complex sum = addComplex(num1, num2);

    // 합산 결과 출력
    cout << "Sum: ";
    showComplex(sum);

    return 0;
}
