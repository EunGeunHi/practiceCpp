#include <iostream>
#include <string>
using namespace std;

// 템플릿 swap 함수 (배열 내 특정 인덱스 i, j 교환)
template <typename T>
void swapElements(T data[], int i, int j) {
    T temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

// 템플릿 버전 버블 정렬
template <typename T>
void sort(T arr[], int size) {
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (arr[i] > arr[j])
                swapElements(arr, i, j);
}

// 템플릿 배열 출력 함수
template <typename T>
void show(T arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int nums[] = { 5, 1, 4, 2, 9, 6, 3 };
    double floats[] = { 3.14, 1.41, 2.71 };
    string words[] = { "banana", "apple", "cherry", "melon", "kiwi" };

    int nSize = sizeof(nums) / sizeof(nums[0]);
    int fSize = sizeof(floats) / sizeof(floats[0]);
    int sSize = sizeof(words) / sizeof(words[0]);

    sort(nums, nSize);
    show(nums, nSize);

    sort(floats, fSize);
    show(floats, fSize);

    sort(words, sSize);
    show(words, sSize);

    int choice;
    cin >> choice;
    return 0;
}
