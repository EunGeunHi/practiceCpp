#include <iostream>
#include <string>
using namespace std;

class Student {
    string name;
    int age;
    string subject[5];
    int score[5];

public:
    // ������
    Student(string n, int a, string sub[5], int sc[5]) {
        name = n;
        age = a;
        for (int i = 0; i < 5; ++i) {
            subject[i] = sub[i];
            score[i] = sc[i];
        }
    }

    // ��� �Լ� (Ȯ�ο�)
    void printInfo() {
        cout << "�̸�: " << name << "\n";
        cout << "����: " << age << "\n";
        for (int i = 0; i < 5; ++i) {
            cout << subject[i] << ": " << score[i] << "��\n";
        }
    }
};

//c��Ÿ��
int main() {
    string subjects[5] = { "����", "����", "����", "����", "��ȸ" };
    int scores[5] = { 95, 88, 76, 84, 90 };

    Student s("ȫ�浿", 20, subjects, scores);
    s.printInfo();

    return 0;
}