#include <iostream>
#include <cstring> // strcmp, strcpy 등 사용
using namespace std;

class Student {
private:
    char* name;
    int score;

public:
    Student() :name(nullptr), score(0) {}
    Student(const char* n, int s) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        score = s;
    }
    ~Student() {
        delete[] name;
    }
    const char* getName() {
        return name;
    }
    int getScore() {
        return score;
    }

    // 비교 함수
    bool isLessThan(const Student* other) {
        if (score != other->score) {
            return score < other->score;
        }
        else {
            return strcmp(name, other->name) < 0;
        }
    }
    void print() {
        cout << name << " - " << score << endl;
    }
};

void swap(Student*& a, Student*& b) {
    Student* temp = a;
    a = b;
    b = temp;
}
void sortStudents(Student* table[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (!table[j]->isLessThan(table[j + 1]))
                swap(table[j], table[j + 1]);
}

int main() {
    const int N = 4;

    Student s1("Alice", 85);
    Student s2("Bob", 75);
    Student s3("Charlie", 95);
    Student s4("Andy", 85);

    Student* table[N] = { &s1, &s2, &s3, &s4 };

    cout << "Before sorting:\n";
    for (int i = 0; i < N; ++i)
        table[i]->print();

    sortStudents(table, N);

    cout << "\nAfter sorting:\n";
    for (int i = 0; i < N; ++i)
        table[i]->print();

    return 0;
}
