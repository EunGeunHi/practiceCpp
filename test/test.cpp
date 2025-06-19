#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <functional>
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
// Employee Ŭ���� ����
// ===========================
class Employee {
    string eno, ename, city;
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
// Product Ŭ���� ����
// ===========================
class Product {
    string pname, color, company;
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
// ObjectTable ���ø� Ŭ����
// ===========================
template <typename T>
class ObjectTable {
    vector<T> data;
    const size_t MAX_SIZE = 6;
public:
    void add(const T& e, int errCode){
        if (data.size() >= MAX_SIZE) throw TableException(errCode, "�����÷ο� ���� �߻�");
        data.push_back(e);
    }
    void remove(int qty, int errCode) {
        if (data.size() < qty) throw TableException(errCode, "����÷ο� ���� �߻�");
        for (int i = 0; i < qty; ++i)
            data.pop_back();
    }

    void sort(function<bool(const T&, const T&)>comp){
        std::sort(data.begin(), data.end(), comp);
    }

    void showAll() {
        for (auto e : data) e.show();
    }

    size_t size() const { return data.size(); }
};

// ===========================
// ObjectTable<Employee> Ư��ȭ showAll()
// ===========================
void ObjectTable<Employee>::showAll() {
    for (auto e : data) e.show();
    cout<< "�� ��ǰ ��: " << data.size() << "��\n";
}
// ===========================
// ObjectTable<Product> Ư��ȭ showAll()
// ===========================

// ===========================
// �޴� ����
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
// Main �Լ�
// ===========================
int main() {
    ObjectTable<Employee> empTable;
    ObjectTable<Product> prodTable;

    Employee emp_list[] = {
        {"E003", "ȫ�浿", "�λ�"}, {"E001", "������", "���"},
        {"E005", "�����ҹ�", "â��"}, {"E002", "���", "���"},
        {"E006", "������", "�뱸"}, {"E007", "�̼���", "����"}
    };

    Product prod_list[] = {
        {"å��", "����", "���ɾ�"}, {"������", "����", "�Ｚ"},
        {"�鵵��", "�Ķ���", "�ĳ��Ҵ�"}, {"���콺", "���", "LG����"},
        {"����", "ȸ��", "�𳪹�"}, {"���", "����", "���"}
    };

    for (auto& e : emp_list) {
        try { empTable.add(e, 1001); }
        catch (const TableException& ex) {
            cout << "[���� �ڵ�: " << ex.getCode() << "] " << ex.what() << "\n";
        }
    }

    for (auto& p : prod_list) {
        try { prodTable.add(p, 1002); }
        catch (const TableException& ex) {
            cout << "[���� �ڵ�: " << ex.getCode() << "] " << ex.what() << "\n";
        }
    }

    int choice;
    while (true) {
        cout << "========= �޴� =========\n";
        cout << "1. ���� ���  2. ��ǰ ���\n";
        cout << "3. ���� �̸� ����  4. ���� ���� ����\n";
        cout << "5. ��ǰ �̸� ����  6. ��ǰ ���� ����\n";
        cout << "7. ���� �߰�  8. ��ǰ �߰�\n";
        cout << "9. ���� ���� 10. ��ǰ ����\n";
        cout << "11. ����\n";
        cout << "����: "; cin >> choice;

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
                cout << "�����ȣ(Exxx �Է�): ";
                cin >> eno;
                cout << "����̸� �Է�: ";
                cin >> ename;
                cout << "�������: ";
                cin >> city;
                empTable.add(Employee(eno, ename, city), 1001);
                break;
            }
            case ADD_PRODUCT: {
                string pname, color, company;
                cout << "��ǰ��: ";
                cin >> pname;
                cout << "��ǰ���� �Է�: ";
                cin >> color;
                cout << "����ȸ���: ";
                cin >> company;
                prodTable.add(Product(pname, color, company), 1002);
                break;
            }
            case REMOVE_EMPLOYEE: {
                int qty;
                cout << "������ ���� ��: "; cin >> qty;
                empTable.remove(qty, 2001);
                break;
            }
            case REMOVE_PRODUCT: {
                int qty;
                cout << "������ ��ǰ ��: "; cin >> qty;
                prodTable.remove(qty, 2002);
                break;
            }
            case EXIT:
                return 0;
            default:
                cout << "�߸��� �Է��Դϴ�.\n";
            }
        }
        catch (const TableException& ex) {
            cout << "[���� �߻�: �ڵ� " << ex.getCode() << "] " << ex.what() << "\n";
        }
    }
    system("pause");
}

