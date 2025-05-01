//6��_1_�޼ҵ�����������.cpp
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

using namespace std;

class Car {
private:
	char* manufacturer;
	//string manufacturer; ������ ����
	int speed;

	static int count;

	char* dupStr(const char* str) {	//�޸� �Ҵ��� ����
		char* ret = new char[strlen(str) + 1];
		strcpy(ret, str);
		return ret;
	}

public:
	//[������]
	//����Ʈ
	Car() {
		manufacturer = dupStr("Unknown");
		speed = 0;
		++count;
		cout << "default constructor ȣ��" << endl;
	}
	//�Ķ����
	Car(const char* manufacturer, int speed) : 
		speed(speed) {
		this->manufacturer = dupStr(manufacturer);
		++count;
		cout << "paramiterized constructor ȣ��" << endl;
	}
	//����
	Car(Car& other) {
		manufacturer = dupStr(other.manufacturer);
		speed = other.speed;
		++count;
		cout << "copy constructor ȣ��" << endl;
	}
	// �Ҹ���
	~Car() {
		delete[] manufacturer;
		--count;
		cout << "destructor ȣ��" << endl;
	}

	//[Getter Setter]
	const char* getManufacturer() const { return manufacturer; }
	const int getSpeed()const { return speed; }
	static const int getCarCount() { return count; }
	/*�Լ� ���� �ڿ� �ִ� const�� const ��ü������ ����Ҽ� �ִٴ� ��*/
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
			cout << "��ȿ���� ���� �ӵ� �Դϴ�. (0~300 km/h)\n";
			this->speed = 0;  // �⺻��
		}
		return *this;
	}
private:
	bool isValidSpeed(int speed) const { //�ӵ��� ��ȿ�� ������ �Ǻ�
		return speed >= 0 && speed <= 300;
	}

public:

	void showCars() const {
		cout << "������: " << manufacturer
			<< ", �ӵ�: " << speed << " km/h"
			<< ", ���� Car ��ü ��: " << count << endl;
	}
	void compareSpeed(const Car& other) const {
		if (this->speed > other.speed)
			cout << manufacturer << "�� " << other.getManufacturer() << "���� �����ϴ�.\n";
		else if (this->speed < other.speed)
			cout << manufacturer << "�� " << other.getManufacturer() << "���� �����ϴ�.\n";
		else
			cout << manufacturer << "�� " << other.getManufacturer() << "�� �ӵ��� �����ϴ�.\n";
	}

	//���� ������
	Car& operator=(const Car& other) {
		if (this == &other) return *this;

		delete[] manufacturer;
		manufacturer = dupStr(other.manufacturer);
		speed = other.speed;
		
		cout << "���� ������ ȣ���" << endl;
	}
};

int Car::count = 0; //static �������

int main() {
	const int SIZE = 5;

	Car* table1 = new Car[SIZE];
	table1[0].setManufacturer("����").setSpeed(100);
	cout << "table1[1] ����" << endl;
	table1[1] = Car("���Ÿ", 120);
	cout << "table1[2] �߸��� ����" << endl;
	table1[2].setManufacturer("���").setSpeed(-50);

	cout << "\n=== carSet[i].showCars() ===" << endl;
	for (int i = 0; i < SIZE; ++i) {
		table1[i].showCars();
	}

	cout << "\n���� ��ü Car ��ü ��:: " << Car::getCarCount() << endl;




}