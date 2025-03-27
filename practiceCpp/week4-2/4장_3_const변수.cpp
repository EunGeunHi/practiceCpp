
#include <iostream>
using namespace std;

// 함수 선언
void readOnly(const int* ptr);        // 포인터가 가리키는 값은 상수
void writeOnly(int* const ptr);       // 포인터 자체는 상수
void readWriteNoneConst(int* ptr);    // 둘 다 상수 아님
void fullyConst(const int* const ptr);// 포인터도 상수, 값도 상수

int main() {
    int a = 10;
    int b = 20;
    int c = 30;

    const int* p1 = &a;     // 가리키는 값이 상수 (read-only)
    int* const p2 = &b;     // 포인터 자체가 상수 (주소 고정)
    const int* const p3 = &c; // 둘 다 상수

    cout << "== 함수 호출 ==" << endl;

    readOnly(p1);           // OK
    // writeOnly(p1);       // ❌ 컴파일 오류 (const int* → int* const)
    // fullyConst(p1);      // OK (const int* → const int* const)

    // readOnly(p2);        // OK (int* → const int*)
    writeOnly(p2);          // OK
    // fullyConst(p2);      // ❌ (int* const → const int* const)

    // readOnly(p3);        // OK
    // writeOnly(p3);       // ❌
    // fullyConst(p3);      // OK

    int x = 100;
    readWriteNoneConst(&x); // OK


    return 0;
}

// 가리키는 값은 읽기만 가능
void readOnly(const int* ptr) {
    cout << "readOnly: " << *ptr << endl;
    // *ptr = 999; // ❌ 수정 불가
}

// 포인터는 고정되어 있으나 가리키는 값은 수정 가능
void writeOnly(int* const ptr) {
    *ptr = *ptr + 1; // ✅ 값 수정 가능
    cout << "writeOnly (after increment): " << *ptr << endl;
    // ptr = nullptr; // ❌ 포인터 주소 수정 불가
}

// 포인터도 수정 가능, 값도 수정 가능
void readWriteNoneConst(int* ptr) {
    *ptr = *ptr + 5;
    cout << "readWriteNoneConst: " << *ptr << endl;
}

// 포인터도 상수, 가리키는 값도 상수
void fullyConst(const int* const ptr) {
    cout << "fullyConst: " << *ptr << endl;
    // *ptr = 123; // ❌
    // ptr = nullptr; // ❌
}
