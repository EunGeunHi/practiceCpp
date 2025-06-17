#include <iostream>
#include <string>
using namespace std;

// =================================
// Employee 클래스 정의
// =================================
class Employee {
    string eno;
    string ename;
    string city;

public:
    Employee(string eno = "", string ename = "", string city = "")
        : eno(eno), ename(ename), city(city) {}

    string getEno() const { return eno; }
    string getEname() const { return ename; }
    string getCity() const { return city; }

    friend ostream& operator<<(ostream& os, const Employee& e) {
        os << "[" << e.eno << "] " << e.ename << " (" << e.city << ")";
        return os;
    }
};

// =================================
// Product 클래스 정의
// =================================
class Product {
    string pname;
    string color;
    string company;

public:
    Product(string pname = "", string color = "", string company = "")
        : pname(pname), color(color), company(company) {}

    string getPname() const { return pname; }
    string getColor() const { return color; }
    string getCompany() const { return company; }

    friend ostream& operator<<(ostream& os, const Product& p) {
        os << p.pname << " [" << p.color << "] (" << p.company << ")";
        return os;
    }
};

// =================================
// Comparator 구조체 정의
// =================================


// =================================
// 템플릿 swap, sort, show 함수
// =================================






// =================================
// enum 메뉴 정의
// =================================
enum Menu {
    SHOW_EMPLOYEE = 1,
    SHOW_PRODUCT,
    SORT_ENAME,
    SORT_CITY,
    SORT_PNAME,
    SORT_COLOR,
    EXIT
};

// =================================
// main 함수
// =================================
int main() {
    Employee emp_list[] = {
        Employee("E003", "홍길동", "부산"),
        Employee("E001", "강감찬", "울산"),
        Employee("E005", "연개소문", "창원"),
        Employee("E002", "계백", "양산")
    };
    int emp_size = sizeof(emp_list) / sizeof(emp_list[0]);

    Product prod_list[] = {
        Product("자동차", "고동색", "기아차"),
        Product("노트북", "갈색", "삼성"),
        Product("휴대폰", "파랑색", "애플"),
        Product("화장품", "녹색", "LG화학")
    };
    int prod_size = sizeof(prod_list) / sizeof(prod_list[0]);

    int choice;
    while (true) {
        cout << "==== MENU ====\n";
        cout << "1. Employee 테이블 출력\n";
        cout << "2. Product 테이블 출력\n";
        cout << "3. Employee 테이블의 Name 정렬\n";
        cout << "4. Employee 테이블의 City 정렬\n";
        cout << "5. Product 테이블의 Name 정렬\n";
        cout << "6. Product 테이블의 Color 정렬\n";
        cout << "7. 종료\n";
        cout << "메뉴 선택: ";
        cin >> choice;

        switch (static_cast<Menu>(choice)) {
        case SHOW_EMPLOYEE:
            cout << "[Employee 테이블 출력]\n";
            show(emp_list, emp_size);
            break;
        case SHOW_PRODUCT:
            cout << "[Product 테이블 출력]\n";
            show(prod_list, prod_size);
            break;
        case SORT_ENAME:
            cout << "[Employee 테이블의 Name 정렬 결과]\n";
            sort(emp_list, emp_size, CompareByEname());
            show(emp_list, emp_size);
            break;
        case SORT_CITY:
            cout << "[Employee 테이블의 City 정렬 결과]\n";
            sort(emp_list, emp_size, CompareByCity());
            show(emp_list, emp_size);
            break;
        case SORT_PNAME:
            cout << "[Product 테이블의 Name 정렬 결과]\n";
            sort(prod_list, prod_size, CompareByPname());
            show(prod_list, prod_size);
            break;
        case SORT_COLOR:
            cout << "[Product 테이블의 Color 정렬 결과]\n";
            sort(prod_list, prod_size, CompareByColor());
            show(prod_list, prod_size);
            break;
        case EXIT:
            cout << "프로그램을 종료합니다.\n";
            return 0;
        default:
            cout << "잘못된 선택입니다. 다시 입력하세요.\n";
        }
    }

    return 0;
}


