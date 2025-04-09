// student *table[];array of pointer 초기화
#include <iostream>
#include <cstring>  //strcpy


using namespace std;
class Car {
private:
    char* manufacturer;
    char model[10];
    int speed;
    string owner;

    static int destruct_cnt;
public:

    Car();                  //기본 생성자
    Car(const char* manufacturer, const char* model, int speed, string owner);    //일반 생성자 
    Car(const Car& other);  //복사 생성자(깊은 복사)
    ~Car();                 //소멸자

    Car& setManufacturer(const char* manufacturer);
    Car& setModel(const char* manufacturer);
    Car& setSpeed(int speed);
    Car& setOwner(const string& owner);

    void display();
    static int getterDestruct_cnt();
};

int Car::destruct_cnt = 0;
int main() {
    const int SIZE = 3;

    Car* table = new Car[SIZE];    // 기본 생성자 3번 호출됨

    table[0].setManufacturer("BMW").setModel("320i").setSpeed(160).setOwner("David");
    table[1].setManufacturer("Audi").setModel("A4").setSpeed(170).setOwner("Eve");
    table[2].setManufacturer("Mercedes").setModel("C200").setSpeed(180).setOwner("Frank");
    for (int i = 0; i < SIZE; ++i) table[i].display();

    Car* table2[SIZE];
    table2[0] = new Car("Hyundai", "Avante", 120, "Alice");
    table2[1] = new Car("Kia", "K5", 130, "Bob");
    table2[2] = new Car(table[2]);  //복사 생성자
    for (int i = 0; i < SIZE; ++i) table2[i]->display();

    cout << "____________________________________\n";
    cout << "for (int i = 0; i < SIZE; ++i) delete table2[i]" << endl;
    for (int i = 0; i < SIZE; ++i) delete table2[i];
    cout << "getterDestruct_cnt(): " << Car::getterDestruct_cnt() << endl;
    cout << endl;

    cout << "table2[2]->display()" << endl;
    table[2].display();
    cout << endl;

    cout << "delete[] table;" << endl;
    delete[] table;
    cout << "getterDestruct_cnt(): " << Car::getterDestruct_cnt() << endl;


    return 0;
}


//__________________________________________________________________//

Car::Car()
    :manufacturer(nullptr), speed(0), owner("Unknown") {
    strcpy(model, "Unknown");
}
// Car::Car(){
//     manufacturer = nullptr;
//     strcpy(model,"Unknown");
//     speed = 0;
// }
Car::Car(const char* manufacturer, const char* model, int speed, string owner) {
    this->manufacturer = new char[strlen(manufacturer) + 1];
    strcpy(this->manufacturer, manufacturer);

    strncpy(this->model, model, sizeof(this->model)); //sizeof(model)하면 포인터 크기..
    this->model[sizeof(this->model) - 1] = '\0';

    this->speed = speed;
    this->owner = owner;
}
Car::Car(const Car& other) {
    if (other.manufacturer != nullptr) {
        manufacturer = new char[strlen(other.manufacturer) + 1];
        strcpy(manufacturer, other.manufacturer);
    }
    else {
        manufacturer = nullptr;
    }
    strcpy(model, other.model);
    speed = other.speed;
    this->owner = other.owner;
}
Car::~Car() {
    delete[] manufacturer;
    ++destruct_cnt;
}
Car& Car::setManufacturer(const char* manufacturer) {
    if (this->manufacturer != nullptr) delete[] this->manufacturer;
    this->manufacturer = new char[strlen(manufacturer) + 1];
    strcpy(this->manufacturer, manufacturer);
    return *this;
}
Car& Car::setModel(const char* model) {
    strcpy(this->model, model);
    return *this;
}
Car& Car::setSpeed(int speed) {
    this->speed = speed;
    return *this;
}
Car& Car::setOwner(const string& owner) {
    this->owner = owner;
    return *this;
}
void Car::display() {
    cout << (manufacturer ? manufacturer : "nullptr") << ", " << model << ", " << owner << ", " << speed << "km/h\n";
}
int Car::getterDestruct_cnt() {
    return  destruct_cnt;
}