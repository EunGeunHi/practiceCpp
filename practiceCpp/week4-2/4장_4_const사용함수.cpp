#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <string>
using namespace std;

class Student {
public:
    char* name;
    int age;
    char* city;
    Student() {}
    Student(const char* name, int age, const char* city);
    void swap(Student* b);
    void showStudent() const;
    ~Student(); // Destructor 추가
    int compareStudents(const Student* b);
    void updateStudentCity(const char* city);
};
void Student::updateStudentCity(const char* city) {
    //this->city = city;//const char *을 char*로 치환 못한다 이유는? 이해가 필요 
    //strcpy(this->city, city);
    this->city = strdup(city);
}
int Student::compareStudents(const Student* b) {
    return strcmp(this->name, b->name);

}
void Student::showStudent() const{
    printf("[%s, %d, %s]\n", name, age, city);
}
// Constructor 구현
Student::Student(const char* name, int age, const char* city) {
    /*
    this->name = name;//const를 사용하는 이유를 이해하는 것이 필요 
    this->age = age;
    this->city = city;//const를 사용하는 이유를 이해하는 것이 필요 
   */
    //*
    this->name = strdup(name);
    this->age = age;
    this->city = strdup(city);
    //*/
}

// Destructor 구현

Student::~Student() {
    if (name != nullptr) {
        free(name);
    }
    if (city != nullptr) {
        free(city);
    }
}
void Student::swap(Student* b) {    // !!pointer로 swap!!
    std::swap(name, b->name);       // strcpy로 하면 err, 
    std::swap(age, b->age);
    std::swap(city, b->city);
}

void showStudents(string message, const Student* students[], int numStudents) {
    //void showStudent();를 사용한 객체 출력
    cout << message << ": " << endl;
    for (int i = 0; i < numStudents; ++i) {
        if (students[i] == NULL)
            break;
        students[i]->showStudent();//const Student를 사용해야 한다.
    }
    cout << endl;
}

void selectionSortStudents(Student* students[], int numStudents) {
    // int compareStudents(const Student* b);를 사용한 정렬
    for (int i = 0; i < numStudents - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < numStudents; ++j) {
            if (students[j]->compareStudents(students[minIndex]) < 0) {
                minIndex = j;

            }
        }
        if (minIndex != i) {    
            students[i]->swap(students[minIndex]);      // !!유의!!
        }
    }
}
int main() {
    // 학생 객체 초기화
    int numStudents = 5;
    Student student1("Hong Gildong", 23, "houston");        //"Hong Gildong"은 data영역.rodata : const  //printf("%p", &"Hong Gildong");
    Student student2("hello", 22, "newyork");
    Student student3("houston", 13, "houston");
    Student student4("hong", 19, "busan");
    Student student5("kim", 33, "jeju");
    Student* students[5] = { &student1,&student2,&student3,&student4 ,&student5 };
    // 각 학생 정보 출력
    showStudents("Before Sort:", students, numStudents);
    student1.updateStudentCity("Busan");
    student1.showStudent();
    selectionSortStudents(students, numStudents);
    showStudents("After Sort", students, numStudents);
    system("pause");
    return 0;
}