//����-(�Ǹſ�,�繫��) ����ؼ� vector<T>data�� ��� ��ü �ֱ�
//���� Ŭ���� overflow underflow ����ؼ� errorcode + msg -> ���� ���� ����
//���ٽ����� Comparator ��ü ���� ����

/*
 *����Ŭ���� ����

 ���Employee�� ��ǰProduct ��ü�� ObjectTable<T>���ø� Ŭ������ �̿��� ����
 ����� ���� ���� ó���� ���� ��ü �߰� �� ���� ���� ������ ó���ϴ� ���α׷� ����

 *TableExceptin ����
 *code:���� �ڵ�
 *what()���� �޽��� ����
 *throw TableException(1001,"�뷮 �ʰ��� ��ü �߰� �Ұ�");

 *ObjectTable<T>����
void add(conmst T& obj, int errCode)
 MAX_SIEZ�ʰ��� Table Exception "�����÷ο� ���� �߻�"
void remove()
 ���� ��� ������ ū �� ���� ��û�� err "����÷ο� ���� �߻�"
void sort(function< boll(constT&, constT&)>f)
 ���ٽ� ���� ����

 *showAll()�Լ� Ư��ȭ
 ��� Employee ��ü ��� show()���
 �������ٿ� '��������: n��'�߰�

 */

 /*
 ========= �޴� =========
1. ���� ���  2. ��ǰ ���
3. ���� �̸� ����  4. ���� ���� ����
5. ��ǰ �̸� ����  6. ��ǰ ���� ����
7. ���� �߰�  8. ��ǰ �߰�
9. ���� ���� 10. ��ǰ ����
11. ����
����:1
[E003] ȫ�浿 (�λ�)
[E001] ������ (���)
[E005] �����ҹ� (â��)
[E002] ��� (���)
[E006] ������ (�뱸)
[E007] �̼��� (����)
�� ���� ��: 6��

========= �޴� =========
1. ���� ���  2. ��ǰ ���
3. ���� �̸� ����  4. ���� ���� ����
5. ��ǰ �̸� ����  6. ��ǰ ���� ����
7. ���� �߰�  8. ��ǰ �߰�
9. ���� ���� 10. ��ǰ ����
11. ����
����:2
å�� [����] (���ɾ�)
������ [����] (�Ｚ)
�鵵�� [�Ķ���] (�ĳ��Ҵ�)
���콺 [���] (LG����)
���� [ȸ��] (�𳪹�)
��� [����] (���)
�� ��ǰ ��: 6��

========= �޴� =========
1. ���� ���  2. ��ǰ ���
3. ���� �̸� ����  4. ���� ���� ����
5. ��ǰ �̸� ����  6. ��ǰ ���� ����
7. ���� �߰�  8. ��ǰ �߰�
9. ���� ���� 10. ��ǰ ����
11. ����
����:3
[E001] ������ (���)
[E002] ��� (���)
[E006] ������ (�뱸)
[E005] �����ҹ� (â��)
[E007] �̼��� (����)
[E003] ȫ�浿 (�λ�)
�� ���� ��: 6��

========= �޴� =========
1. ���� ���  2. ��ǰ ���
3. ���� �̸� ����  4. ���� ���� ����
5. ��ǰ �̸� ����  6. ��ǰ ���� ����
7. ���� �߰�  8. ��ǰ �߰�
9. ���� ���� 10. ��ǰ ����
11. ����
����:4
[E007] �̼��� (����)
[E006] ������ (�뱸)
[E003] ȫ�浿 (�λ�)
[E002] ��� (���)
[E001] ������ (���)
[E005] �����ҹ� (â��)
�� ���� ��: 6��

========= �޴� =========
1. ���� ���  2. ��ǰ ���
3. ���� �̸� ����  4. ���� ���� ����
5. ��ǰ �̸� ����  6. ��ǰ ���� ����
7. ���� �߰�  8. ��ǰ �߰�
9. ���� ���� 10. ��ǰ ����
11. ����
����:5
������ [����] (�Ｚ)
��� [����] (���)
���콺 [���] (LG����)
�鵵�� [�Ķ���] (�ĳ��Ҵ�)
���� [ȸ��] (�𳪹�)
å�� [����] (���ɾ�)
�� ��ǰ ��: 6��

========= �޴� =========
1. ���� ���  2. ��ǰ ���
3. ���� �̸� ����  4. ���� ���� ����
5. ��ǰ �̸� ����  6. ��ǰ ���� ����
7. ���� �߰�  8. ��ǰ �߰�
9. ���� ���� 10. ��ǰ ����
11. ����
����:6
������ [����] (�Ｚ)
��� [����] (���)
å�� [����] (���ɾ�)
���콺 [���] (LG����)
�鵵�� [�Ķ���] (�ĳ��Ҵ�)
���� [ȸ��] (�𳪹�)
�� ��ǰ ��: 6��

========= �޴� =========
1. ���� ���  2. ��ǰ ���
3. ���� �̸� ����  4. ���� ���� ����
5. ��ǰ �̸� ����  6. ��ǰ ���� ����
7. ���� �߰�  8. ��ǰ �߰�
9. ���� ���� 10. ��ǰ ����
11. ����
����:7
�����ȣ(Exxx �Է�): E100
����̸� �Է�: ��ö��
�������: û��
[���� �߻�: �ڵ� 1001]  �����÷ο� ���� �߻�

========= �޴� =========
1. ���� ���  2. ��ǰ ���
3. ���� �̸� ����  4. ���� ���� ����
5. ��ǰ �̸� ����  6. ��ǰ ���� ����
7. ���� �߰�  8. ��ǰ �߰�
9. ���� ���� 10. ��ǰ ����
11. ����
����:8
��ǰ��: ����
��ǰ���� �Է�: ȸ��
����ȸ���: �Ҵ�
[���� �߻�: �ڵ� 1002]  �����÷ο� ���� �߻�

========= �޴� =========
1. ���� ���  2. ��ǰ ���
3. ���� �̸� ����  4. ���� ���� ����
5. ��ǰ �̸� ����  6. ��ǰ ���� ����
7. ���� �߰�  8. ��ǰ �߰�
9. ���� ���� 10. ��ǰ ����
11. ����
����: 9
������ ���� ��: 7
[���� �߻�: �ڵ� 2001]  ����÷ο� ���� �߻�

========= �޴� =========
1. ���� ���  2. ��ǰ ���
3. ���� �̸� ����  4. ���� ���� ����
5. ��ǰ �̸� ����  6. ��ǰ ���� ����
7. ���� �߰�  8. ��ǰ �߰�
9. ���� ���� 10. ��ǰ ����
11. ����
����: 10
������ ��ǰ ��:  7
[���� �߻�: �ڵ� 2002]  ����÷ο� ���� �߻�

========= �޴� =========
1. ���� ���  2. ��ǰ ���
3. ���� �̸� ����  4. ���� ���� ����
5. ��ǰ �̸� ����  6. ��ǰ ���� ����
7. ���� �߰�  8. ��ǰ �߰�
9. ���� ���� 10. ��ǰ ����
11. ����
����: 11

 */