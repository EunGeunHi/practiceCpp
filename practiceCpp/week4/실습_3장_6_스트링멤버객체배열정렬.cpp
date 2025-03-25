/*
5,6장 학습후 아래 실습 코드를 완성할 수 있는 스킬을 확보해야 한다.
*/
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <string>
#include <windows.h>

using namespace std;

class Student {
public:
    char* name;
    int age;
    char* city;
    Student() {}
    Student(const char* name, int age, const char* city);
    void swap(Student* b);
    void showStudent();
    ~Student(); // Destructor 추가
    int compareStudents(const Student* b);
    void updateStudentCity(char* city);
};
void Student::updateStudentCity(char* city) {

}
int Student::compareStudents(const Student* b) {


}
void Student::showStudent() {

}
// Constructor 구현 - 오류 수정
Student::Student(const char* name, int age, const char* city) {
    this->name = name;
    this->age = age;
    this->city = city;

}

// Destructor 구현

Student::~Student() {

}
void Student::swap(Student* b) {

}

void showStudents(string message, Student* students[], int numStudents) {
    //void showStudent();를 사용한 객체 출력

}

void selectionSortStudents(Student* students[], int numStudents) {
    // int compareStudents(const Student* b);를 사용한 정렬

}
int main() {
    SetConsoleOutputCP(CP_UTF8);//한글깨지는 문제 해결하기 위해 사용 
// 학생 객체 초기화
    int numStudents = 5;
    Student student1("홍길동", 23, "부산");
    Student student2("강감찬", 22, "의주");
    Student student3("을지문덕", 13, "살수");
    Student student4("이순신", 19, "한산도");
    Student student5("계백", 33, "공주");
    Student* students[5] = { &student1,&student2,&student3,&student4 ,&student5 };
    // 각 학생 정보 출력
    showStudents("정렬전:", students, numStudents);
    student1.updateStudentCity("나주");
    student1.showStudent();
    selectionSortStudents(students, numStudents);
    showStudents("정렬후", students, numStudents);
    system("pause");
    return 0;
}