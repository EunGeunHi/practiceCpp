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

    // 비명시적 변환 생성자 (int -> Complex)
    Complex(int r) : real(static_cast<float>(r)), imag(0.0f) {
        cout << "비명시적 변환 생성자(int): " << real << " + " << imag << "i" << endl;
    }

    // 명시적 변환 생성자 (float -> Complex)
    explicit Complex(float r) : real(std::abs(r)), imag(0.0f) {
        cout << "명시적 변환 생성자(float): " << real << " + " << imag << "i" << endl;
    }

    // Ÿ�� ��ȯ �Լ�: Complex �� float
    operator float() const {
        cout << "Ÿ�� ��ȯ �Լ� operator float() ȣ���" << endl;
        return std::abs(real);  // �Ǽ��� ���� ��ȯ
    }

    void show() const {
        cout << "���Ҽ�: " << real << " + " << imag << "i" << endl;
    }
};

// Complex ��ü�� �Ű������� �޴� �Լ�
void printComplex(Complex c) {
    cout << "[printComplex] ";
    c.show();
}

int main() {
    // ������� ��ȯ ������ (int �� Complex)
    Complex c1 = -7;    // Complex(int) ȣ��
    Complex c2;

    // Ÿ�� ��ȯ ������ + std::abs �� Complex �� float �� abs(float)
    Complex c3;
    c3 = std::abs(c1);  // operator float() ȣ�� �� float ��ȯ �� �ٽ� Complex(int) ������ ȣ��

    // ��� Ȯ��
    cout << "\n��� ���Ҽ� c3 = abs(c1): ";
    c3.show();

    // ������ Ÿ�� ��ȯ ����
    Complex c4 = Complex(-3.5f);  // explicit Complex(float) ȣ��

    cout << "\n������ Ÿ�� ��ȯ c4 = Complex(-3.5f): ";
    c4.show();

    // �Լ� ȣ�� �� ������� ��ȯ
    printComplex(19);  // int �� Complex ��ȯ�� �ڵ� ȣ��

    return 0;
}