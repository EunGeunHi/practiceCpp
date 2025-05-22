#include <iostream>
#include <string>
using namespace std;

// 추상 클래스 Animal
class Animal {
protected:
    double weight;
    string color;

public:
    Animal(double w, const string& c) : weight(w), color(c) {}

    // 가상 함수
    virtual void show()const {}

    // 가상 소멸자
    virtual ~Animal() {}
};

// Cow 클래스는 Animal을 상속
class Cow : public Animal {
private:
    int id;
    string owner;
    int age;

public:
    Cow(double w, const string& c, int i, const string& o, int a)
        : Animal(w, c), id(i), owner(o), age(a) {}

    void show()const override{
        cout << "Cow details:\n";
        cout << "Weight: " << weight << " kg\n";
        cout << "Color: " << color << endl;
        cout << "ID: " << id << endl;
        cout << "Owner: " << owner << endl;
        cout << "Age: " << age << " years\n";
    }
};

// MilkCow 클래스는 Cow을 상속
class MilkCow : public Cow {
private:
    int milkProduct;

public:
    MilkCow(double w, const string& c, int i, const string& o, int a, int m)
        : Cow(w, c, i, o, a), milkProduct(m) {}

    void show(){
        Cow::show();    //코드 재사용
        cout << "Milk Production: " << milkProduct << " liters/day\n";
    }
};

// Dog 클래스는 Animal을 상속
class Dog : public Animal {
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
};

// slicing 발생 (subclass 정보 잘림)
void printByValue(Animal a) {       //값 복사로 전달, milkcow, cow부분 짤리면서 animal부분만 
    cout << "\n[SLICED VERSION: Passed by Value]\n";
    a.show();  // always calls Animal's base version (if not abstract)
}

// slicing 방지 (정상 polymorphism)
void printByReference(const Animal& a) {    //참조로 전달하면 객체 복사 없이 객체를 가르킴->파생클래스 정보 유지&슬라이싱 방지
    cout << "\n[POLYMORPHIC VERSION: Passed by Reference]\n";
    a.show();  // virtual dispatch works correctly
}

// Animal 배열 출력
void showAll(Animal* animals[], int size) {
    for (int i = 0; i < size; ++i) {
        animals[i]->show(); //동적바인딩 //동적바인딩은 포인터: ->show() 으로!  .show()하면 동적바인딩 안됨
        cout << endl;
    }
}

int main() {
    const int numAnimals = 10;
    Animal* animals[numAnimals];

    // 동적 객체 생성
    animals[0] = new Cow(500, "Brown", 101, "John Doe", 5);
    animals[1] = new Cow(520, "Black", 102, "Alice Smith", 4);
    animals[2] = new Cow(480, "White", 103, "Bob Johnson", 6);

    animals[3] = new MilkCow(530, "Brown", 104, "Charlie Rose", 3, 20);
    animals[4] = new MilkCow(510, "Spotted", 105, "Diana Ross", 5, 25);
    animals[5] = new MilkCow(495, "White", 106, "Emily Clark", 4, 22);

    animals[6] = new Dog(30, "Black", 201, "Jane Smith", 3);
    animals[7] = new Dog(28, "Brown", 202, "Emily Davis", 2);
    animals[8] = new Dog(35, "White", 203, "Frank White", 4);
    animals[9] = new Dog(32, "Gray", 204, "Grace Lee", 5);

    cout << "\n▶▶ 모든 Animal 출력 (정상 polymorphism)\n";
    showAll(animals, numAnimals);

    cout << "\n▶▶ 개별 객체 전달 실험\n";

    // slicing 발생
    printByValue(*animals[3]);      // MilkCow → Animal by value → slicing 발생
    printByValue(*animals[6]);      // Dog → Animal by value → slicing 발생

    // slicing 방지
    printByReference(*animals[3]);  // MilkCow → Animal& → polymorphism 유지
    printByReference(*animals[6]);  // Dog → Animal& → polymorphism 유지

    // 메모리 해제
    for (int i = 0; i < numAnimals; ++i) {
        delete animals[i];
    }

    return 0;
}
