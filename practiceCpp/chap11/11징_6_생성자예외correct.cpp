#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class TableOverflow : public std::runtime_error {
    int code;
public:
    TableOverflow(int code, const string& message)
        : std::runtime_error(message), code(code) {}
    int getCode() const noexcept { return code; }
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
    static const int MAX_CAPACITY = 4;
    T** data;
    int size;
    int capacity;

public:
    ObjectTable(int cap) : size(0) {
        if (cap <= 0 || cap >= MAX_CAPACITY)
            throw invalid_argument("유효하지 않은 테이블 크기입니다. (1~3만 허용)");

        capacity = cap;
        data = new T * [capacity];
        for (int i = 0; i < capacity; ++i)
            data[i] = nullptr;
    }

    ~ObjectTable() {
        for (int i = 0; i < size; ++i)
            delete data[i];
        delete[] data;
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
// main(): 사용자 입력 & error correction
// ==============================
int main() {
    ObjectTable<Person>* table = nullptr;
    int capacity;

    // 사용자 입력 반복
    while (true) {
        cout << "테이블의 크기(1~3)를 입력하세요: ";
        cin >> capacity;

        try {
            table = new ObjectTable<Person>(capacity);
            break;  // 생성 성공 시 루프 종료
        }
        catch (const invalid_argument& e) {
            cerr << "[입력 오류] " << e.what() << endl;
            cerr << "다시 입력해주세요.\n";
        }
    }

    try {
        table->add(new Person("홍길동", 30));
        table->add(new Person("김철수", 25));
        table->add(new Person("이영희", 22));
        table->add(new Person("오버", 99)); // 일부러 오버플로우 유도
    }
    catch (const TableOverflow& e) {
        cerr << "[예외 처리] 코드: " << e.getCode() << ", 메시지: " << e.what() << endl;
    }

    try {
        table->show();
    }
    catch (const TableUnderflow& e) {
        cerr << "[예외 처리] 코드: " << e.getCode() << ", 메시지: " << e.what() << endl;
    }

    try {
        table->remove();
        table->remove();
        table->remove();
        table->remove();  // 언더플로우 유도
    }
    catch (const TableUnderflow& e) {
        cerr << "[예외 처리] 코드: " << e.getCode() << ", 메시지: " << e.what() << endl;
    }

    try {
        table->show();  // 언더플로우
    }
    catch (const TableUnderflow& e) {
        cerr << "[예외 처리] 코드: " << e.getCode() << ", 메시지: " << e.what() << endl;
    }

    delete table;
    return 0;
}
