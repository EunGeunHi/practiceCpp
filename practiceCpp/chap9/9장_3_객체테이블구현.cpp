/*
* 다중상속 : Person - Employee - Coder, Person - Student, Coder + Student - CoderStudent 객체들을 stack에 넣는 구현
* 객체들의 집합을 갖는 테이블의 배열을 갖는 클래스 구현하기 
*/
#include <iostream>
#include <string>
#define DefaultSize 50
using namespace std;

class Person { //추상 클래스로 구현한다
public:
    string GetName() { return pname; }
    void SetName(char* str) { pname = str; }
    string pid;
    string pname;
    Person() {}
    Person(string pid, string pname) : pid(pid), pname(pname) { }
    virtual void Print() = 0;
    virtual bool Equals(Person*) = 0;
    virtual ~Person() {}
    virtual int operator >(Person&) = 0;

};

class Employee : public Person {
private:
    string eno;
    string role;
public:
    Employee() :Person() {}
    Employee(string pid, string pname, string eno, string role) : Person(pid, pname), eno(eno), role(role) { }
    virtual void Print();
    virtual bool Equals(Person* p);
};
bool Employee::Equals(Person* p) {
    if (this->pid.compare(p->pid) == 0 && this->pname.compare(p->pname) == 0)
        return true;
    else
        return false;
}
void Employee::Print() {
    cout << "| " <<pid <<" |" << pname<< "| " << eno << " |" << " |" <<role<<" |";
}
class Coder : public Employee {
private:
    string language;
public:
    Coder() :Employee() {}
    Coder(string pid, string pname, string eno, string role, string language) : Employee(pid, pname, eno, role), language(language) {}
    void Print();
};
void Coder::Print() {
    Employee::Print();
    cout << "| " << language<<" |";
}

class Student : public Person {
private:
    string sid;
    string major;
public:
    Student(string pid, string pname, string sid, string major) : Person(pid, pname), sid(sid), major(major) { }
    void Print();
    bool Equals(Person* p);
};
void Student::Print() {
    Person::Print();
    cout << "| " << sid << " |" <<"| "<< major<<" |";
}
class CoderStudent : Student, Coder {
private:
    int cowork_year;
public:
    CoderStudent(int cowork_year, string sid, string major, string eno, string role, string language, string pid, string pname):
        Student(pid, pname, sid, major), Coder(pid, pname, eno, role, language),cowork_year(cowork_year) {}
};
const int tableMaxSize = 20;
class RecordTable { 
    int top;
    Person * data[tableMaxSize];
    int capacity;
public:
    RecordTable(int numberSet, int numberRecords) :tableMaxSize(numberSet),capacity(numberRecords) {
        topRecordTable = 0;
        data = new RecordSet * [numberSet];//10개의 set
        for (int i = 0; i < numberSet; i++) {
            data[i] = new RecordSet(numberRecords);//각 set는 5개 records
        }


    }
    int Add(Person*); // 정수 하나를 bag에 삽입
    int Delete(char*);
    sort();
    Person* Search(char*);
    void Print();
};
int RecordTable::Delete(char* str) {
    int recordSetDeleted = 0;
    for (int i = 0; i < topRecordTable; i++) {
        recordSetDeleted += data[i]->Delete(str);
        
    }
    return recordSetDeleted;

}//bag에서 정수 하나를 삭제
int RecordTable::Add(Person* p) {
    if (topRecordTable > tableMaxSize) {
        cout << "Overflow" << endl;
        return -1; //overflow 표시
    }
    
    if (data[topRecordTable]->Add(p) == -1) //data[i]이가 full이면
    {
        data[++topRecordTable]->Add(p);
        return 1;
    } 
}
void RecordTable::Print() {
    cout << endl;
    for (int i = 0; i <= topRecordTable; i++) {
        data[i]->Print();//동적 바인딩을 안하고 있다
    }
    cout << endl;
}
Person* RecordTable::Search(char* str) {
    for (int i = 0; i < topRecordTable; i++) {
        Person* p = data[i]->Search(str);
        if (p != nullptr) return p;
    }
    return nullptr;
}

