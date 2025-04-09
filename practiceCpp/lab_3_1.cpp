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
    // 생성자
    Student(string n, int a, array<string, 5> sub, array<int, 5> sc)
        : name(n), age(a), subject(sub), score(sc) {
    }

    void printInfo() {
        cout << "이름: " << name << "\n나이: " << age << "\n";
        for (int i = 0; i < 5; ++i)
            cout << subject[i] << ": " << score[i] << "점\n";
    }
};

//cpp스타일
int main() {
    Student s("홍길동", 20,
        { "수학", "국어", "영어", "과학", "사회" },
        { 95, 88, 76, 84, 90 });
    s.printInfo();
    return 0;
}