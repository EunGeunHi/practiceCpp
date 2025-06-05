#include <iostream>
#include <string>
using namespace std;

void swapInt(int data[], int i, int j) {
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;;
}
// 정수 배열 버블 정렬
void sortInt(int arr[], int size) {
    for (int i = 0; i < size; i++)
        for (int j = i+1; j < size; j++)
            if (arr[i] > arr[j])
                swapInt(arr, i, j);
}
void swapDouble(double data[], int i, int j) {
    double temp = data[i];
    data[i] = data[j];
    data[j] = temp;;
}
// 실수 배열 버블 정렬
void sortDouble(double arr[], int size) {
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (arr[i] > arr[j])
                swapDouble(arr, i, j);
}
void swapString(string data[], int i, int j) {
    string temp = data[i];
    data[i] = data[j];
    data[j] = temp;;
}
// 문자열 배열 버블 정렬
void sortString(string arr[], int size) {
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (arr[i] > arr[j])
                swapString(arr, i, j);
}

// 정수 출력
void showInt(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// 실수 출력
void showDouble(double arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// 문자열 출력
void showString(string arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

/*
=> 타입별로 비슷한 함수 여러개 구현해야함
*/

int main() {
    int nums[] = { 5, 1, 4, 2, 9, 6,3};
    double floats[] = { 3.14, 1.41, 2.71 };
    string words[] = { "banana", "apple", "cherry", "melon", "kiwi"};

    int nSize = sizeof(nums) / sizeof(nums[0]);
    //int nSize = 7; // !!hard coding
    int fSize = sizeof(floats) / sizeof(floats[0]);
    int sSize = sizeof(words) / sizeof(words[0]);

    sortInt(nums, nSize);
    showInt(nums, nSize);

    sortDouble(floats, fSize);
    showDouble(floats, fSize);

    sortString(words, sSize);
    showString(words, sSize);
    int choice; cin >> choice;
    return 0;
}
