#include <iostream>
#include <string>
using namespace std;

class Animal {
protected:  //subclass는 접근 가능 나머진 불가
    double weight;
    string color;

public:
    Animal(double w, const string& c) : weight(w), color(c) {}
    virtual void show() const = 0; // 순수 가상 함수로 변경
    virtual ~Animal() {}
};

//class A: private Animal{} //animal의 protected가private, public이 private

// Cow 클래스는 Animal을 private 상속
//외부 코드가 upcasting을 할 수 없다
class Cow : protected Animal {  //animal의 protected가protected, public이 protected  :: 외부코드가 
private:
    int id;
    string owner;
    int age;

public:
    Cow(double w, const string& c, int i, const string& o, int a)
        : Animal(w, c), id(i), owner(o), age(a) {}

    void show() const override {
        cout << "Cow details:\n";
        cout << "Weight: " << weight << " kg\n";
        cout << "Color: " << color << endl;
        cout << "ID: " << id << endl;
        cout << "Owner: " << owner << endl;
        cout << "Age: " << age << " years\n";
    }

    Animal* getAnimal() { return this; } // Animal 포인터 노출
};

// MilkCow 클래스는 Cow을 private 상속
//private 상속은 "is-a" 관계를 외부뿐 아니라 내부에서도 제한
//class MilkCow : private Cow {
class MilkCow : protected Cow {
private:
    int milkProduct;

public:
    MilkCow(double w, const string& c, int i, const string& o, int a, int m)
        : Cow(w, c, i, o, a), milkProduct(m) {}

    void show() const override {
        Cow::show();
        cout << "Milk Production: " << milkProduct << " liters/day\n";
    }

    //Animal* getAnimal() { return this; }//클래스 내에서는 upcasting 허용
    Animal* getAnimal() { return static_cast<Animal*>(this); }

};

// Dog 클래스는 Animal을 private 상속
//외부 코드가 upcasting을 할 수 없다 //메인함수 주석부분
class Dog : private Animal {
private:
    int id;
    string owner;
    int age;

public:
    Dog(double w, const string& c, int i, const string& o, int a)
        : Animal(w, c), id(i), owner(o), age(a) {}

    void show() const override {
        cout << "Dog details:\n";
        cout << "Weight: " << weight << " kg\n";
        cout << "Color: " << color << endl;
        cout << "ID: " << id << endl;
        cout << "Owner: " << owner << endl;
        cout << "Age: " << age << " years\n";
    }

    Animal* getAnimal() { return this; }
};

// printByReference
void printByReference(const Animal& a) {
    cout << "\n[POLYMORPHIC VERSION: Passed by Reference]\n";
    a.show();
}

// showAll
void showAll(Animal* animals[], int size) {
    for (int i = 0; i < size; ++i) {
        animals[i]->show();
        cout << endl;
    }
}

int main() {
    const int numAnimals = 10;
    Animal* animals[numAnimals];

    // 생성하고 getAnimal()로 포인터 획득
    Cow* c1 = new Cow(500, "Brown", 101, "John Doe", 5);
    Cow* c2 = new Cow(520, "Black", 102, "Alice Smith", 4);
    Cow* c3 = new Cow(480, "White", 103, "Bob Johnson", 6);

    MilkCow* mc1 = new MilkCow(530, "Brown", 104, "Charlie Rose", 3, 20);
    MilkCow* mc2 = new MilkCow(510, "Spotted", 105, "Diana Ross", 5, 25);
    MilkCow* mc3 = new MilkCow(495, "White", 106, "Emily Clark", 4, 22);

    Dog* d1 = new Dog(30, "Black", 201, "Jane Smith", 3);
    Dog* d2 = new Dog(28, "Brown", 202, "Emily Davis", 2);
    Dog* d3 = new Dog(35, "White", 203, "Frank White", 4);
    Dog* d4 = new Dog(32, "Gray", 204, "Grace Lee", 5);

    animals[0] = c1->getAnimal();
    animals[1] = c2->getAnimal();
    animals[2] = c3->getAnimal();
    animals[3] = mc1->getAnimal();
    animals[4] = mc2->getAnimal();
    animals[5] = mc3->getAnimal();
    animals[6] = d1->getAnimal();
    animals[7] = d2->getAnimal();
    animals[8] = d3->getAnimal();
    animals[9] = d4->getAnimal();
    /*
    Cow c(...);
    Animal* a = &c;  // ❌ 오류! private 상속이므로 외부에서 업캐스팅 금지
    Animal* a = c1; //업케스팅 오류! public이면 가능==> private 상속은 상속관계를 숨긴다는것
    */
    cout << "\n▶▶ 모든 Animal 출력 (정상 polymorphism)\n";
    showAll(animals, numAnimals);

    cout << "\n▶▶ 개별 객체 전달 실험\n";
    printByReference(*animals[3]);
    printByReference(*animals[6]);

    // 메모리 해제
    delete c1; delete c2; delete c3;
    delete mc1; delete mc2; delete mc3;
    delete d1; delete d2; delete d3; delete d4;

    return 0;
}
