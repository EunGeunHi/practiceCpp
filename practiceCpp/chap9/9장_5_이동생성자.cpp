#include <iostream>
#include <string>
using namespace std;

class Fruit {
private:
    string* data;

public:
    // 생성자
    Fruit(const string& str) {
        data = new string(str);
        cout << "[생성자] " << *data << endl;
    }

    // 복사 생성자 lvalue를 복사
    Fruit(const Fruit& other) {
        data = new string(*other.data);
        cout << "[복사 생성자] " << *data << endl;
    }

    // 이동 생성자 rvalue의 소유권 복사
    Fruit(Fruit&& other) noexcept {
        data = other.data;
        other.data = nullptr;
        cout << "[이동 생성자] " << *data << endl;
    }

    // 복사 치환 연산자
    Fruit& operator=(const Fruit& other) {
        if (this != &other) {
            delete data;
            data = new string(*other.data);
            cout << "[복사 치환 연산자] " << *data << endl;
        }
        return *this;
    }

    // 이동 치환 연산자
    // a = T("temp"); 객체도 rvalue
    //a = std::move(b); move(b)도 rvalue > move(b)는 b를 rvalue로 casting
    //a = func(); 함수 리턴값도 rvalue
    Fruit& operator=(Fruit&& other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;//할당된 자원의 소유권을 이전
            cout << "[이동 치환 연산자] " << *data << endl;
        }
        return *this;
    }

    // 소멸자
    ~Fruit() {
        if (data)
            cout << "[소멸자] " << *data << endl;
        else
            cout << "[소멸자] (null)" << endl;
        delete data;
    }
};
int main() {
    cout << "\n=== [1] 복사 생성자 호출 테스트 ===\n";
    Fruit f1("Apple");
    Fruit f2 = f1;  // 복사 생성자 호출

    cout << "\n=== [2] 이동 생성자 호출 테스트 ===\n";
    Fruit f3 = Fruit("Banana");  // 이동 생성자 호출
    //Fruit("Banana")는 rvalue, f3인 lvalue에 넘기고 rvalue 사라짐

    cout << "\n=== [3] 복사 치환 연산자 호출 테스트 ===\n";
    Fruit f4("Cherry");
    Fruit f5("Durian");
    f4 = f5;  // 복사 치환 연산자 호출

    cout << "\n=== [4] 이동 치환 연산자 호출 테스트 ===\n";
    Fruit f6("Elderberry");
    f6 = Fruit("Fig");  // 이동 치환 연산자 호출

    cout << "\n=== [5] 자기 자신에 대한 복사 대입 테스트 ===\n";
    f5 = f5;  // 자기 자신 대입

    return 0;
}
