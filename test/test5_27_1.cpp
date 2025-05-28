#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
#include <algorithm>

/*
클래스 구현
    1.Book: 제목,저자,출판사
    2.Bag: 모델명,크기,색상
    3.EBook:Book상속 + 저장매체,용량
    4.RegularCustomer: 도시, 마일리지, 할인율 3%
    5.VIPCustomer: 할인율 필드 사용
    6.OrderTable: 최대 20개 Order객체 저장
        메소드
        1.void add(Order* o)
        2.void printAll()
        3.Order* search(string name)
        4.int remove(string name)
        5.void sort()
main() 함수에 enum 메뉴로 입출력 구현



oreder는 has-a (Item,Customer)
Itme은 is-a (Book,Bag,EBook)
Customer는 is-a (RegularCustomer, VIPCustomer)
*/


// [제공 코드 시작] - 수정 금지
class Item {
protected:
    string name;
    double price;
    int stockQuantity;

public:
    Item(const string& name, double price, int stock)
        : name(name), price(price), stockQuantity(stock) {}

    virtual ~Item() {}

    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStockQuantity() const { return stockQuantity; }

    void reduceStock(int quantity) {
        if (stockQuantity >= quantity)
            stockQuantity -= quantity;
        else
            cout << "Insufficient stock for " << name << endl;
    }

    virtual void show() const {
        cout << name << " - W" << price << " 재고량: " << stockQuantity;
    }
};

class Customer {
protected:
    string name;

public:
    Customer(const string& name) : name(name) {}
    virtual ~Customer() {}

    string getName() const { return name; }
    virtual double applyDiscount(double price) const = 0;
};

class Order {
    static const int N = 20;
    Customer* customer;
    Item* items[N]{};
    int quantities[N]{};
    int count = 0;

public:
    Order(Customer* customer) : customer(customer) {}

    string getCustomerName() const {
        return customer->getName();
    }

    void addItem(Item* item, int quantity) {
        if (count < N) {
            items[count] = item;
            quantities[count] = quantity;
            item->reduceStock(quantity);
            ++count;
        }
    }

    void printOrderSummary() const {
        cout << "\n=== 주문 요약 ===\n";
        cout << "고객: " << customer->getName() << endl;
        double total = 0;
        for (int i = 0; i < count; ++i) {
            double basePrice = items[i]->getPrice();
            double discount = customer->applyDiscount(basePrice);
            double finalPrice = basePrice - discount;
            total += finalPrice * quantities[i];

            cout << fixed << setprecision(2);
            cout << "- " << items[i]->getName() << " x " << quantities[i]
                 << "개: 원가 W" << basePrice
                 << ", 할인 W" << discount
                 << ", 최종 W" << finalPrice << endl;
        }
        cout << "총 지불 금액: W" << total << endl;
    }

    bool matchCustomer(string target) const {
        return customer->getName() == target;
    }

    bool operator>(const Order& other) const {
        return customer->getName() > other.customer->getName();
    }
};

// 1. Book 클래스 구현
class Book : public Item {
protected:
    string author;
    string publisher;

public:
    Book(const string& name, const string& author, const string& publisher, double price, int stock)
        : Item(name, price, stock), author(author), publisher(publisher) {
    }

    void show() const override {
        Item::show();
        cout << ", 저자: " << author << ", 출판사: " << publisher;
    }
};

// 2. Bag 클래스 구현
class Bag : public Item {
protected:
    string size;
    string color;

public:
    Bag(const string& name, const string& size, const string& color, double price, int stock)
        : Item(name, price, stock), size(size), color(color) {
    }

    void show() const override {
        Item::show();
        cout << ", 크기: " << size << ", 색상: " << color;
    }
};

// 3. EBook 클래스 구현
class EBook : public Book {
protected:
    string storageMedium;
    string capacity;

public:
    EBook(const string& name, const string& storageMedium, const string& capacity,
        const string& author, const string& publisher, double price, int stock)
        : Book(name, author, publisher, price, stock), storageMedium(storageMedium), capacity(capacity) {
    }

    void show() const override {
        Book::show();
        cout << ", 저장매체: " << storageMedium << ", 용량: " << capacity;
    }
};

// 4. RegularCustomer 클래스 구현
class RegularCustomer : public Customer {
protected:
    string city;
    int mileage;
    const double DISCOUNT_RATE = 0.03; // 3% 할인율

public:
    RegularCustomer(const string& name, const string& city, int mileage)
        : Customer(name), city(city), mileage(mileage) {
    }

    double applyDiscount(double price) const override {
        return price * DISCOUNT_RATE;
    }
};

