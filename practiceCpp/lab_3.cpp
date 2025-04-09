#include <iostream>
#include <string>
using namespace std;

class Student {
    string name;
    int age;
    string subject[5];
    int score[5];

public:
    // 생성자
    Student(string n, int a, string sub[5], int sc[5]) {
        name = n;
        age = a;
        for (int i = 0; i < 5; ++i) {
            subject[i] = sub[i];
            score[i] = sc[i];
        }
    }

    // 출력 함수 (확인용)
    void printInfo() {
        cout << "이름: " << name << "\n";
        cout << "나이: " << age << "\n";
        for (int i = 0; i < 5; ++i) {
            cout << subject[i] << ": " << score[i] << "점\n";
        }
    }
};

//c스타일
int main() {
    string subjects[5] = { "수학", "국어", "영어", "과학", "사회" };
    int scores[5] = { 95, 88, 76, 84, 90 };

    Student s("홍길동", 20, subjects, scores);
    s.printInfo();

    return 0;
}