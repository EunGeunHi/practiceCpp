#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 10;
//������ 10 ~ 60 ���̿� ����
void inputData(int data[], int size) {
    srand(time(0));
    
    //rand() % 50;
}



void swap(int arr[], int ind1, int ind2) {
 
}



/*
 * ���̵��� �ſ� ���� �˰��� ����
 * ���ĵ� ���� �迭�� ���� ���� �߰��ϴ� �˰��� > �� �迭�� ũ��� ���� �迭���� +1�� ����� ���� �迭�� copy�� ��
 * ���Ե� ���� �߰��� ���� �˰��� �����ϱ�
 * O(n) �˰������� ���� => for/while �ѹ���
 */
int* insertData(int data[], int size, int value) { // int data[]���� int *data ���� �� ��õ(���� ������), �̹� �迭 ũ��� ���� ���� ���ο� �迭 �����ؾ���, char *data or stirng *data
    int* newData = new int[size + 1];// �Լ� �����Ŀ��� ���� �־� delete[] �ʿ�

    return newData;
}

void sortData(int* data, int SIZE) { //�迭�� �����ͷ� �޴´�, ���� ���� for for i<Size, j=i+1,if swap

}

// int arr[10] = {1,2,3,4} ��𼭵� ���ٰ��� �׷��� �ѹ��ٲ�� �� ã�ƾ���
int main() {
    int data[SIZE];
    inputData(data, SIZE);
    showData("���� �Է�", data, SIZE);

    sortData(data, SIZE);//
    showData("������", data, SIZE);

    reverse(data, SIZE);
    showData("\n���� ���ġ", data, SIZE);

    maxSort(data, SIZE);

    sortData(data, SIZE);
    showData("\n ������", data, SIZE);

    int realData[] = { 5, 15, 99 };
    for (int newData : realData) {
        int* result = insertData(data, SIZE, newData);
        cout << "\n\n" << newData << " : ";
        showData("�Ǽ� ������", result, SIZE + 1);
        delete[] result;
    }
    system("pause");
    return 0;
}
