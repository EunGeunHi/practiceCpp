#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student 구조체 정의
struct Student {
    char* name;
    int age;
    char* city;
};
void swap(struct Student* a, struct Student* b);
void interchangeSort(struct Student** arr, int n);
void showStudents(char* message, struct Student** arr, int n);
int main() {
    struct Student student1 = { "홍길동", 20, "서울" };
    struct Student student2 = { "김철수", 22, "부산" };
    struct Student student3 = { "김길동", 19, "대전" };
    struct Student student4 = { "길동", 39, "전주" };
    struct Student student5 = { "홍길순", 49, "광주" };
    struct Student student6 = { "이길동", 59, "대구" };
    struct Student student7 = { "빅길동", 9, "춘천" };

    struct Student* students[10] = { &student1, &student2, &student3, &student4,&student5,&student6,&student7 };
    // 나머지 요소들을 포인터로 초기화하시오


    // 배열의 크기 계산
    int numStudents = sizeof(students) / sizeof(students[0]);
    showStudents("정렬전 배열", students, numStudents);
    // 정렬 전 출력

    // interchangeSort 함수를 사용하여 구조체 객체 배열 정렬
    interchangeSort(students, numStudents);

    // 정렬 후 출력
    showStudents("정렬후 배열", students, numStudents);

    system("pause");

    return 0;
}
// 두 Student 객체를 교환하는 함수
void swap(struct Student* a, struct Student* b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

// 구조체 객체 배열을 이름(name)을 기준으로 오름차순 정렬하는 함수
