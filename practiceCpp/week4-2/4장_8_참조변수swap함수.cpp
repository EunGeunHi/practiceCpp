/*
스트링 배열 정렬과 insert 문제 해결
*/
#include <iostream>
#include <cstring> // strcmp, strcpy_s

using namespace std;

#define MAX_LEN 20
#define SIZE 8

// 배열 출력 함수
void showData(const char* msg, char* arr[], int size) {
    cout << msg << ": ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 문자열 교환 함수 (swap)
void swapStrings(char*& a, char*& b) {
    //a,b는 포인터를 참조하는 변수
    //a는 포인터를 가리키는 참조변수라는 의미
    char* temp = a;
    a = b;
    b = temp;
    //main 함수의 포인터가 변경됨
}

void swapStrings(char* a, char* b) {//a,b 포인터 값이 복사됨
    char* temp = a;
    a = b;
    b = temp;
    //main 함수의 포인터가 변경되지 않음
}

// 버블 정렬 함수 (오름차순) - Sort() 함수 사용 금지 -swap() 사용
void sortData(char* arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) { // 오름차순 정렬 (A-Z)
                swapStrings(arr[j], arr[j + 1]);
            }
        }
    }
}

// 문자열 삽입 후 크기 증가된 정렬 배열 반환 - Sort() 사용금지 O(n) 시간 복잡도로 해결- while 문 1개로 해결 
char** insertData(char* data[], int size, const char* value) {
    char* newValue = new char[MAX_LEN]; // 동적 메모리 할당
    strcpy_s(newValue, MAX_LEN, value);

    // 새로운 배열 생성 (size + 1 크기)
    char** newData = new char* [size + 1];
    for (int i = 0; i < size + 1; i++) {
        newData[i] = new char[MAX_LEN];
    }

    int i = size - 1;
    bool tag = true;

    // 기존 데이터를 복사하면서 새로운 데이터 삽입
    while (i >= 0) {
        if (strcmp(data[i], newValue) > 0) {
            strcpy_s(newData[i + 1], MAX_LEN, data[i]);
            i--;
            if (tag && i < 0) {
                strcpy_s(newData[i + 1], MAX_LEN, newValue);
                break;
            }
        }
        else {
            if (tag) {
                strcpy_s(newData[i + 1], MAX_LEN, newValue);
                tag = false;
                continue;
            }
            else {
                strcpy_s(newData[i], MAX_LEN, data[i]);
                i--;
            }
        }
    }

    delete[] newValue; // 동적 메모리 해제
    return newData;
}

int main() {
    // 초기 문자열 데이터 동적 할당
    char* data[] = {
        new char[MAX_LEN] {"avocado"},
        new char[MAX_LEN] {"grape"},
        new char[MAX_LEN] {"persimmon"},
        new char[MAX_LEN] {"pear"},
        new char[MAX_LEN] {"blueberry"},
        new char[MAX_LEN] {"strawberry"},
        new char[MAX_LEN] {"melon"},
        new char[MAX_LEN] {"jujube"}
    };

    showData("정렬 전", data, SIZE);

    sortData(data, SIZE);

    showData("정렬 후 (오름차순)", data, SIZE);

    // 삽입할 데이터
    const char* realData[3] = { "waterMelon", "kiwi", "apple" };

    for (const char* newData : realData) {
        char** result = insertData(data, SIZE, newData);
        cout << "\n\n" << newData << " 삽입 후: ";
        showData("삽입 후 정렬된 배열", result, SIZE + 1);

        // 동적 할당된 메모리 해제
        for (int i = 0; i < SIZE + 1; i++) {
            delete[] result[i];
        }
        delete[] result;
    }

    // 원래 배열의 메모리 해제
    for (int i = 0; i < SIZE; i++) {
        delete[] data[i];
    }
    system("pause");
    return 0;
}
