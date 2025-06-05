#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

// ===========================
// Person 계층 구조
// ===========================
class Person {
private:
    string pid;
    string name;
    string city;
public:
    Person(string pid, string name, string city);
    virtual void show() const;
    virtual string getName() const;
    virtual string getPid() const;
    virtual bool operator>(const Person& other) const;
    virtual bool operator==(const Person& other) const;
    virtual ~Person();
};

class Student : public Person {
private:
    string sid;
    string dept;
public:
    Student(string pid, string name, string city, string sid, string dept);
    void show() const override;
    bool operator>(const Person& other) const override;
    bool operator==(const Person& other) const override;
};

class Employee : public Person {
private:
    string eno;
    string company;
    string role;
public:
    Employee(string pid, string name, string city, string eno, string company, string role);
    void show() const override;
    bool operator>(const Person& other) const override;
    bool operator==(const Person& other) const override;
};

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

// ===========================
// 템플릿 ObjectTable 클래스 > ObjectTable.h로 선언부와 같이 저장
// ===========================
template <typename T>
class ObjectTable {
private:
    T* data[MAX];
    int size;
public:
    ObjectTable();
    ~ObjectTable();
    void add(T* obj);
    void remove(int index);
    void update(int index, T* obj);
    int search(T* target);
    void sort();
    void showAll() const;
};

template <typename T>
ObjectTable<T>::ObjectTable() : size(0) {
    for (int i = 0; i < MAX; i++)
        data[i] = nullptr;
}

template <typename T>
ObjectTable<T>::~ObjectTable() {
    for (int i = 0; i < size; i++)
        delete data[i];
}

template <typename T>
void ObjectTable<T>::add(T* obj) {
    if (size < MAX) data[size++] = obj;
    else cout << "📛 테이블 용량 초과\n";
}

template <typename T>
void ObjectTable<T>::remove(int index) {
    if (index >= 0 && index < size) {
        delete data[index];
        for (int i = index; i < size - 1; i++)
            data[i] = data[i + 1];
        data[--size] = nullptr;
    }
}

template <typename T>
void ObjectTable<T>::update(int index, T* obj) {
    if (index >= 0 && index < size) {
        delete data[index];
        data[index] = obj;
    }
}

template <typename T>
int ObjectTable<T>::search(T* target) {
    for (int i = 0; i < size; i++)
        if (*data[i] == *target)
            return i;
    return -1;
}

template <typename T>
void ObjectTable<T>::sort() {
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (*data[i] > *data[j])
                swap(data[i], data[j]);
}

template <typename T>
void ObjectTable<T>::showAll() const {
    for (int i = 0; i < size; i++)
        data[i]->show();
}

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
