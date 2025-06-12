#include <iostream>
#include <string>
#include <stdexcept> // runtime_error 포함
using namespace std;

// ==============================
// std::runtime_error 기반 예외 클래스 정의
// ==============================
class TableOverflow : public std::runtime_error {//stl 제공 예외객체를 상속
    int code;  // 상세 오류 코드
public:
    TableOverflow(int code, const string& message) // message는  std::runtime_error의 멤버 변수
        : std::runtime_error(message), code(code) {}

    int getCode() const noexcept { return code; }
    // void what(const string& message) override {
    //     runtime_error::what(message);
    //     cout << "오버플로우";
    // }
};

class TableUnderflow : public std::runtime_error {
    int code;
public:
    TableUnderflow(int code, const string& message)
        : std::runtime_error(message), code(code) {}

    int getCode() const noexcept { return code; }
};

// ==============================
// 템플릿 ObjectTable 클래스
// ==============================
template <typename T>
class ObjectTable {
    static const int capacity = 4;
    T* data[capacity];
    int size;

public:
    ObjectTable() : size(0) {
        for (int i = 0; i < capacity; ++i)
            data[i] = nullptr;
    }

    ~ObjectTable() {
        for (int i = 0; i < size; ++i)
            delete data[i];
    }

    void add(T* obj) {
        if (size >= capacity)
            throw TableOverflow(1001, "오버플로우: 더 이상 객체를 추가할 수 없습니다.");
        data[size++] = obj;
    }

    void remove() {
        if (size <= 0)
            throw TableUnderflow(2001, "언더플로우: 테이블이 비어 있습니다.");
        delete data[--size];
        data[size] = nullptr;
    }

    void show() const {
        if (size <= 0)
            throw TableUnderflow(2002, "언더플로우: 출력할 객체가 없습니다.");

        cout << "[Object Table 내용 출력]" << endl;
        for (int i = 0; i < size; ++i) {
            cout << i << ": ";
            data[i]->show();
        }
    }
};

// ==============================
// 테스트용 클래스
// ==============================
class Person {
    string name;
    int age;
public:
    Person(string name, int age) : name(name), age(age) {}

    void show() const {
        cout << "이름: " << name << ", 나이: " << age << endl;
    }
};

// ==============================
// 테스트 main 함수
// ==============================
int main() {
    ObjectTable<Person> table;

    try {
        table.add(new Person("홍길동", 30));
        table.add(new Person("김철수", 25));
        table.add(new Person("이영희", 22));
        table.add(new Person("박민수", 28));
        table.add(new Person("오버", 99)); // 오버플로우
    }
    catch (const TableOverflow& e) {
        cerr << "[예외 처리] 코드: " << e.getCode() << ", 메시지: " << e.what() << endl;
    }   //e.getCode()는 상속받는 예외객체[TableOverflow]의 멤버 함수, e.what()은 상속하는 base 예외객체[std::runtime_error]의 멤버함수

    try {
        table.show();
    }
    catch (const TableUnderflow& e) {
        cerr << "[예외 처리] 코드: " << e.getCode() << ", 메시지: " << e.what() << endl;
    }

    try {
        table.remove();
        table.remove();
        table.remove();
        table.remove();
        table.remove(); // 언더플로우
    }
    catch (const TableUnderflow& e) {
        cerr << "[예외 처리] 코드: " << e.getCode() << ", 메시지: " << e.what() << endl;
    }

    try {
        table.show(); // 언더플로우
    }
    catch (const TableUnderflow& e) {
        cerr << "[예외 처리] 코드: " << e.getCode() << ", 메시지: " << e.what() << endl;
    }

    return 0;
}
