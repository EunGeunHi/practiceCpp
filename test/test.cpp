#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// �߻� Ŭ���� Item
class Item {
protected:
    string name;
    double price;
    int stockQuantity;

public:
    Item(const string& name, double price, int stock)
        : name(name), price(price), stockQuantity(stock) {
    }

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
        cout << name << " - W" << price << " ���: " << stockQuantity;
    }
};

class Electronics : public Item {
    int madeYear;
public:
    Electronics(const string& name, double price, int stock, int year)
        : Item(name, price, stock), madeYear(year) {
    }

    void show() const override {
        cout << "������ǰ: ";
        Item::show();
        cout << " �����⵵: " << madeYear << endl;
    }
};

class Clothing : public Item {
    int size;
public:
    Clothing(const string& name, double price, int stock, int size)
        : Item(name, price, stock), size(size) {
    }

    void show() const override {
        cout << "�Ƿ��Ѽ�: ";
        Item::show();
        cout << " ġ��: " << size << endl;
    }
};

// Discountable �������̽�
class Discountable {
public:
    virtual double getDiscountedPrice(double price) const = 0;
    virtual ~Discountable() {}
};

class SeasonalDiscount : public Discountable {
    double discountRate;
public:
    SeasonalDiscount(double rate = 0.05) : discountRate(rate) {}
    double getDiscountedPrice(double price) const override {
        return price * discountRate;
    }
};

// �߻� Ŭ���� Customer
class Customer {
protected:
    string name;
public:
    Customer(const string& name) : name(name) {}
    virtual ~Customer() {}

    string getName() const { return name; }
    virtual double applyDiscount(double price) const = 0;
};

class RegularCustomer : public Customer {
public:
    RegularCustomer(const string& name) : Customer(name) {}
    double applyDiscount(double price) const override {
        return price * 0.03;
    }
};

class PremiumCustomer : public Customer {
public:
    PremiumCustomer(const string& name) : Customer(name) {}
    double applyDiscount(double price) const override {
        return price * 0.10;
    }
};

class Order : public SeasonalDiscount {
    static const int N = 20;
    Customer* customer;
    Item* items[N]{};
    int quantities[N]{};
    string orderDates[N]{};
    int count = 0;

public:
    Order(Customer* customer) : customer(customer) {}

    void addItem(Item* item, int quantity, const string& date) {
        if (count < N) {
            items[count] = item;
            quantities[count] = quantity;
            orderDates[count] = date;
            item->reduceStock(quantity);
            ++count;
        }
    }

    double calculateTotal() const {
        double total = 0;
        for (int i = 0; i < count; ++i) {
            total += items[i]->getPrice() * quantities[i];
        }
        return total;
    }

    void printOrderSummary() const {
        cout << "\n=== �� �ֹ� ��� ===\n";
        cout << "��: " << customer->getName() << endl;
        cout << "�ֹ����:\n";
        for (int i = 0; i < count; ++i) {
            cout << "- " << items[i]->getName() << " x " << quantities[i] << "��: �ܰ� W" << items[i]->getPrice() << endl;
        }
        cout << "���� ������ �Ѻ��: W" << calculateTotal() << endl;
    }

    void printDiscountDetails() const {
        cout << "\n���� ����:\n";
        double total = 0;
        for (int i = 0; i < count; ++i) {
            double original = items[i]->getPrice();
            double season = getDiscountedPrice(original);
            double cust = customer->applyDiscount(original);
            double finalPrice = original - season - cust;
            total += finalPrice * quantities[i];
            cout << fixed << setprecision(2);
            cout << "- " << items[i]->getName() << ": ���� ���� W" << original
                << ", �������� W" << season
                << ", ������ W" << cust
                << ", ���� �� W" << finalPrice << endl;
        }
        cout << "���ε� ���� �ݾ� = W" << total << endl;
    }
};

void showItemsStock(Item* items[], int size) {
    for (int i = 0; i < size; ++i) {
        items[i]->show();
    }
}

int main() {
    Item* items[4] = {
        new Electronics("��Ʈ��", 1500, 100, 2023),
        new Clothing("Ƽ����", 50, 100, 95),
        new Electronics("�޴���", 800, 100, 2024),
        new Clothing("û����", 80, 100, 90)
    };

    showItemsStock(items, 4);

    RegularCustomer rc("ȫ�浿");
    PremiumCustomer pc("������");

    Order rOrder(&rc);
    rOrder.addItem(items[0], 1, "240901");
    rOrder.addItem(items[1], 2, "240902");
    rOrder.printOrderSummary();
    rOrder.printDiscountDetails();

    Order pOrder(&pc);
    pOrder.addItem(items[1], 1, "240901");
    pOrder.addItem(items[3], 2, "240903");
    pOrder.printOrderSummary();
    pOrder.printDiscountDetails();

    showItemsStock(items, 4);

    for (auto& item : items) delete item;
    return 0;
}
