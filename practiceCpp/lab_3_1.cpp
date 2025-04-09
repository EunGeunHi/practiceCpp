#include <iostream>
#include <string>
#include <array>
using namespace std;

class Student {
    string name;
    int age;
    array<string, 5> subject;
    array<int, 5> score;

public:
    // ������
    Student(string n, int a, array<string, 5> sub, array<int, 5> sc)
        : name(n), age(a), subject(sub), score(sc) {
    }

    void printInfo() {
        cout << "�̸�: " << name << "\n����: " << age << "\n";
        for (int i = 0; i < 5; ++i)
            cout << subject[i] << ": " << score[i] << "��\n";
    }
};

//cpp��Ÿ��
int main() {
    Student s("ȫ�浿", 20,
        { "����", "����", "����", "����", "��ȸ" },
        { 95, 88, 76, 84, 90 });
    s.printInfo();
    return 0;
}