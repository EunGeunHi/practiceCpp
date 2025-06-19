#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional> // std::function을 위해 필요

using namespace std;

// ===========================
// Employee 클래스 정의
// ===========================
class Employee {
    string eno;
    string ename;
    string city;

public:
    Employee(string eno = "", string ename = "", string city = "")
        : eno(eno), ename(ename), city(city) {
    }

    string getEno() const { return eno; }
    string getEname() const { return ename; }
    string getCity() const { return city; }


    void show() const {
        cout << "[" << eno << "] " << ename << " (" << city << ")\n";
    }
};

// ===========================
// Product 클래스 정의
// ===========================
class Product {
    string pname;
    string color;
    string company;

public:
    Product(string pname = "", string color = "", string company = "")
        : pname(pname), color(color), company(company) {
    }

    string getPname() const { return pname; }
    string getColor() const { return color; }
    string getCompany() const { return company; }

    void show() const {
        cout << pname << " [" << color << "] (" << company << ")\n";
    }
};

// ===========================
// ObjectTable 템플릿 클래스
// ===========================
template <typename T>
class ObjectTable {
private:
    vector<T> data;
public:
    void add(const T& obj) {
        data.push_back(obj);
    }
    void showAll() const {
        for (auto e : data) {
            e.show();
        }
        cout << endl;
    }
    void sort(function <bool(const T&, const T&)>comp) {
        std::sort(data.begin(), data.end(), comp);
    }
};

template<>
void ObjectTable<Employee>::showAll() const {
    for (auto e : data)
        e.show();
    cout << "총 " << data.size() << "명\n";
}

// ===========================
// 메뉴 정의
// ===========================
enum Menu {
    SHOW_EMPLOYEE = 1,
    SHOW_PRODUCT,
    SORT_ENAME,
    SORT_CITY,
    SORT_PNAME,
    SORT_COLOR,
    EXIT
};

// ===========================
// Main 함수
// ===========================
int main() {
    ObjectTable<Employee> empTable;
    ObjectTable<Product> prodTable;

    Employee emp_list[] = {
        Employee("E003", "홍길동", "부산"),
        Employee("E001", "강감찬", "울산"),
        Employee("E005", "연개소문", "창원"),
        Employee("E002", "계백", "양산")
    };
    int emp_size = sizeof(emp_list) / sizeof(emp_list[0]);

    Product prod_list[] = {
        Product("노트북", "고동색", "삼성전자"),
        Product("모니터", "갈색", "LG전자"),
        Product("휴대폰", "파랑색", "애플"),
        Product("자동차", "녹색", "현대차")
    };
    int prod_size = sizeof(prod_list) / sizeof(prod_list[0]);

    // 초기 데이터 추가
    for (int i = 0; i < emp_size; ++i)
        empTable.add(emp_list[i]);
    for (int i = 0; i < prod_size; ++i)
        prodTable.add(prod_list[i]);

    int choice;
    while (true) {
        cout << "========= 메뉴 =========\n";
        cout << "1. 직원 목록 출력\n";
        cout << "2. 제품 목록 출력\n";
        cout << "3. 직원 이름 기준 정렬\n";
        cout << "4. 직원 도시 기준 정렬\n";
        cout << "5. 제품 이름 기준 정렬\n";
        cout << "6. 제품 색상 기준 정렬\n";
        cout << "7. 종료\n";
        cout << "메뉴 선택: ";
        cin >> choice;

        switch (static_cast<Menu>(choice)) {
        case SHOW_EMPLOYEE:
            cout << "\n[직원 목록 출력]\n";
            empTable.showAll();
            break;
        case SHOW_PRODUCT:
            cout << "\n[제품 목록 출력]\n";
            prodTable.showAll();
            break;
        case SORT_ENAME:
            empTable.sort([](const Employee& a, const Employee& b) {
                return a.getEname() < b.getEname();
                });
            cout << "\n[이름 기준 직원 정렬 완료]\n";
            empTable.showAll();
            break;
        case SORT_CITY:
            empTable.sort([](const Employee& a, const Employee& b) {
                return a.getCity() < b.getCity();
                });
            cout << "\n[도시 기준 직원 정렬 완료]\n";
            empTable.showAll();
            break;
        case SORT_PNAME:
            prodTable.sort([](const Product& a, const Product& b) {
                return a.getPname() < b.getPname();
                });
            cout << "\n[제품 이름 기준 정렬 완료]\n";
            prodTable.showAll();
            break;
        case SORT_COLOR:
            prodTable.sort([](const Product& a, const Product& b) {
                return a.getColor() < b.getColor();
                });
            cout << "\n[제품 색상 기준 정렬 완료]\n";
            prodTable.showAll();
            break;
        case EXIT:
            cout << "프로그램을 종료합니다.\n";
            return 0;
        default:
            cout << "잘못된 입력입니다. 다시 선택하세요.\n";
        }
    }
    system("pause");
    return 0;
}

