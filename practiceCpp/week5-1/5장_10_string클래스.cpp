

#include <iostream>
#include <string>

using namespace std;

class Car {
private:
    string manufacturer;
    string licensePlate;
    int speed;

    static int count;

public:
    Car() {
        manufacturer = "Unknown";
        licensePlate = "None";
        speed = 0;
        ++count;
        cout << "Default Constructor ȣ��" << endl;
    }

    Car(string manufacturer, string licensePlate, int speed) {
        this->manufacturer = manufacturer;
        this->licensePlate = licensePlate;
        this->speed = speed;
        ++count;
        cout << "Parameterized Constructor ȣ��" << endl;
    }

    ~Car() {
        cout << "Destructor ȣ��: " << manufacturer << " (" << licensePlate << ")" << endl;
        --count;
    }

    // setters
    Car& setManufacturer(const string& m) {
        manufacturer = m;
        return *this;
    }

    Car& setLicensePlate(const string& l) {
        licensePlate = l;
        return *this;
    }

    Car& setSpeed(int s) {
        speed = s;
        return *this;
    }

    void show() const {
        cout << "������: " << manufacturer
            << ", ��ȣ��: " << licensePlate
            << ", �ӵ�: " << speed << " km/h"
            << ", ��ü ��ü ��: " << count << endl;
    }

    static int getCount() {
        return count;
    }
};

// static ���� ����
int Car::count = 0;

// ===================== main =====================
int main() {
    const int SIZE = 3;
    Car* carSet = new Car[SIZE];  // ���� Car ��ü �迭 ����

    carSet[0].setManufacturer("Hyundai").setLicensePlate("12��3456").setSpeed(100);
    carSet[1].setManufacturer("Toyota").setLicensePlate("78��9012").setSpeed(120);
    carSet[2].setManufacturer("Kia").setLicensePlate("34��5678").setSpeed(90);

    cout << "\n=== Car ��ü ���� ��� ===" << endl;
    for (int i = 0; i < SIZE; ++i) {
        carSet[i].show();
    }

    cout << "\n���� ��ü Car ��ü ��: " << Car::getCount() << endl;

    delete[] carSet;  // �Ҹ��� �ڵ� ȣ��

    cout << "\n��ü ���� �� ��: " << Car::getCount() << endl;

    return 0;
}


/*
!!���蹮��!!
���� .
class Car{
    char *name;
    string name1;

    public:
    Car(){
        name = ?? //new char[];
        name1 = ??
    
    !!���Ϲ��� ���۷��� �Լ�
    &Car
    }


<����1>
enum menu{}
    ����ġ������ �޴� ����

<����2> ���� ����
student *table[];
��ü �ʱ�ȭ
    "����","���׽ý�",5000
    "BMW","520d",6000

<����3>
class mothod, class ���� ���� �� ���

<����4>
class student{
    char* name; //string name; ������
    int age;
}
    �����Ҵ��� new char[]�� malloc X

<����5>
s1 = new student[10];
s2 = new student();
delete s1;  ->�Ҹ��� ���� 

<����6>
student *table[];���Ĺ���
char*name;string name

<����7>
class Student{
private:
    ��� data member�� private��
public:
    getter,setter ����
}

<����8>
�޼ҵ��� return by refernce
Car& setMethod();

<����9>
class Student{
    string name;
    int age;
    string subject[5];
    int score[5];   

    ������ ����
}
        "ȫ�浿",20,{"����","����",...},{20,30,...}
*/