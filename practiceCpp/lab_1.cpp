//enum menu{}
//����ġ������ �޴� ����

#include <iostream>

using namespace std;
enum Menu {
    M_EXIT,
    M_ADD,
    M_SUBTRACT,
    M_MULTIPLY,
    M_DIVIDE,
};

void showMenu();
void performAction(Menu m);

int main() {

    int input;
    Menu choice;

    while (true) {
        showMenu();
        cout << "�޴� ��ȣ�� �Է��ϼ���\n";
        cin >> input;

        //������ �Է� ó��
        if (cin.fail() || input < M_EXIT || input > M_DIVIDE) {
            cin.clear();    //�Է� ��Ʈ�� err���� ����
            cin.ignore(1000, '\n');  //�Էµ��ִ� ��Ʈ�� �ʱ�ȭ
            cout << "�߸��� �Է��Դϴ�.\n\n";
            continue;
        }

        choice = static_cast<Menu>(input);
        if (choice == M_EXIT) {
            cout << "���α׷��� �����մϴ�.\n";
            break;
        }

        performAction(choice);
    }
    return 0;
}

void showMenu() {
    cout << "\n====== �޴� ======\n";
    cout << "0. ����\n";
    cout << "1. ����\n";
    cout << "2. ����\n";
    cout << "3. ����\n";
    cout << "4. ������\n";
    cout << "==================\n";
}

void performAction(Menu m) {
    double a, b;

    cout << "�� ���ڸ� �Է��ϼ���: ";
    cin >> a >> b;

    switch (m) {
    case M_ADD:
        cout << "���: " << a + b << "\n";
        break;
    case M_SUBTRACT:
        cout << "���: " << a - b << "\n";
        break;
    case M_MULTIPLY:
        cout << "���: " << a * b << "\n";
        break;
    case M_DIVIDE:
        if (b != 0)
            cout << "���: " << a / b << "\n";
        else
            cout << "0���� ���� �� �����ϴ�.\n";
        break;
    default:
        cout << "�� �� ���� ����Դϴ�.\n";
    }
}

/*
cin >> input;���� ������ ���� int�� enum Menu�� ����ȯ�������
Menu choice = static_cast<Menu>(input);
*/