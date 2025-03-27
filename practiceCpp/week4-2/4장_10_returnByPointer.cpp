#include <iostream>
using namespace std;

// 배열 포인터를 받아 포인터 반환
int* value(int* ptr, int n);

int main() {
    int a[] = { 10, 20, 30, 40, 50 };
    // 참조 버전에서는 value(a, 2) = 60; 이 가능했지만,
    // 포인터 버전에서는 *value(a, 2) = 60; 으로 사용해야 함
    *value(a, 2) = 60;
    *value(a, 4) = 70;

    for (int i = 0; i < 5; i++)
        cout << "a[" << i << "] = " << a[i] << endl;

    system("pause");
    return 0;
}

int* value(int* ptr, int n) {
    return  &ptr[n];  // 또는ptr + n;
}
