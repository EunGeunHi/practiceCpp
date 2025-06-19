#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <memory> // unique_ptr ����� ���� �߰�

using namespace std;

// ===========================
// ����� ���� ���� Ŭ����
// ===========================
class TableException : public runtime_error {
    int code;
public:
    TableException(int code, const string& msg) : runtime_error(msg), code(code) {}
    int getCode() const { return code; }
};

// ===========================
// Person ��� Ŭ���� ����
// ===========================
class Person {
protected:
    string name; // ���� �Ӽ����� �̸� �߰�
public:
    Person(string name = "") : name(name) {}
    virtual ~Person() {} // ������ �Ҹ��� ���� ���� �Ҹ���

    string getName() const { return name; }
    virtual void show() const = 0; // ���� ���� �Լ�
};

// ===========================
// Employee Ŭ���� ���� (Person ���)
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
// Product Ŭ���� ���� (Person ���)
// (���ǻ� Product�� Person�� ��ӹ޵��� �Ͽ�����,
//  ���� �ó����������� Product�� Person�� �������� ���谡 ���� �� �ֽ��ϴ�.
//  ���⼭�� ObjectTable<Person>�� ����ϱ� ���� ���� �������� ��� ������ �������ϴ�.)
// ===========================
class Product : public Person {
    string color, company;
public:
    Product(string pname = "", string color = "", string company = "")
        : Person(pname), color(color), company(company) {
    } // pname�� Person�� name���� ���

    string getColor() const { return color; }
    string getCompany() const { return company; }

    void show() const override {
        cout << name << " [" << color << "] (" << company << ")\n";
    }
};

// ===========================
// ObjectTable ���ø� Ŭ����
// T�� Person*, Ȥ�� std::unique_ptr<Person> ���� ������ Ÿ���� �Ǿ�� �մϴ�.
// ���⼭�� ����Ʈ ������ std::unique_ptr<T>�� ����մϴ�.
// ===========================
template <typename T> // T�� Person�� �Ļ� Ŭ���� Ÿ�� (��: Employee, Product)
class ObjectTable {
    vector<unique_ptr<T>> data; // ����Ʈ �����ͷ� ��ü ����
    const size_t MAX_SIZE = 6;
public:
    // add �Լ��� T Ÿ���� ��ü(unique_ptr)�� �޾� ����
    void add(unique_ptr<T> obj, int errCode) {
        if (data.size() >= MAX_SIZE) {
            throw TableException(errCode, "�����÷ο� ���� �߻�");
        }
        data.push_back(std::move(obj)); // unique_ptr �̵� �ø�ƽ ���
    }

    void remove(int qty, int errCode) {
        if (data.size() < qty) {
            throw TableException(errCode, "����÷ο� ���� �߻�");
        }
        for (int i = 0; i < qty; ++i) {
            data.pop_back();
        }
    }

    // ���� �Լ��� T�� ������ Ÿ���� ���ϴ� ���� �Լ��� �޽��ϴ�.
    void sort(function<bool(const unique_ptr<T>&, const unique_ptr<T>&)> comp) {
        std::sort(data.begin(), data.end(), comp);
    }

    // showAll �Լ��� �� ��ü�� show() �޼��带 ȣ��
    void showAll() const { // const ��� �Լ��� ����
        for (const auto& item : data) { // unique_ptr ������ ��ȸ
            item->show(); // �����͸� ���� show() ȣ��
        }
    }

    size_t size() const { return data.size(); }
};

// ===========================
// �޴� ����
// ===========================
enum Menu {
    SHOW_ALL = 1,
    SORT_BY_NAME,
    ADD_EMPLOYEE, ADD_PRODUCT,
    REMOVE_ITEM,
    EXIT
};

// ===========================
// Main �Լ�
// ===========================
int main() {
    ObjectTable<Person> pTable; // Person Ÿ���� ����Ʈ �����͸� �����ϴ� ���̺�

    // �ʱ� ������ �߰�
    try {
        pTable.add(make_unique<Employee>("E003", "ȫ�浿", "�λ�"), 1001);
        pTable.add(make_unique<Employee>("E001", "������", "���"), 1001);
        pTable.add(make_unique<Employee>("E005", "�����ҹ�", "â��"), 1001);
        pTable.add(make_unique<Employee>("E002", "���", "���"), 1001);
        pTable.add(make_unique<Product>("å��", "����", "���ɾ�"), 1002); // ��ǰ��->Person::name
        pTable.add(make_unique<Product>("������", "����", "�Ｚ"), 1002);
    }
    catch (const TableException& ex) {
        cout << "[�ʱ� ������ �ε� ���� �ڵ�: " << ex.getCode() << "] " << ex.what() << "\n";
    }

    int choice;
    while (true) {
        cout << "\n========= �޴� =========\n";
        cout << "1. ��ü �׸� ���\n";
        cout << "2. �̸�/��ǰ������ �����Ͽ� ���\n";
        cout << "3. ���� �߰�\n";
        cout << "4. ��ǰ �߰�\n";
        cout << "5. �׸� ���� (�ֱ� �߰��� n��)\n";
        cout << "6. ����\n";
        cout << "����: "; cin >> choice;

        try {
            switch (static_cast<Menu>(choice)) {
            case SHOW_ALL:
                cout << "\n--- ��ü �׸� ---\n";
                pTable.showAll();
                cout << "�� �׸� ��: " << pTable.size() << "��\n";
                break;
            case SORT_BY_NAME:
                cout << "\n--- �̸�/��ǰ������ ���� ---\n";
                pTable.sort([](const unique_ptr<Person>& a, const unique_ptr<Person>& b) {
                    return a->getName() < b->getName();
                    });
                pTable.showAll();
                cout << "�� �׸� ��: " << pTable.size() << "��\n";
                break;
            case ADD_EMPLOYEE: {
                string eno, ename, city;
                cout << "�����ȣ(Exxx �Է�): "; cin >> eno;
                cout << "����̸� �Է�: "; cin >> ename;
                cout << "�������: "; cin >> city;
                pTable.add(make_unique<Employee>(eno, ename, city), 1001);
                cout << "���� �߰� �Ϸ�.\n";
                break;
            }
            case ADD_PRODUCT: {
                string pname, color, company;
                cout << "��ǰ��: "; cin >> pname;
                cout << "��ǰ���� �Է�: "; cin >> color;
                cout << "����ȸ���: "; cin >> company;
                pTable.add(make_unique<Product>(pname, color, company), 1002);
                cout << "��ǰ �߰� �Ϸ�.\n";
                break;
            }
            case REMOVE_ITEM: {
                int qty;
                cout << "������ �׸� ��: "; cin >> qty;
                pTable.remove(qty, 2000); // 2000�� �Ϲ����� ���� ���� �ڵ�
                cout << qty << "���� �׸��� �����Ǿ����ϴ�.\n";
                break;
            }
            case EXIT:
                cout << "���α׷��� �����մϴ�.\n";
                return 0;
            default:
                cout << "�߸��� �Է��Դϴ�.\n";
            }
        }
        catch (const TableException& ex) {
            cout << "[���� �߻�: �ڵ� " << ex.getCode() << "] " << ex.what() << "\n";
        }
    }
    // system("pause")�� Windows �����̹Ƿ� �����ϰų� �÷����� �°� ����
    return 0;
}