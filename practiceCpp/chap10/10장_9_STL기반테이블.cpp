#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ===========================
// Person 계층 구조
// ===========================
class Person {
private:
    string pid, name, city;
public:
    Person(string pid, string name, string city) : pid(pid), name(name), city(city) {}
    virtual ~Person() {}
    virtual void show() const {
        cout << "👤 PID: " << pid << ", Name: " << name << ", City: " << city;
    }
    string getPid() const { return pid; }
    string getName() const { return name; }
    string getCity() const { return city; }
    virtual bool operator>(const Person& other) const {
        if (pid != other.pid) return pid > other.pid;
        if (name != other.name) return name > other.name;
        return city > other.city;
    }
    virtual bool operator==(const Person& other) const {
        return pid == other.pid;
    }
};

class Student : public Person {
private:
    string sid, dept;
public:
    Student(string pid, string name, string city, string sid, string dept)
        : Person(pid, name, city), sid(sid), dept(dept) {}
    void show() const override {
        Person::show();
        cout << " 🎓 SID: " << sid << ", Dept: " << dept << endl;
    }
    bool operator>(const Person& other) const override {
        if (*this == other) {
            const Student* s = dynamic_cast<const Student*>(&other);
            return s ? sid > s->sid : false;
        }
        return getName() > other.getName();
    }
    bool operator==(const Person& other) const override {
        return Person::operator==(other);
    }
};

class Employee : public Person {
private:
    string eno, company, role;
public:
    Employee(string pid, string name, string city, string eno, string company, string role)
        : Person(pid, name, city), eno(eno), company(company), role(role) {}
    void show() const override {
        Person::show();
        cout << " 💼 ENO: " << eno << ", Role: " << role << ", Company: " << company << endl;
    }
    string getEno() const { return eno; }
    string getCompany() const { return company; }
    string getRole() const { return role; }
    bool operator>(const Person& other) const override {
        if (*this == other) {
            const Employee* e = dynamic_cast<const Employee*>(&other);
            return e ? eno > e->eno : false;
        }
        return getName() > other.getName();
    }
    bool operator==(const Person& other) const override {
        return Person::operator==(other);
    }
};

// ===========================
// 템플릿 ObjectTable 클래스
// ===========================
template <typename T>
class ObjectTable {
private:
    vector<T*> data;
public:
    ~ObjectTable() {
        for (auto p : data) delete p;
    }
    void add(T* obj) { data.push_back(obj); }
    void showAll() const {
        for (auto p : data) p->show();
    }
    void sort() {
        std::sort(data.begin(), data.end(), [](T* a, T* b) { return *a > *b; });
    }
    int getSize() const { return data.size(); }
    T* get(int i) const { return data[i]; }
};

template <>
void ObjectTable<Student>::showAll() const {
    for (auto p : data) p->show();
    cout << "총 학생 수: " << data.size() << "명\n";
}

template <>
void ObjectTable<Employee>::showAll() const {
    for (auto p : data) p->show();
    cout << "총 직원 수: " << data.size() << "명\n";
}

template <>
void ObjectTable<Employee>::sort() {
    std::sort(data.begin(), data.end(), [](Employee* a, Employee* b) {
        if (a->getEno() != b->getEno()) return a->getEno() < b->getEno();
        if (a->getCompany() != b->getCompany()) return a->getCompany() < b->getCompany();
        return a->getRole() < b->getRole();
        });
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

    for (int i = 0; i < stable.getSize(); i++)
        ptable.add(static_cast<Person*>(stable.get(i)));
    for (int i = 0; i < etable.getSize(); i++)
        ptable.add(static_cast<Person*>(etable.get(i)));

    cout << "\n[👥 통합 목록 (정렬 전)]\n";
    ptable.showAll();

    ptable.sort();
    cout << "\n[👥 통합 목록 (정렬 후)]\n";
    ptable.showAll();

    cout << "\n[🎓 학생 목록]\n";
    stable.showAll();

    cout << "\n[💼 직원 목록 (정렬 전)]\n";
    etable.showAll();

    etable.sort();
    cout << "\n[💼 직원 목록 (ENO, Company, Role 기준 정렬 후)]\n";
    etable.showAll();

    return 0;
}
