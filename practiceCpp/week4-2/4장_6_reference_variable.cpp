//4-4. reference_variable.cpp    4.3 pointer 변수와 reference 변수

#include <iostream>
using namespace std;
#define COLS 5

// 배열을 참조로 받아 수정하는 함수
void update(int* const& rfrn) { //void update(int* const p)와 비교
    /*
    * int* const&: const&: 참조로 전달하며 참조 자체는 변경할 수 없다.
    * int* const: 포인터 p가 가리키는 주소는 변경할 수 없다.
    * 함수 안에서 p = 다른 주소; 같은 코드는 금지되어 안전
    */
    rfrn[0] = 100;  //*rfrn = 100;
    rfrn[1] = 200;  //*(rfrn+1) = 100;
    // 즉 포인터처럼 쓴다
}

int main() {
    int a[COLS] = { 10, 11, 12, 13, 14 };

    cout << "<<함수 호출 전 a 배열>>" << endl;
    for (int i = 0; i < COLS; i++) {
        cout << "a[" << i << "] = " << a[i] << endl;
    }

    // 배열 a를 참조로 전달
    update(a);

    cout << endl << "<<함수 호출 후 a 배열>>" << endl;
    for (int i = 0; i < COLS; i++) {
        cout << "a[" << i << "] = " << a[i] << endl;
    }

    cout << endl << "<<reference 변수 rfrn 출력>>" << endl;
    int* const& rfrn = a;  // 배열의 주소를 const pointer reference로 참조
    rfrn[2] = 300;

    for (int i = 0; i < COLS; i++) {
        cout << "a[" << i << "] = " << a[i] << "\t"
            << "rfrn[" << i << "] = " << rfrn[i] << endl;
    }
    system("pause");
    return 0;
}

