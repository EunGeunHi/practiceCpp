#include <iostream>
#include <string>
using namespace std;

#define tableMaxSize 50

enum Menu {
    INPUT = 1,
    PRINT,
    SEARCH,
    DELETE,
    SORT,
    EXIT
};

class Person {
public:
    string pid;
    string pname;
    Person() {}
    Person(string pid, string pname) : pid(pid), pname(pname) {}
    virtual void Print() = 0;
    virtual bool Equals(Person*) = 0;
    virtual ~Person() {}
    virtual int operator >(Person&) = 0;
};

class Employee : public Person {
protected:
    string eno;
    string role;
public:
    Employee() : Person() {}
    Employee(string pid, string pname, string eno, string role)
        : Person(pid, pname), eno(eno), role(role) {}
    virtual void Print();
    virtual bool Equals(Person* p);
    int operator >(Person& other) override {
        return pname > other.pname ? 1 : 0;
    }
};

bool Employee::Equals(Person* p) {
    return this->pid == p->pid && this->pname == p->pname;
}

void Employee::Print() {
    cout << "| " << pid << " | " << pname << " | " << eno << " | " << role << " |";
}

class Coder : public Employee {
private:
    string language;
public:
    Coder() : Employee() {}
    Coder(string pid, string pname, string eno, string role, string language)
        : Employee(pid, pname, eno, role), language(language) {}
    void Print() override {
        Employee::Print();
        cout << " " << language << " |\n";
    }
    bool Equals(Person* p) override { return Employee::Equals(p); }
    int operator >(Person& other) override {
        return pname > other.pname ? 1 : 0;
    }
};

class Student : public Person {
private:
    string sid;
    string major;
public:
    Student(string pid, string pname, string sid, string major)
        : Person(pid, pname), sid(sid), major(major) {}
    void Print() override {
        cout << "| " << pid << " | " << pname << " | " << sid << " | " << major << " |\n";
    }
    bool Equals(Person* p) override { return this->pid == p->pid && this->pname == p->pname; }
    int operator >(Person& other) override {
        return pname > other.pname ? 1 : 0;
    }
};

class CoderStudent : public Coder, public Student {
private:
    int cowork_year;
public:
    CoderStudent(int year, string sid, string major, string eno, string role, string language, string pid, string pname)
        : Person(pid, pname), Coder(pid, pname, eno, role, language), Student(pid, pname, sid, major), cowork_year(year) {}
    void Print() override {
        Coder::Print();
        Student::Print();
        cout << "| Co-work Year: " << cowork_year << " |\n";
    }
    bool Equals(Person* p) override { return this->pid == p->pid && this->pname == p->pname; }
    int operator >(Person& other) override {
        return pname > other.pname ? 1 : 0;
    }
};

class RecordTable {
private:
    Person* data[tableMaxSize]; //has-a 관계
    int count;

public:
    RecordTable() : count(0) {}

    void Add(Person* p) {
        if (count < tableMaxSize) {
            data[count++] = p;
        }
        else {
            cout << "테이블이 가득 찼습니다.\n";
        }
    }

    int Delete(const string& name) {
        int delCount = 0;
        for (int i = 0; i < count; ) {
            if (data[i]->pname == name) {
                delete data[i];
                for (int j = i; j < count - 1; ++j) {
                    data[j] = data[j + 1];
                }
                --count;
                ++delCount;
            }
            else {
                ++i;
            }
        }
        return delCount;
    }

    Person* Search(const string& name) {
        for (int i = 0; i < count; ++i) {
            if (data[i]->pname == name)
                return data[i];
        }
        return nullptr;
    }

    void Swap(int i, int j) {
        Person* temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }

    void Sort() {
        for (int i = 0; i < count - 1; ++i) {
            for (int j = 0; j < count - i - 1; ++j) {
                if (*data[j] > *data[j + 1]) {
                    Swap(j, j + 1);
                }
            }
        }
        cout << "정렬 완료.\n";
    }

    void Print() {
        cout << "\n=== 전체 인원 출력 ===\n";
        for (int i = 0; i < count; ++i) {
            data[i]->Print();
        }
    }

    ~RecordTable() {
        for (int i = 0; i < count; ++i) delete data[i];
    }
};

int main() {
    RecordTable table;
    Person* members[15];
    int select;

    while (true) {
        cout << "\n1. 객체 입력, 2. 전체 출력, 3. 검색, 4. 삭제, 5. 정렬, 6. 종료: ";
        cin >> select;

        switch (static_cast<Menu>(select)) {
        case INPUT:
            members[0] = new Student("s1", "Alice", "2023001", "CS");
            members[1] = new Student("s2", "Bob", "2023002", "Math");
            members[2] = new Student("s3", "Cathy", "2023003", "Physics");
            members[3] = new Student("s4", "David", "2023004", "Chemistry");
            members[4] = new Student("s5", "Eva", "2023005", "Biology");

            members[5] = new Coder("c1", "Tom", "E1", "Dev", "C++");
            members[6] = new Coder("c2", "Jerry", "E2", "Dev", "Java");
            members[7] = new Coder("c3", "Mike", "E3", "QA", "Python");
            members[8] = new Coder("c4", "Jane", "E4", "Design", "JavaScript");
            members[9] = new Coder("c5", "Lily", "E5", "Support", "Go");

            members[10] = new CoderStudent(2, "23001", "CS", "E6", "AI", "Python", "cs1", "Kim");
            members[11] = new CoderStudent(1, "23002", "Math", "E7", "ML", "C++", "cs2", "Lee");
            members[12] = new CoderStudent(3, "23003", "EE", "E8", "Cloud", "Java", "cs3", "Park");
            members[13] = new CoderStudent(4, "23004", "Data", "E9", "Infra", "Rust", "cs4", "Choi");
            members[14] = new CoderStudent(5, "23005", "Bio", "E10", "Research", "R", "cs5", "Han");

            for (int i = 0; i < 15; i++) table.Add(members[i]);
            cout << "입력 완료.\n";
            break;

        case PRINT:
            table.Print();
            break;

        case SEARCH: {
            string name;
            cout << "검색할 이름: ";
            cin >> name;
            Person* found = table.Search(name);
            if (found) found->Print();
            else cout << name << " 을(를) 찾을 수 없습니다.\n";
            break;
        }
        case DELETE: {
            string name;
            cout << "삭제할 이름: ";
            cin >> name;
            int count = table.Delete(name);
            cout << "삭제된 객체 수: " << count << "\n";
            break;
        }
        case SORT:
            table.Sort();
            break;

        case EXIT:
        default:
            return 0;
        }
    }
}
