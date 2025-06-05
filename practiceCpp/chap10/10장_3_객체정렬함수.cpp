#include <iostream>
#include <string>
using namespace std;

// ==============================
// Student 클래스 정의
// ==============================
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

    // operator > 오버로딩: sid 기준 사전식 정렬
    bool operator>(const Student& other) const {
        return sid > other.sid; // 하드코딩-> 정렬 기준 sid말고 name,get등으로 바꾸려면 일일히 바꿔야함
        // => Comparator 정렬 필요(10_4)
    }
    

    // 출력 지원 함수
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << "[" << s.sid << "] " << s.name << " (" << s.dept << ")";
        return os;
    }
};

// ==============================
// 템플릿 swap 함수
// ==============================
template <typename T>
void swapElements(T data[], int i, int j) {
    T temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

// ==============================
// 템플릿 버블 정렬 함수
// ==============================
template <typename T>
void sort(T arr[], int size) {
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (arr[i] > arr[j])        //  Student s1 > Student s2 이 필요함으로 bool operator>(const Student& other)구현해야함
                swapElements(arr, i, j);
}

// ==============================
// 템플릿 출력 함수
// ==============================
template <typename T>
void show(T arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << endl;
    cout << endl;
}

// ==============================
// main 함수
// ==============================
int main() {
    Student list[] = {
        Student("2024005", "Alice", "CS"),
        Student("2024002", "Bob", "EE"),
        Student("2024010", "Charlie", "ME"),
        Student("2024001", "Diana", "CS")
    };
    //계층으로 해서 연습 ex) Person list[]={Student s1(),Employee e1(), WorkSutdents ws1()...};
    int sSize = sizeof(list) / sizeof(list[0]);
    //계층으로 한다면 포인터로 해야 sSize 올바름 객체 인스턴스바로 넣으면 사이즈 객체별로 다를수 있기에
    //에초에 동적바인딩하려면 ptr로 해야되네

    cout << "[정렬 전]\n";
    show(list, sSize);

    sort(list, sSize);

    cout << "[정렬 후: sid 기준 오름차순]\n";
    show(list, sSize);

    return 0;
}