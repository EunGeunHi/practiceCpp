#include <iostream>
#include <iomanip>
using namespace std;

// =====================================
// 추상 클래스: 공통 구조 (union + enum)
// =====================================
class ValueItem {
protected:
    enum Type { INT, FLOAT, CHAR } type;

    union {
        int i;
        float f;
        char c;
    } data;

public:
    virtual ~ValueItem() {
        cout << "[Base] ValueItem destroyed\n";
    }

    virtual void show() const = 0;
};

// =====================================
// 하위 클래스들
// =====================================

class IntItem : public ValueItem {
public:
    IntItem(int x) {
        type = INT;
        data.i = x;
    }

    ~IntItem() override {
        cout << "[Derived] IntItem destroyed\n";
    }

    void show() const override {
        cout << "[INT] " << data.i << endl;
    }
};

class FloatItem : public ValueItem {
public:
    FloatItem(float x) {
        type = FLOAT;
        data.f = x;
    }

    ~FloatItem() override {
        cout << "[Derived] FloatItem destroyed\n";
    }

    void show() const override {
        cout << fixed << setprecision(2);
        cout << "[FLOAT] " << data.f << endl;
    }
};

class CharItem : public ValueItem {
public:
    CharItem(char x) {
        type = CHAR;
        data.c = x;
    }

    ~CharItem() override {
        cout << "[Derived] CharItem destroyed\n";
    }

    void show() const override {
        cout << "[CHAR] '" << data.c << "'" << endl;
    }
};

// =====================================
// 리스트 출력 함수 (동적 바인딩)
// =====================================

void printList(ValueItem* arr[], int size) {
    cout << "\n[📋 출력 시작: 동적 바인딩 기반]\n";
    for (int i = 0; i < size; ++i) {
        if (arr[i]) arr[i]->show();
    }
}

// =====================================
// main 함수
// =====================================

int main() {
    const int SIZE = 5;
    ValueItem* list[SIZE];

    list[0] = new IntItem(42);
    list[1] = new FloatItem(3.14f);
    list[2] = new CharItem('A');
    list[3] = new IntItem(100);
    list[4] = new FloatItem(2.718f);

    printList(list, SIZE);  // ✅ 일반 함수에서 동적 바인딩

    // ✅ 메모리 해제 (가상 소멸자 필수)
    for (int i = 0; i < SIZE; ++i) {
        delete list[i];
    }

    return 0;
}
