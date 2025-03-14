#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 10;
//난수를 10 ~ 60 사이에 생성
void inputData(int data[], int size) {
    srand(time(0));
    
    //rand() % 50;
}



void swap(int arr[], int ind1, int ind2) {
 
}



/*
 * 난이도가 매우 높은 알고리즘 구현
 * 정렬된 기존 배열에 임의 값을 추가하는 알고리즘 > 새 배열의 크기는 기존 배열보다 +1로 만들고 기존 배열을 copy할 때
 * 삽입된 값이 중간에 들어가는 알고리즘 구현하기
 * O(n) 알고리즘으로 구현 => for/while 한번만
 */
int* insertData(int data[], int size, int value) { // int data[]보다 int *data 쓰는 거 추천(개념 포인터), 이미 배열 크기는 결정 따라서 새로운 배열 생성해야함, char *data or stirng *data
    int* newData = new int[size + 1];// 함수 종료후에도 남아 있어 delete[] 필요

    return newData;
}

void sortData(int* data, int SIZE) { //배열을 포인터로 받는다, 버블 정렬 for for i<Size, j=i+1,if swap

}

// int arr[10] = {1,2,3,4} 어디서든 접근가능 그래서 한번바뀌면 다 찾아야함
int main() {
    int data[SIZE];
    inputData(data, SIZE);
    showData("난수 입력", data, SIZE);

    sortData(data, SIZE);//
    showData("정렬후", data, SIZE);

    reverse(data, SIZE);
    showData("\n역순 재배치", data, SIZE);

    maxSort(data, SIZE);

    sortData(data, SIZE);
    showData("\n 정렬후", data, SIZE);

    int realData[] = { 5, 15, 99 };
    for (int newData : realData) {
        int* result = insertData(data, SIZE, newData);
        cout << "\n\n" << newData << " : ";
        showData("실수 삽입후", result, SIZE + 1);
        delete[] result;
    }
    system("pause");
    return 0;
}
