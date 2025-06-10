#include <iostream>
#include <string>

#include "10장_6_객체 테이블.h"
#include "10장_6_objectTable.h"



// ===========================
// main 함수
// ===========================
int main() {
    ObjectTable<Person> table;

    table.add(new Student("S001", "Alice", "Seoul", "ST001", "CS"));
    table.add(new Student("S002", "Bob", "Busan", "ST002", "Math"));
    table.add(new Student("S003", "Charlie", "Incheon", "ST003", "Physics"));
    table.add(new Student("S004", "David", "Daegu", "ST004", "Biology"));
    table.add(new Student("S005", "Eve", "Daejeon", "ST005", "Chemistry"));

    table.add(new Employee("E001", "Grace", "Seoul", "EMP01", "Samsung", "Engineer"));
    table.add(new Employee("E002", "Heidi", "Busan", "EMP02", "LG", "Manager"));
    table.add(new Employee("E003", "Ivan", "Ulsan", "EMP03", "SK", "Analyst"));
    table.add(new Employee("E004", "Judy", "Jeonju", "EMP04", "Hyundai", "Developer"));
    table.add(new Employee("E005", "Kevin", "Suwon", "EMP05", "Kakao", "Planner"));

    cout << "\n[👥 Person 목록 (정렬 전)]\n";
    table.showAll();

    table.sort();
    cout << "\n[👥 Person 목록 (정렬 후)]\n";
    table.showAll();

    return 0;
}
