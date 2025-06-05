#include <iostream>
#include <string>
using namespace std;

// =================================
// Student 클래스 정의
// =================================
class Student {
    string sid;
    string name;
    string dept;

public:
    Student(string sid = "", string name = "", string dept = "")
        : sid(sid), name(name), dept(dept) {}

    string getSid() const { return sid; }
    string getName() const { return name; }
    string getDept() const { return dept; }

    // 출력용
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << "[" << s.sid << "] " << s.name << " (" << s.dept << ")";
        return os;
    }
};

// =================================
// Comparator 함수 객체들
// =================================
struct CompareBySid {
    // operator() 함수객체 - 객체를 함수호출처럼 사용:파이썬에서 빈번히 사용
    bool operator()(const Student& a, const Student& b) {//overriding a객체b객체 받아서 {} //operator()함수를 override
        return a.getSid() > b.getSid();  // 오름차순
    }
};

struct CompareByName {
    bool operator()(const Student& a, const Student& b) {
        return a.getName() > b.getName();
    }
};

struct CompareByDept {
    bool operator()(const Student& a, const Student& b) {
        return a.getDept() > b.getDept();
    }
};

// =================================
// 템플릿 swap 함수
// =================================
template <typename T>
void swapElements(T data[], int i, int j) {
    T temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

// =================================
// Comparator 기반 sort 함수
// =================================
template <typename T, typename Comparator>
void sort(T arr[], int size, Comparator comp) {
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size; ++j)
            if (comp(arr[i], arr[j])) // 오름차순: 앞이 크면 교환       CompareBySid(),CompareByName(),CompareByDept() = operator() 중 선택해서 사용
                swapElements(arr, i, j);
}

// =================================
// 출력 함수
// =================================
template <typename T>
void show(T arr[], int size) {
    for (int i = 0; i < size; ++i)
        cout << arr[i] << endl;
    cout << endl;
}

// =================================
// main 함수
// =================================
int main() {
    Student list[] = {
        Student("2024005", "Alice", "CS"),
        Student("2024002", "Bob", "EE"),
        Student("2024010", "Charlie", "ME"),
        Student("2024001", "Diana", "CS")
    };
    int size = sizeof(list) / sizeof(list[0]);

    cout << "[정렬 전]\n";
    show(list, size);

    cout << "[SID 기준 정렬]\n";
    sort(list, size, CompareBySid()); //CompareBySid() 는 생성자 -> struct CompareBySid인스턴스화
    show(list, size);

    cout << "[NAME 기준 정렬]\n";
    sort(list, size, CompareByName());
    show(list, size);

    cout << "[DEPT 기준 정렬]\n";
    sort(list, size, CompareByDept());
    show(list, size);

    return 0;
}
