#include <iostream>
#include <string>

#include "10장_6_객체 테이블.h"

using namespace std;

// ===========================
// Person 멤버 함수 정의
// ===========================
Person::Person(string pid, string name, string city) : pid(pid), name(name), city(city) {}
void Person::show() const {
    cout << "👤 PID: " << pid << ", Name: " << name << ", City: " << city;
}
string Person::getName() const { return name; }
string Person::getPid() const { return pid; }
bool Person::operator>(const Person& other) const {
    return name > other.name;
}
bool Person::operator==(const Person& other) const {
    return pid == other.getPid();
}
Person::~Person() {}

// ===========================
// Student 멤버 함수 정의
// ===========================
Student::Student(string pid, string name, string city, string sid, string dept)
    : Person(pid, name, city), sid(sid), dept(dept) {}
void Student::show() const {
    Person::show();
    cout << " 🎓 SID: " << sid << ", Dept: " << dept << endl;
}
bool Student::operator>(const Person& other) const {
    if (*this == other) {
        const Student* p = dynamic_cast<const Student*>(&other);
        return p ? sid > p->sid : false;
    }
    return getName() > other.getName();
}
bool Student::operator==(const Person& other) const {
    return Person::operator==(other);
}

// ===========================
// Employee 멤버 함수 정의
// ===========================
Employee::Employee(string pid, string name, string city, string eno, string company, string role)
    : Person(pid, name, city), eno(eno), company(company), role(role) {}
void Employee::show() const {
    Person::show();
    cout << " 💼 ENO: " << eno << ", Role: " << role << ", Company: " << company << endl;
}
bool Employee::operator>(const Person& other) const {
    if (*this == other) {
        const Employee* p = dynamic_cast<const Employee*>(&other);
        return p ? eno > p->eno : false;
    }
    return getName() > other.getName();
}
bool Employee::operator==(const Person& other) const {
    return Person::operator==(other);
}



