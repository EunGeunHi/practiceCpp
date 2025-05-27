#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

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
