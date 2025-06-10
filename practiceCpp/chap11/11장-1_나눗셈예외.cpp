// 11장-1.BASIC.CPP   11.1 예외의 기본 개념
// 기본적인 예외 처리의 예제
#include <iostream>
#include <cassert>
using namespace std;
// 두 개의 정수 값을 필요로 하는 함수 선언
// 두 번째 parameter는 0이 아니어야 한다
double divide (int num1, int num2){
    if (num2 == 0)
        throw ("Divide by zero");
    else if (num1 == 0)
       // assert(num1 != 0);
		//abort();//abnormal program termination
		//exit(0);
		throw("분자 = 0");
	else
		return static_cast<double>(num1) / num2;
}
void main ( ){
    int num1, num2 ;
    cout << "두 개의 정수를 입력하세요 (예: 10 0): ";
    cin >> num1 >> num2 ;
    try{
        cout << num1 << " / " << num2 << " = " << divide (num1, num2) 
              << endl;
    }
    //*
    catch (const char * text){
        cout << "ERROR: " << text << endl ;
    }
    catch (...) {
        cout << "[알 수 없는 예외] 처리됨" << endl;
    }
    cout << "프로그램 정상 종료" << endl;
    //*/
	system("pause");
}