int main() {
    Person* members[30];//Employee 선언으로 변경하는 문제 해결 필요 
    RecordTable table(10, 5);//10개의 record sets, 각 set은 5개의 records
    int select;
    Person* p;
    int result;
    while (1)
    {
        cout << "\n선택 1: member  객체 30개 입력, 2.table 출력, 3: table 객체 찾기,4. table에서 객체 삭제, 5. 종료" << endl;
        cin >> select;
        switch (select) {
        case 1://table에 객체 30개 입력
            members[0] = new Coder("p1", "hong", "E1", "Coding", "C++");
            members[1] = new Coder("p2", "hee", "E2", "Coding", "C++");
            members[2] = new Coder("p3", "kim", "E3", "Test", "JAVA");
            members[3] = new Coder("p4", "lee", "E4", "Test", "C#");
            members[4] = new Coder("p5", "ko", "E5", "Design", "GO");
            members[5] = new Coder("p6", "choi", "E6", "Design", "GO");
            members[6] = new Coder("p7", "han", "E7", "Sales", "PYTHON");
            members[7] = new Coder("p8", "na", "E8", "Sales", "C");
            members[8] = new Coder("p9", "you", "E9", "Account", "C++");
            members[9] = new Coder("p10", "song", "E10", "Production", "C#");
            members[10] = new Student("s011","coding", "E33", "manager", "23001", "hong");
            members[11] = new Student("s012", "coding", "E33", "manager", "23002", "ong");
            members[12] = new Student("s013", "coding", "E33", "manager", "23003", "dong");
            members[13] = new Student("s014", "coding", "E33", "manager", "23004", "fong");
            members[14] = new Student("s015", "coding", "E33", "manager", "23011", "tong");
            members[15] = new Student("s016", "coding", "E33", "manager", "23021", "nong");
            members[16] = new Student("s017", "coding", "E33", "manager", "23031", "mong");
            members[17] = new Student("s018", "coding", "E33", "manager", "23041", "kong");
            members[18] = new Student("s019", "coding", "E33", "manager", "23051", "long");
            members[19] = new Student("s020", "coding", "E33", "manager", "23101", "pong");
            members[20] = new Student("s021", "coding", "E53", "manager", "23141", "lim");
            members[21] = new Student("s022", "coding", "E53", "manager", "23241", "mim");
            members[22] = new Student("s023", "coding", "E53", "manager", "23341", "bim");
            members[23] = new Student("s024", "coding", "E53", "manager", "23441", "dim");
            members[24] = new Student("s025", "coding", "E53", "manager", "23541", "rim");
            members[25] = new Student("s026", "coding", "E53", "manager", "23641", "qim");
            members[26] = new Student("s021", "coding", "E53", "manager", "23741", "fim");
            members[27] = new Student("s021", "coding", "E53", "manager", "23841", "him");
            members[28] = new Student("s027", "coding", "E53", "manager", "23941", "jim");
            members[29] = new Student("s027", "coding", "E53", "manager", "24041", "jjj");
            

            for (int i = 0; i < 30; i++)
            {
                table.Add(members[i]);

            }
            break;
        case 2:
            // table의 모든 객체 출력하기
            //table 모양으로 출력해야 한다: | *** | ???? | === |으로 출력한다.

            table.Print();
            break;
        case 3:
            // table에서 객체 찾기

            p = table.Search("kim");
            if (p == nullptr) cout << "kim이 존재하지 않는다" << endl;
            else
                p->Print();
            break;
        case 4:
            //table에서 객체 삭제하기
            result = table.Delete("hong");
            if (result > 0)
                cout << "삭제된 records 숫자" <<result << endl;

            break;

        default:
            exit(0);

        }
    }
    system("pause");
    return 1;
}