#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

// ====================================
// 템플릿 객체 테이블 클래스 정의
// ====================================
template <typename T>
class ObjectTable {
private:
    T* data[MAX];
    int size;

public:
    ObjectTable() : size(0) {
        for (int i = 0; i < MAX; i++)
            data[i] = nullptr;
    }

    ~ObjectTable() {
        for (int i = 0; i < size; i++)
            delete data[i];
    }

    void add(T* obj) {
        if (size < MAX)
            data[size++] = obj;
        else
            cout << "📛 테이블 용량 초과\n";
    }

    void remove(int index) {
        if (index >= 0 && index < size) {
            delete data[index];
            for (int i = index; i < size - 1; i++)
                data[i] = data[i + 1];
            data[--size] = nullptr;
        }
    }

    void update(int index, T* obj) {
        if (index >= 0 && index < size) {
            delete data[index];
            data[index] = obj;
        }
    }

    int search(T* target) {
        for (int i = 0; i < size; i++)
            if (*data[i] == *target)
                return i;
        return -1;
    }

    void sort() {
        for (int i = 0; i < size - 1; i++)
            for (int j = i + 1; j < size; j++)
                if (*data[i] > *data[j])
                    swap(data[i], data[j]);
    }

    void showAll() const {
        for (int i = 0; i < size; i++)
            data[i]->show();
    }
};

// ====================================
// Vehicle 클래스 계층
// ====================================
class Vehicle {
protected:
    string model;
public:
    Vehicle(string m) : model(m) {}
    virtual void show() const {
        cout << "🚗 Vehicle: " << model << endl;
    }
    virtual string getModel() const { return model; }
    virtual bool operator>(const Vehicle& other) const {
        return model > other.model;
    }
    virtual bool operator==(const Vehicle& other) const {
        return model == other.model;
    }
    virtual ~Vehicle() {}
};

class Car : public Vehicle {
    int year;
public:
    Car(string m, int y) : Vehicle(m), year(y) {}
    void show() const override {
        cout << "🚘 Car: " << model << ", Year: " << year << endl;
    }
    bool operator>(const Vehicle& other) const override {
        if (model == other.getModel()) {
            const Car* pCar = dynamic_cast<const Car*>(&other); //const Car* pCar = other;과 차이
            return pCar ? year > pCar->year : false;
        }
        return model > other.getModel();
    }
    bool operator==(const Vehicle& other) const override {
        if (model != other.getModel()) return false;
        const Car* pCar = dynamic_cast<const Car*>(&other);
        return pCar && year == pCar->year;
    }
};

class Truck : public Vehicle {
    int capacity;
public:
    Truck(string m, int c) : Vehicle(m), capacity(c) {}
    void show() const override {
        cout << "🚚 Truck: " << model << ", Capacity: " << capacity << " ton" << endl;
    }
    bool operator>(const Vehicle& other) const override {
        if (model == other.getModel()) {
            const Truck* pTruck = dynamic_cast<const Truck*>(&other);
            return pTruck ? capacity > pTruck->capacity : false;
        }
        return model > other.getModel();
    }
    bool operator==(const Vehicle& other) const override {
        if (model != other.getModel()) return false;
        const Truck* pTruck = dynamic_cast<const Truck*>(&other);
        return pTruck && capacity == pTruck->capacity;
    }
};

// ====================================
// Animal 클래스 계층
// ====================================
class Animal {
protected:
    string name;
public:
    Animal(string n) : name(n) {}
    virtual void show() const {
        cout << "🐾 Animal: " << name << endl;
    }
    virtual string getName() const { return name; }
    virtual bool operator>(const Animal& other) const {
        return name > other.name;
    }
    virtual bool operator==(const Animal& other) const {
        return name == other.name;
    }
    virtual ~Animal() {}
};

class Dog : public Animal {
    int age;
public:
    Dog(string n, int a) : Animal(n), age(a) {}
    void show() const override {
        cout << "🐶 Dog: " << name << ", Age: " << age << endl;
        /*
        Animal::show();
        cout<<",Age: "<<age<<endl;
        */
    }
    bool operator>(const Animal& other) const override {
        if (name == other.getName()) {
            const Dog* pDog = dynamic_cast<const Dog*>(&other);
            return pDog ? age < pDog->age : false; // 나이 적은 순 우선
        }
        return name > other.getName();
    }
    bool operator==(const Animal& other) const override {
        if (name != other.getName()) return false;
        const Dog* pDog = dynamic_cast<const Dog*>(&other);
        return pDog && age == pDog->age;
    }
};

class Cow : public Animal {
    double weight;
public:
    Cow(string n, double w) : Animal(n), weight(w) {}
    void show() const override {
        cout << "🐄 Cow: " << name << ", Weight: " << weight << "kg" << endl;
    }
    bool operator>(const Animal& other) const override {
        if (name == other.getName()) {
            const Cow* pCow = dynamic_cast<const Cow*>(&other);
            return pCow ? weight > pCow->weight : false;
        }
        return name > other.getName();
    }
    bool operator==(const Animal& other) const override {
        if (name != other.getName()) return false;
        const Cow* pCow = dynamic_cast<const Cow*>(&other);
        return pCow && weight == pCow->weight;
    }
};

// ====================================
// main 함수
// ====================================
int main() {
    ObjectTable<Vehicle> vTable;
    vTable.add(new Car("Avante", 2020));
    vTable.add(new Truck("Porter", 2));
    vTable.add(new Car("Avante", 2018)); // 같은 이름, 다른 연도
    vTable.add(new Truck("Porter", 3));  // 같은 이름, 다른 용량

    cout << "\n[🚗 Vehicle 목록 (정렬 전)]\n";
    vTable.showAll();

    vTable.sort();
    cout << "\n[🚗 Vehicle 목록 (정렬 후)]\n";
    vTable.showAll();

    ObjectTable<Animal> aTable;
    aTable.add(new Dog("Buddy", 3));
    aTable.add(new Cow("Milky", 250.5));
    aTable.add(new Dog("Buddy", 2));     // 같은 이름, 나이 비교
    aTable.add(new Cow("Milky", 270.2)); // 같은 이름, 무게 비교

    cout << "\n[🐾 Animal 목록 (정렬 전)]\n";
    aTable.showAll();

    aTable.sort();
    cout << "\n[🐾 Animal 목록 (정렬 후)]\n";
    aTable.showAll();

    return 0;
}