/*
 *템플릿 함수 연습

 클래스 구현
 -Employee 클래스
    변수: eno, ename, city
    접근자: getEno(), getEname(), getCity()
    operator<< :오버로딩을 통해 출력
      [E001] 홍길동 (부산)
 -Product 클래스
    변수: pname,color,company
    접근자: getPname(),getColor(),getCompany()
    operator<< :오버로딩을 통해 출력
      자동차 [고동색] (기아차)
 
 템플릿 함수 구현
 -void show(T arr[],int size)
   모든 객체를 cout으로 출력
   출력후 '총 객체수 N' 출력
 -void sort(T arr[],int size,Comparator comp)
   버블 정렬 알고리즘을 사용하여 정렬
   주어진 Comparator를 기준으로 배열 정렬
 -void swapElements(T data[], int i, int j)

  Comparator 구조체 구현
    각 구조체는 bool operator()(const T&am const T&b){}을 제공해야함
 -CompareByEname 직원 이름 오른차순
 -CompareByCity 직원 도시 오른차순
 -CompareByPname 제품 이름 오른차순
 -CompareByColor 제품 색 오른차순
  
*/



/*

==== MENU ====
1. Employee 테이블 출력
2. Product 테이블 출력
3. Employee 테이블의 Name 정렬
4. Employee 테이블의 City 정렬
5. Product 테이블의 Name 정렬
6. Product 테이블의 Color 정렬
7. 종료
메뉴 선택: 1
[Employee 테이블 출력]
[E003] 홍길동 (부산)
[E001] 강감찬 (울산)
[E005] 연개소문 (창원)
[E002] 계백 (양산)

==== MENU ====
1. Employee 테이블 출력
2. Product 테이블 출력
3. Employee 테이블의 Name 정렬
4. Employee 테이블의 City 정렬
5. Product 테이블의 Name 정렬
6. Product 테이블의 Color 정렬
7. 종료
메뉴 선택: 2
[Product 테이블 출력]
자동차 [고동색] (기아차)
노트북 [갈색] (삼성)
휴대폰 [파랑색] (애플)
화장품 [녹색] (LG화학)

==== MENU ====
1. Employee 테이블 출력
2. Product 테이블 출력
3. Employee 테이블의 Name 정렬
4. Employee 테이블의 City 정렬
5. Product 테이블의 Name 정렬
6. Product 테이블의 Color 정렬
7. 종료
메뉴 선택: 3
[Employee 테이블의 Name 정렬 결과]
[E001] 강감찬 (울산)
[E002] 계백 (양산)
[E005] 연개소문 (창원)
[E003] 홍길동 (부산)

==== MENU ====
1. Employee 테이블 출력
2. Product 테이블 출력
3. Employee 테이블의 Name 정렬
4. Employee 테이블의 City 정렬
5. Product 테이블의 Name 정렬
6. Product 테이블의 Color 정렬
7. 종료
메뉴 선택: 4
[Employee 테이블의 City 정렬 결과]
[E003] 홍길동 (부산)
[E002] 계백 (양산)
[E001] 강감찬 (울산)
[E005] 연개소문 (창원)

==== MENU ====
1. Employee 테이블 출력
2. Product 테이블 출력
3. Employee 테이블의 Name 정렬
4. Employee 테이블의 City 정렬
5. Product 테이블의 Name 정렬
6. Product 테이블의 Color 정렬
7. 종료
메뉴 선택: 5
[Product 테이블의 Name 정렬 결과]
노트북 [갈색] (삼성)
자동차 [고동색] (기아차)
화장품 [녹색] (LG화학)
휴대폰 [파랑색] (애플)

==== MENU ====
1. Employee 테이블 출력
2. Product 테이블 출력
3. Employee 테이블의 Name 정렬
4. Employee 테이블의 City 정렬
5. Product 테이블의 Name 정렬
6. Product 테이블의 Color 정렬
7. 종료
메뉴 선택: 6
[Product 테이블의 Color 정렬 결과]
노트북 [갈색] (삼성)
자동차 [고동색] (기아차)
화장품 [녹색] (LG화학)
휴대폰 [파랑색] (애플)

==== MENU ====
1. Employee 테이블 출력
2. Product 테이블 출력
3. Employee 테이블의 Name 정렬
4. Employee 테이블의 City 정렬
5. Product 테이블의 Name 정렬
6. Product 테이블의 Color 정렬
7. 종료
메뉴 선택: 7
프로그램을 종료합니다.

*/