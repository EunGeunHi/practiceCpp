#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <memory> // unique_ptr 사용을 위해 추가

using namespace std;

// ===========================
// 사용자 정의 예외 클래스
// ===========================
class TableException : public runtime_error {
    int code;
public:
    TableException(int code, const string& msg) : runtime_error(msg), code(code) {}
    int getCode() const { return code; }
};

// ===========================
// Person 기반 클래스 정의
// ===========================
class Person {
protected:
    string name; // 공통 속성으로 이름 추가
public:
    Person(string name = "") : name(name) {}
    virtual ~Person() {} // 다형적 소멸을 위한 가상 소멸자

    string getName() const { return name; }
    virtual void show() const = 0; // 순수 가상 함수
};

// ===========================
// Employee 클래스 정의 (Person 상속)
// ===========================
class Employee : public Person {
    string eno, city;
public:
    Employee(string eno = "", string ename = "", string city = "")
        : Person(ename), eno(eno), city(city) {
    }

    string getEno() const { return eno; }
    string getCity() const { return city; }

    void show() const override {
        cout << "[" << eno << "] " << name << " (" << city << ")\n";
    }
};

// ===========================
// Product 클래스 정의 (Person 상속)
// (편의상 Product도 Person을 상속받도록 하였지만,
//  실제 시나리오에서는 Product가 Person과 직접적인 관계가 없을 수 있습니다.
//  여기서는 ObjectTable<Person>을 사용하기 위한 예제 목적으로 상속 구조를 따랐습니다.)
// ===========================
class Product : public Person {
    string color, company;
public:
    Product(string pname = "", string color = "", string company = "")
        : Person(pname), color(color), company(company) {
    } // pname을 Person의 name으로 사용

    string getColor() const { return color; }
    string getCompany() const { return company; }

    void show() const override {
        cout << name << " [" << color << "] (" << company << ")\n";
    }
};

// ===========================
// ObjectTable 템플릿 클래스
// T는 Person*, 혹은 std::unique_ptr<Person> 같은 포인터 타입이 되어야 합니다.
// 여기서는 스마트 포인터 std::unique_ptr<T>를 사용합니다.
// ===========================
template <typename T> // T는 Person의 파생 클래스 타입 (예: Employee, Product)
class ObjectTable {
    vector<unique_ptr<T>> data; // 스마트 포인터로 객체 관리
    const size_t MAX_SIZE = 6;
public:
    // add 함수는 T 타입의 객체(unique_ptr)를 받아 저장
    void add(unique_ptr<T> obj, int errCode) {
        if (data.size() >= MAX_SIZE) {
            throw TableException(errCode, "오버플로우 예외 발생");
        }
        data.push_back(std::move(obj)); // unique_ptr 이동 시맨틱 사용
    }

    void remove(int qty, int errCode) {
        if (data.size() < qty) {
            throw TableException(errCode, "언더플로우 예외 발생");
        }
        for (int i = 0; i < qty; ++i) {
            data.pop_back();
        }
    }

    // 정렬 함수는 T의 포인터 타입을 비교하는 람다 함수를 받습니다.
    void sort(function<bool(const unique_ptr<T>&, const unique_ptr<T>&)> comp) {
        std::sort(data.begin(), data.end(), comp);
    }

    // showAll 함수는 각 객체의 show() 메서드를 호출
    void showAll() const { // const 멤버 함수로 변경
        for (const auto& item : data) { // unique_ptr 참조로 순회
            item->show(); // 포인터를 통해 show() 호출
        }
    }

    size_t size() const { return data.size(); }
};

// ===========================
// 메뉴 정의
// ===========================
enum Menu {
    SHOW_ALL = 1,
    SORT_BY_NAME,
    ADD_EMPLOYEE, ADD_PRODUCT,
    REMOVE_ITEM,
    EXIT
};

// ===========================
// Main 함수
// ===========================
int main() {
    ObjectTable<Person> pTable; // Person 타입의 스마트 포인터를 저장하는 테이블

    // 초기 데이터 추가
    try {
        pTable.add(make_unique<Employee>("E003", "홍길동", "부산"), 1001);
        pTable.add(make_unique<Employee>("E001", "강감찬", "울산"), 1001);
        pTable.add(make_unique<Employee>("E005", "연개소문", "창원"), 1001);
        pTable.add(make_unique<Employee>("E002", "계백", "양산"), 1001);
        pTable.add(make_unique<Product>("책상", "고동색", "이케아"), 1002); // 제품명->Person::name
        pTable.add(make_unique<Product>("갤럭시", "갈색", "삼성"), 1002);
    }
    catch (const TableException& ex) {
        cout << "[초기 데이터 로드 에러 코드: " << ex.getCode() << "] " << ex.what() << "\n";
    }

    int choice;
    while (true) {
        cout << "\n========= 메뉴 =========\n";
        cout << "1. 전체 항목 출력\n";
        cout << "2. 이름/제품명으로 정렬하여 출력\n";
        cout << "3. 직원 추가\n";
        cout << "4. 제품 추가\n";
        cout << "5. 항목 삭제 (최근 추가된 n개)\n";
        cout << "6. 종료\n";
        cout << "선택: "; cin >> choice;

        try {
            switch (static_cast<Menu>(choice)) {
            case SHOW_ALL:
                cout << "\n--- 전체 항목 ---\n";
                pTable.showAll();
                cout << "총 항목 수: " << pTable.size() << "개\n";
                break;
            case SORT_BY_NAME:
                cout << "\n--- 이름/제품명으로 정렬 ---\n";
                pTable.sort([](const unique_ptr<Person>& a, const unique_ptr<Person>& b) {
                    return a->getName() < b->getName();
                    });
                pTable.showAll();
                cout << "총 항목 수: " << pTable.size() << "개\n";
                break;
            case ADD_EMPLOYEE: {
                string eno, ename, city;
                cout << "사원번호(Exxx 입력): "; cin >> eno;
                cout << "사원이름 입력: "; cin >> ename;
                cout << "사원도시: "; cin >> city;
                pTable.add(make_unique<Employee>(eno, ename, city), 1001);
                cout << "직원 추가 완료.\n";
                break;
            }
            case ADD_PRODUCT: {
                string pname, color, company;
                cout << "제품명: "; cin >> pname;
                cout << "제품색상 입력: "; cin >> color;
                cout << "제조회사명: "; cin >> company;
                pTable.add(make_unique<Product>(pname, color, company), 1002);
                cout << "제품 추가 완료.\n";
                break;
            }
            case REMOVE_ITEM: {
                int qty;
                cout << "삭제할 항목 수: "; cin >> qty;
                pTable.remove(qty, 2000); // 2000은 일반적인 삭제 에러 코드
                cout << qty << "개의 항목이 삭제되었습니다.\n";
                break;
            }
            case EXIT:
                cout << "프로그램을 종료합니다.\n";
                return 0;
            default:
                cout << "잘못된 입력입니다.\n";
            }
        }
        catch (const TableException& ex) {
            cout << "[예외 발생: 코드 " << ex.getCode() << "] " << ex.what() << "\n";
        }
    }
    // system("pause")는 Windows 전용이므로 제거하거나 플랫폼에 맞게 변경
    return 0;
}