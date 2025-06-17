#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
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
// Employee 클래스 정의
// ===========================
class Employee {
    string eno, ename, city;
public:
    Employee(string eno = "", string ename = "", string city = "")
        : eno(eno), ename(ename), city(city) {}

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
    string pname, color, company;
public:
    Product(string pname = "", string color = "", string company = "")
        : pname(pname), color(color), company(company) {}

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
    vector<T> data;
    const size_t MAX_SIZE = 6;
public:

    size_t size() const { return data.size(); }
};

// ===========================
// ObjectTable<Employee> 특수화 showAll()
// ===========================

// ===========================
// ObjectTable<Product> 특수화 showAll()
// ===========================

// ===========================
// 메뉴 정의
// ===========================
enum Menu {
    SHOW_EMPLOYEE = 1, SHOW_PRODUCT,
    SORT_ENAME, SORT_CITY,
    SORT_PNAME, SORT_COLOR,
    ADD_EMPLOYEE, ADD_PRODUCT,
    REMOVE_EMPLOYEE, REMOVE_PRODUCT,
    EXIT
};

// ===========================
// Main 함수
// ===========================
int main() {
    ObjectTable<Employee> empTable;
    ObjectTable<Product> prodTable;

    Employee emp_list[] = {
        {"E003", "홍길동", "부산"}, {"E001", "강감찬", "울산"},
        {"E005", "연개소문", "창원"}, {"E002", "계백", "양산"},
        {"E006", "김유신", "대구"}, {"E007", "이순신", "광주"}
    };

    Product prod_list[] = {
        {"책상", "고동색", "이케아"}, {"갤럭시", "갈색", "삼성"},
        {"면도기", "파랑색", "파나소닉"}, {"마우스", "녹색", "LG전자"},
        {"볼펜", "회색", "모나미"}, {"라면", "검정", "농심"}
    };

    for (auto& e : emp_list) {
        try { empTable.add(e, 1001); }
        catch (const TableException& ex) {
            cout << "[에러 코드: " << ex.getCode() << "] " << ex.what() << "\n";
        }
    }

    for (auto& p : prod_list) {
        try { prodTable.add(p, 1002); }
        catch (const TableException& ex) {
            cout << "[에러 코드: " << ex.getCode() << "] " << ex.what() << "\n";
        }
    }

    int choice;
    while (true) {
        cout << "========= 메뉴 =========\n";
        cout << "1. 직원 출력  2. 제품 출력\n";
        cout << "3. 직원 이름 정렬  4. 직원 도시 정렬\n";
        cout << "5. 제품 이름 정렬  6. 제품 색상 정렬\n";
        cout << "7. 직원 추가  8. 제품 추가\n";
        cout << "9. 직원 삭제 10. 제품 삭제\n";
        cout << "11. 종료\n";
        cout << "선택: "; cin >> choice;

        try {
            switch (static_cast<Menu>(choice)) {
            case SHOW_EMPLOYEE:
                empTable.showAll(); break;
            case SHOW_PRODUCT:
                prodTable.showAll(); break;
            case SORT_ENAME:
                empTable.sort([](const Employee& a, const Employee& b) { return a.getEname() < b.getEname(); });
                empTable.showAll(); break;
            case SORT_CITY:
                empTable.sort([](const Employee& a, const Employee& b) { return a.getCity() < b.getCity(); });
                empTable.showAll(); break;
            case SORT_PNAME:
                prodTable.sort([](const Product& a, const Product& b) { return a.getPname() < b.getPname(); });
                prodTable.showAll(); break;
            case SORT_COLOR:
                prodTable.sort([](const Product& a, const Product& b) { return a.getColor() < b.getColor(); });
                prodTable.showAll(); break;
            case ADD_EMPLOYEE: {
                string eno, ename, city;
                cout << "사원번호(Exxx 입력): ";
                cin >> eno;
                cout << "사원이름 입력: ";
                cin >> ename;
                cout << "사원도시: ";
                cin >> city;
                empTable.add(Employee(eno, ename, city), 1001);
                break;
            }
            case ADD_PRODUCT: {
                string pname, color, company;
                cout << "제품명: ";
                cin >> pname;
                cout << "제품색상 입력: ";
                cin >> color;
                cout << "제조회사명: ";
                cin >> company;
                prodTable.add(Product(pname, color, company), 1002);
                break;
            }
            case REMOVE_EMPLOYEE: {
                int qty;
                cout << "삭제할 직원 수: "; cin >> qty;
                empTable.remove(qty, 2001);
                break;
            }
            case REMOVE_PRODUCT: {
                int qty;
                cout << "삭제할 제품 수: "; cin >> qty;
                prodTable.remove(qty, 2002);
                break;
            }
            case EXIT:
                return 0;
            default:
                cout << "잘못된 입력입니다.\n";
            }
        }
        catch (const TableException& ex) {
            cout << "[예외 발생: 코드 " << ex.getCode() << "] " << ex.what() << "\n";
        }
    }
    system("pause");
}

