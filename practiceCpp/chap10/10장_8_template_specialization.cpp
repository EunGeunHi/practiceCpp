#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

class Person;

template <typename T>
class ObjectTable;

// ===========================
// Person 계층 구조
// ===========================
class Person {
private:
    string pid;
    string name;
    string city;

    friend class ObjectTable<Person>;

public:
    Person(string pid, string name, string city);
    virtual void show() const;
    virtual string getName() const;
    virtual string getPid() const;
    virtual string getCity() const;
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
    string getEno() const;
    string getCompany() const;
    string getRole() const;
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
string Person::getCity() const { return city; }
bool Person::operator>(const Person& other) const {
    if (pid != other.getPid()) return pid > other.getPid();
    if (name != other.getName()) return name > other.getName();
    return city > other.getCity();
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
string Employee::getEno() const { return eno; }
string Employee::getCompany() const { return company; }
string Employee::getRole() const { return role; }
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
// 템플릿 ObjectTable 클래스
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
    void addInternal(T* obj); // 내부 접근용
    void remove(int index);
    void update(int index, T* obj);
    int search(T* target);
    void sort();
    void showAll() const;
    int getSize() const { return size; }
    T* get(int i) const { return data[i]; }
};

template <typename T>
ObjectTable<T>::ObjectTable() : size(0) {
    for (int i = 0; i < MAX; i++) data[i] = nullptr;
}

template <typename T>
ObjectTable<T>::~ObjectTable() {
    for (int i = 0; i < size; i++) delete data[i];
}

template <typename T>
void ObjectTable<T>::add(T* obj) {
    if (size < MAX) data[size++] = obj;
    else cout << "📛 테이블 용량 초과\n";
}

template <typename T>
void ObjectTable<T>::addInternal(T* obj) {
    add(obj);
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
// Employee 전용 정렬 특수화
// ===========================
template <>
void ObjectTable<Employee>::sort() {
    for (int i = 0; i < getSize() - 1; ++i)
        for (int j = i + 1; j < getSize(); ++j)
            if (get(i)->getEno() > get(j)->getEno() ||
                (get(i)->getEno() == get(j)->getEno() &&
                    get(i)->getCompany() > get(j)->getCompany()) ||
                (get(i)->getEno() == get(j)->getEno() &&
                    get(i)->getCompany() == get(j)->getCompany() &&
                    get(i)->getRole() > get(j)->getRole())) {
                swap(data[i], data[j]);
            }
}

// ===========================
// showAll 특수화
// ===========================
template <>
void ObjectTable<Student>::showAll() const {
    for (int i = 0; i < getSize(); i++) get(i)->show();
    cout << "총 학생 수: " << getSize() << "명\n";
}

template <>
void ObjectTable<Employee>::showAll() const {
    for (int i = 0; i < getSize(); i++) get(i)->show();
    cout << "총 직원 수: " << getSize() << "명\n";
}

// ===========================
// main 함수
// ===========================
int main() {
    ObjectTable<Person> ptable;
    ObjectTable<Student> stable;
    ObjectTable<Employee> etable;

    stable.add(new Student("S002", "Bob", "Busan", "ST002", "Math"));
    stable.add(new Student("S003", "Alice", "Seoul", "ST003", "Physics"));
    stable.add(new Student("S002", "Bob", "Busan", "ST001", "CS"));
    stable.add(new Student("S001", "Charlie", "Daejeon", "ST004", "AI"));

    etable.add(new Employee("E002", "Heidi", "Ulsan", "EMP02", "LG", "Manager"));
    etable.add(new Employee("E001", "Alice", "Seoul", "EMP01", "Samsung", "Engineer"));
    etable.add(new Employee("E001", "Alice", "Busan", "EMP03", "Samsung", "Planner"));
    etable.add(new Employee("E003", "Judy", "Daejeon", "EMP02", "Samsung", "Developer"));

    // 통합 테이블에 안전하게 삽입
    for (int i = 0; i < stable.getSize(); i++)
        ptable.addInternal(static_cast<Person*>(stable.get(i)));
    for (int i = 0; i < etable.getSize(); i++)
        ptable.addInternal(static_cast<Person*>(etable.get(i)));

    cout << "\n[👥 통합 목록 (정렬 전)]\n";
    ptable.showAll();

    ptable.sort();
    cout << "\n[👥 통합 목록 (정렬 후)]\n";
    ptable.showAll();

    // 🎓 학생 목록
    cout << "\n[🎓 학생 목록]\n";
    stable.showAll();

    // 💼 직원 목록 (정렬 전/후)
    cout << "\n[💼 직원 목록]\n";
    etable.showAll();

    cout << "\n[💼 Employee 목록 (정렬 전)]\n";
    etable.showAll();

    etable.sort();
    cout << "\n[💼 Employee 목록 (ENO, Company, Role 기준 정렬 후)]\n";
    etable.showAll();

    return 0;
}