// 5. VIPCustomer 클래스 구현
class VIPCustomer : public Customer {
protected:
    double discountRate; // 할인율 필드 사용

public:
    VIPCustomer(const string& name, double discountRate)
        : Customer(name), discountRate(discountRate) {
    }

    double applyDiscount(double price) const override {
        return price * discountRate;
    }
};

// 6. OrderTable 클래스 구현
class OrderTable {
    static const int MAX_ORDERS = 20;
    Order* orders[MAX_ORDERS]{};
    int count = 0;

public:
    void add(Order* o) {
        if (count < MAX_ORDERS) {
            orders[count] = o;
            ++count;
        }
        else {
            cout << "주문 테이블이 가득 찼습니다. 더 이상 추가할 수 없습니다.\n";
        }
    }

    void printAll() const {
        if (count == 0) {
            cout << "주문 내역이 없습니다.\n";
            return;
        }
        for (int i = 0; i < count; ++i) {
            orders[i]->printOrderSummary();
        }
    }

    Order* search(string name) const {
        for (int i = 0; i < count; ++i) {
            if (orders[i]->matchCustomer(name)) {
                return orders[i];
            }
        }
        return nullptr;
    }

    int remove(string name) {
        int removedCount = 0;
        // 삭제된 요소를 채우기 위해 왼쪽으로 요소들을 이동시킵니다.
        for (int i = 0; i < count; ) {
            if (orders[i]->matchCustomer(name)) {
                // 관련 고객 객체 삭제
                // Order 객체가 Customer 객체를 독점적으로 소유하고 있다고 가정합니다.
                // 만약 Customer 객체가 여러 Order에 의해 공유될 수 있다면,
                // 여기서는 Customer를 삭제해서는 안 됩니다.
                //delete orders[i]->customer; // 고객 객체 삭제
                // Order 객체 자체 삭제
                delete orders[i];
                for (int j = i; j < count - 1; ++j) {
                    orders[j] = orders[j + 1];
                }
                orders[count - 1] = nullptr; // 마지막 포인터 초기화
                --count;
                ++removedCount;
            }
            else {
                ++i;
            }
        }
        return removedCount;
    }

    void sort() {
        // 고객 이름으로 정렬합니다. std::sort를 사용하여 효율적으로 구현합니다.
        std::sort(orders, orders + count, [](Order* a, Order* b) {
            return a->getCustomerName() < b->getCustomerName();
            });
    }

    // 동적으로 할당된 Order 객체를 정리하기 위한 소멸자
    ~OrderTable() {
        for (int i = 0; i < count; ++i) {
            // Order 객체를 삭제합니다.
            // 참고: Customer와 Item은 OrderTable 외부에서 생성되므로,
            // Order가 독점적으로 소유하지 않는다면 main에서 삭제 책임을 집니다.
            // 현재 remove 함수는 Order 삭제 시 Customer도 삭제합니다.
            delete orders[i];
        }
    }
};




enum Menu { INPUT = 1, PRINT, SEARCH, DELETE, SORT, EXIT };

int main() {
    OrderTable table;
    Item* items[] = {
        new Book("자바의정석", "남궁성", "도우출판", 30000, 50),
        new EBook("알고리즘", "PDF", "2GB", "홍길동", "한빛", 25000, 100),
        new Bag("에코백", "Large", "화이트", 12000, 80)
    };
    Customer* rc = new RegularCustomer("홍길동", "서울", 1000);
    Customer* vip = new VIPCustomer("이순신", 0.1);

    Order* order1 = new Order(rc);
    order1->addItem(items[0], 1);
    order1->addItem(items[2], 2);

    Order* order2 = new Order(vip);
    order2->addItem(items[1], 1);

    int select;
    while (true) {
        cout << "\n1. 객체 입력, 2. 전체 출력, 3. 검색, 4. 삭제, 5. 정렬, 6. 종료: ";
        cin >> select;

        switch (static_cast<Menu>(select)) {
        case INPUT:
            table.add(order1);
            table.add(order2);
            cout << "주문 입력 완료.\n";
            break;

        case PRINT:
            table.printAll();
            break;

        case SEARCH: {
            string name;
            cout << "검색할 고객명: ";
            cin >> name;
            Order* found = table.search(name);
            if (found) found->printOrderSummary();
            else cout << name << " 을(를) 찾을 수 없습니다.\n";
            break;
        }

        case DELETE: {
            string name;
            cout << "삭제할 고객명: ";
            cin >> name;
            int count = table.remove(name);
            cout << "삭제된 주문 수: " << count << "\n";
            break;
        }

        case SORT:
            table.sort();
            cout << "정렬 완료.\n";
            break;

        case EXIT:
            return 0;
        }
    }
}

// [제공 코드 끝]