//직원-(판매원,사무원) 상속해서 vector<T>data에 상속 객체 넣기
//예외 클래스 overflow underflow 상속해서 errorcode + msg
//람다식으로 Comparator 객체 만들어서 적용

/*
 *예외클래스 연습

 사원Employee와 제품Product 객체를 ObjectTable<T>템플릿 클래스를 이용해 저장
 사용자 정의 예외 처리를 통해 객체 추가 및 삭제 시의 에러를 처리하는 프로그램 구현

 *TableExceptin 구현
 *code:에러 코드
 *what()으로 메시지 리턴
 *throw TableException(1001,"용량 초과로 객체 추가 불가");
 
 *ObjectTable<T>구현
void add(conmst T& obj, int errCode)
 MAX_SIEZ초과시 Table Exception "오버플로우 예외 발생"
void remove()
 현재 요소 수보다 큰 수 삭제 요청시 err "언더플로우 예외 발생"
void sort(function< boll(constT&, constT&)>f)
 람다식 기준 정렬
 
 *showAll()함수 특수화
 모든 Employee 객체 출력 show()사용
 마지막줄에 '총직원수: n명'추가

 */

 /*
 ========= 메뉴 =========
1. 직원 출력  2. 제품 출력
3. 직원 이름 정렬  4. 직원 도시 정렬
5. 제품 이름 정렬  6. 제품 색상 정렬
7. 직원 추가  8. 제품 추가
9. 직원 삭제 10. 제품 삭제
11. 종료
선택:1
[E003] 홍길동 (부산)
[E001] 강감찬 (울산)
[E005] 연개소문 (창원)
[E002] 계백 (양산)
[E006] 김유신 (대구)
[E007] 이순신 (광주)
총 직원 수: 6명

========= 메뉴 =========
1. 직원 출력  2. 제품 출력
3. 직원 이름 정렬  4. 직원 도시 정렬
5. 제품 이름 정렬  6. 제품 색상 정렬
7. 직원 추가  8. 제품 추가
9. 직원 삭제 10. 제품 삭제
11. 종료
선택:2
책상 [고동색] (이케아)
갤럭시 [갈색] (삼성)
면도기 [파랑색] (파나소닉)
마우스 [녹색] (LG전자)
볼펜 [회색] (모나미)
라면 [검정] (농심)
총 제품 수: 6개

========= 메뉴 =========
1. 직원 출력  2. 제품 출력
3. 직원 이름 정렬  4. 직원 도시 정렬
5. 제품 이름 정렬  6. 제품 색상 정렬
7. 직원 추가  8. 제품 추가
9. 직원 삭제 10. 제품 삭제
11. 종료
선택:3
[E001] 강감찬 (울산)
[E002] 계백 (양산)
[E006] 김유신 (대구)
[E005] 연개소문 (창원)
[E007] 이순신 (광주)
[E003] 홍길동 (부산)
총 직원 수: 6명

========= 메뉴 =========
1. 직원 출력  2. 제품 출력
3. 직원 이름 정렬  4. 직원 도시 정렬
5. 제품 이름 정렬  6. 제품 색상 정렬
7. 직원 추가  8. 제품 추가
9. 직원 삭제 10. 제품 삭제
11. 종료
선택:4
[E007] 이순신 (광주)
[E006] 김유신 (대구)
[E003] 홍길동 (부산)
[E002] 계백 (양산)
[E001] 강감찬 (울산)
[E005] 연개소문 (창원)
총 직원 수: 6명

========= 메뉴 =========
1. 직원 출력  2. 제품 출력
3. 직원 이름 정렬  4. 직원 도시 정렬
5. 제품 이름 정렬  6. 제품 색상 정렬
7. 직원 추가  8. 제품 추가
9. 직원 삭제 10. 제품 삭제
11. 종료
선택:5
갤럭시 [갈색] (삼성)
라면 [검정] (농심)
마우스 [녹색] (LG전자)
면도기 [파랑색] (파나소닉)
볼펜 [회색] (모나미)
책상 [고동색] (이케아)
총 제품 수: 6개

========= 메뉴 =========
1. 직원 출력  2. 제품 출력
3. 직원 이름 정렬  4. 직원 도시 정렬
5. 제품 이름 정렬  6. 제품 색상 정렬
7. 직원 추가  8. 제품 추가
9. 직원 삭제 10. 제품 삭제
11. 종료
선택:6
갤럭시 [갈색] (삼성)
라면 [검정] (농심)
책상 [고동색] (이케아)
마우스 [녹색] (LG전자)
면도기 [파랑색] (파나소닉)
볼펜 [회색] (모나미)
총 제품 수: 6개

========= 메뉴 =========
1. 직원 출력  2. 제품 출력
3. 직원 이름 정렬  4. 직원 도시 정렬
5. 제품 이름 정렬  6. 제품 색상 정렬
7. 직원 추가  8. 제품 추가
9. 직원 삭제 10. 제품 삭제
11. 종료
선택:7
사원번호(Exxx 입력): E100
사원이름 입력: 김철수
사원도시: 청주
[예외 발생: 코드 1001]  오버플로우 예외 발생

========= 메뉴 =========
1. 직원 출력  2. 제품 출력
3. 직원 이름 정렬  4. 직원 도시 정렬
5. 제품 이름 정렬  6. 제품 색상 정렬
7. 직원 추가  8. 제품 추가
9. 직원 삭제 10. 제품 삭제
11. 종료
선택:8
제품명: 라디오
제품색상 입력: 회색 
제조회사명: 소니
[예외 발생: 코드 1002]  오버플로우 예외 발생

========= 메뉴 =========
1. 직원 출력  2. 제품 출력
3. 직원 이름 정렬  4. 직원 도시 정렬
5. 제품 이름 정렬  6. 제품 색상 정렬
7. 직원 추가  8. 제품 추가
9. 직원 삭제 10. 제품 삭제
11. 종료
선택: 9
삭제할 직원 수: 7
[예외 발생: 코드 2001]  언더플로우 예외 발생

========= 메뉴 =========
1. 직원 출력  2. 제품 출력
3. 직원 이름 정렬  4. 직원 도시 정렬
5. 제품 이름 정렬  6. 제품 색상 정렬
7. 직원 추가  8. 제품 추가
9. 직원 삭제 10. 제품 삭제
11. 종료
선택: 10
삭제할 제품 수:  7
[예외 발생: 코드 2002]  언더플로우 예외 발생

========= 메뉴 =========
1. 직원 출력  2. 제품 출력
3. 직원 이름 정렬  4. 직원 도시 정렬
5. 제품 이름 정렬  6. 제품 색상 정렬
7. 직원 추가  8. 제품 추가
9. 직원 삭제 10. 제품 삭제
11. 종료
선택: 11
 
 */