/*
 * 템플릿 클래스 연습
 사원Employee와 제품Product 객체를 관리하는 ObjectTable<T>템플릿 클래스 구현

 내부적으로 STL의 vector<T>를 사용하여 데이터 저장.
 람다식을 이용한 정렬
 객체 출력 및 정렬 로직 구현

 void add(const T& obj);
   요소 추가
 void showAll() const;
   전체 출력
   마지막에 총 개수를 출력 '총 직원 수 :n명','총 제품수  : n개'
 void sort(function <bool(const T&, const T&)>comp);
   정렬
   STL sort함수 사용하여 구현 가능
*/

/*

========= 메뉴 =========
1. 직원 목록 출력
2. 제품 목록 출력
3. 직원 이름 기준 정렬
4. 직원 도시 기준 정렬
5. 제품 이름 기준 정렬
6. 제품 색상 기준 정렬
7. 종료
메뉴 선택: 1
[직원 목록 출력]
[E003] 홍길동 (부산)
[E001] 강감찬 (울산)
[E005] 연개소문 (창원)
[E002] 계백 (양산)
총 개수: 4

========= 메뉴 =========
1. 직원 목록 출력
2. 제품 목록 출력
3. 직원 이름 기준 정렬
4. 직원 도시 기준 정렬
5. 제품 이름 기준 정렬
6. 제품 색상 기준 정렬
7. 종료
메뉴 선택: 2
[제품 목록 출력]
노트북 [고동색] (삼성전자)
모니터 [갈색] (LG전자)
휴대폰 [파랑색] (애플)
자동차 [녹색] (현대차)
총 개수: 4

========= 메뉴 =========
1. 직원 목록 출력
2. 제품 목록 출력
3. 직원 이름 기준 정렬
4. 직원 도시 기준 정렬
5. 제품 이름 기준 정렬
6. 제품 색상 기준 정렬
7. 종료
메뉴 선택: 3
[이름 기준 직원 정렬 완료]
[E001] 강감찬 (울산)
[E002] 계백 (양산)
[E005] 연개소문 (창원)
[E003] 홍길동 (부산)
총 개수: 4

========= 메뉴 =========
1. 직원 목록 출력
2. 제품 목록 출력
3. 직원 이름 기준 정렬
4. 직원 도시 기준 정렬
5. 제품 이름 기준 정렬
6. 제품 색상 기준 정렬
7. 종료
메뉴 선택: 4
[도시 기준 직원 정렬 완료]
[E003] 홍길동 (부산)
[E002] 계백 (양산)
[E001] 강감찬 (울산)
[E005] 연개소문 (창원)
총 개수: 4

========= 메뉴 =========
1. 직원 목록 출력
2. 제품 목록 출력
3. 직원 이름 기준 정렬
4. 직원 도시 기준 정렬
5. 제품 이름 기준 정렬
6. 제품 색상 기준 정렬
7. 종료
메뉴 선택: 5
[제품 이름 기준 정렬 완료]
노트북 [고동색] (삼성전자)
모니터 [갈색] (LG전자)
자동차 [녹색] (현대차)
휴대폰 [파랑색] (애플)
총 개수: 4

========= 메뉴 =========
1. 직원 목록 출력
2. 제품 목록 출력
3. 직원 이름 기준 정렬
4. 직원 도시 기준 정렬
5. 제품 이름 기준 정렬
6. 제품 색상 기준 정렬
7. 종료
메뉴 선택: 6
[제품 색상 기준 정렬 완료]
모니터 [갈색] (LG전자)
노트북 [고동색] (삼성전자)
자동차 [녹색] (현대차)
휴대폰 [파랑색] (애플)
총 개수: 4

========= 메뉴 =========
1. 직원 목록 출력
2. 제품 목록 출력
3. 직원 이름 기준 정렬
4. 직원 도시 기준 정렬
5. 제품 이름 기준 정렬
6. 제품 색상 기준 정렬
7. 종료
메뉴 선택: 7
프로그램을 종료합니다.
*/