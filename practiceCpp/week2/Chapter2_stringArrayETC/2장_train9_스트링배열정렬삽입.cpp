/*
스트링 배열 정렬과 insert 문제 해결
*/
#include <iostream>
#include <cstring> // strcmp, strcpy_s

using namespace std;

#define MAX_LEN 20
#define SIZE 8

void showData(const char* msg, char* arr[], int size);
void swapStrings(char*& a, char*& b);
void sortData(char* arr[], int size);
char** insertData(char* data[], int size, const char* value);
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
