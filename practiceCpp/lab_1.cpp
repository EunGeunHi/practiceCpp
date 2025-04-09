//enum menu{}
//스위치문으로 메뉴 구현

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
        cout << "메뉴 번호를 입력하세요\n";
        cin >> input;

        //범위밖 입력 처리
        if (cin.fail() || input < M_EXIT || input > M_DIVIDE) {
            cin.clear();    //입력 스트림 err상태 해제
            cin.ignore(1000, '\n');  //입력돼있는 스트림 초기화
            cout << "잘못된 입력입니다.\n\n";
            continue;
        }

        choice = static_cast<Menu>(input);
        if (choice == M_EXIT) {
            cout << "프로그램을 종료합니다.\n";
            break;
        }

        performAction(choice);
    }
    return 0;
}

void showMenu() {
    cout << "\n====== 메뉴 ======\n";
    cout << "0. 종료\n";
    cout << "1. 덧셈\n";
    cout << "2. 뺄셈\n";
    cout << "3. 곱셈\n";
    cout << "4. 나눗셈\n";
    cout << "==================\n";
}

void performAction(Menu m) {
    double a, b;

    cout << "두 숫자를 입력하세요: ";
    cin >> a >> b;

    switch (m) {
    case M_ADD:
        cout << "결과: " << a + b << "\n";
        break;
    case M_SUBTRACT:
        cout << "결과: " << a - b << "\n";
        break;
    case M_MULTIPLY:
        cout << "결과: " << a * b << "\n";
        break;
    case M_DIVIDE:
        if (b != 0)
            cout << "결과: " << a / b << "\n";
        else
            cout << "0으로 나눌 수 없습니다.\n";
        break;
    default:
        cout << "알 수 없는 명령입니다.\n";
    }
}

/*
cin >> input;에서 정수로 받은 int를 enum Menu로 형변환해줘야함
Menu choice = static_cast<Menu>(input);
*/