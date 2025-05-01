//6장_1_메소드접근제한자.cpp
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

using namespace std;

class Car {
private:
	char* manufacturer;
	//string manufacturer; 버전도 연습
	int speed;

	static int count;

	char* dupStr(const char* str) {	//메모리 할당후 복사
		char* ret = new char[strlen(str) + 1];
		strcpy(ret, str);
		return ret;
	}

public:
	//[생성자]
	//디폴트
	Car() {
		manufacturer = dupStr("Unknown");
		speed = 0;
		++count;
		cout << "default constructor 호출" << endl;
	}
	//파라미터
	Car(const char* manufacturer, int speed) : 
		speed(speed) {
		this->manufacturer = dupStr(manufacturer);
		++count;
		cout << "paramiterized constructor 호출" << endl;
	}
	//복사
	Car(Car& other) {
		manufacturer = dupStr(other.manufacturer);
		speed = other.speed;
		++count;
		cout << "copy constructor 호출" << endl;
	}
	// 소멸자
	~Car() {
		delete[] manufacturer;
		--count;
		cout << "destructor 호출" << endl;
	}

	//[Getter Setter]
	const char* getManufacturer() const { return manufacturer; }
	const int getSpeed()const { return speed; }
	static const int getCarCount() { return count; }
	/*함수 정의 뒤에 있는 const는 const 객체에서도 사용할수 있다는 뜻*/
	Car& setManufacturer(const char* str) {
		delete[] manufacturer;
		manufacturer = dupStr(str);
		return *this;
	}
	Car& setSpeed(int speed) {
		if (isValidSpeed(speed)) {
			this->speed = speed;
		}
		else {
			cout << "유효하지 않은 속도 입니다. (0~300 km/h)\n";
			this->speed = 0;  // 기본값
		}
		return *this;
	}
private:
	bool isValidSpeed(int speed) const { //속도가 유효한 값인지 판별
		return speed >= 0 && speed <= 300;
	}

public:

	void showCars() const {
		cout << "제조사: " << manufacturer
			<< ", 속도: " << speed << " km/h"
			<< ", 현재 Car 객체 수: " << count << endl;
	}
	void compareSpeed(const Car& other) const {
		if (this->speed > other.speed)
			cout << manufacturer << "가 " << other.getManufacturer() << "보다 빠릅니다.\n";
		else if (this->speed < other.speed)
			cout << manufacturer << "가 " << other.getManufacturer() << "보다 느립니다.\n";
		else
			cout << manufacturer << "와 " << other.getManufacturer() << "의 속도가 같습니다.\n";
	}

	//대입 연산자
	Car& operator=(const Car& other) {
		if (this == &other) return *this;

		delete[] manufacturer;
		manufacturer = dupStr(other.manufacturer);
		speed = other.speed;
		
		cout << "대입 연산자 호출됨" << endl;
	}
};

int Car::count = 0; //static 멤버변수

int main() {
	const int SIZE = 5;

	Car* table1 = new Car[SIZE];
	table1[0].setManufacturer("현대").setSpeed(100);
	cout << "table1[1] 수정" << endl;
	table1[1] = Car("토요타", 120);
	cout << "table1[2] 잘못된 수정" << endl;
	table1[2].setManufacturer("기아").setSpeed(-50);

	cout << "\n=== carSet[i].showCars() ===" << endl;
	for (int i = 0; i < SIZE; ++i) {
		table1[i].showCars();
	}

	cout << "\n현재 전체 Car 객체 수:: " << Car::getCarCount() << endl;




}