#include <iostream>
#include <string>
using namespace std;

// ==============================
// 사용자 정의 예외 클래스
// ==============================
class TableOverflow {
public:
    string what() const { return "오버플로우: 더 이상 객체를 추가할 수 없습니다."; }
};

class TableUnderflow {
public:
    string what() const { return "언더플로우: 테이블이 비어 있습니다."; }
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
            throw TableOverflow();
        data[size++] = obj;
    }

    void remove() {
        if (size <= 0)
            throw TableUnderflow();
        delete data[--size];
        data[size] = nullptr;
    }

    void show() const {
        if (size <= 0)
            throw TableUnderflow();

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
    catch (TableOverflow& e) {
        cout << "[예외 처리] " << e.what() << endl;
    }

    try {
        table.show();
    }
    catch (TableUnderflow& e) {
        cout << "[예외 처리] " << e.what() << endl;
    }

    try {
        table.remove();
        table.remove();
        table.remove();
        table.remove();
        table.remove(); // 언더플로우
    }
    catch (TableUnderflow& e) {
        cout << "[예외 처리] " << e.what() << endl;
    }

    try {
        table.show(); // 언더플로우
    }
    catch (TableUnderflow& e) {
        cout << "[예외 처리] " << e.what() << endl;
    }

    return 0;
}
