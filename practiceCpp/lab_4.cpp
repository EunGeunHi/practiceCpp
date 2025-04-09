#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Student {
private:
    string name;
    int score;

public:
    Student(string n, int s) : name(n), score(s) {}

    string getName() const { return name; }
    int getScore() const { return score; }

    // �� �Լ� (���Ŀ�)
    static bool compare(const Student* a, const Student* b) {
        if (a->score != b->score)
            return a->score < b->score; // ���� ��������
        else
            return a->name < b->name;   // �̸� ������
    }

    void print() const {
        cout << name << " - " << score << endl;
    }
};

// ���� �Լ� (���� ����)
void sortStudents(Student* table[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (!Student::compare(table[j], table[j + 1])) {
                swap(table[j], table[j + 1]);
            }
        }
    }
}

int main() {
    const int N = 4;

    Student s1("Alice", 85);
    Student s2("Bob", 75);
    Student s3("Charlie", 95);
    Student s4("Andy", 85); // Alice�� ���� ����

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