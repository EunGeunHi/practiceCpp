#include "ObjectTable.h"

class Dummy {
    int value;
public:
    Dummy(int v) : value(v) {}
    void show() const {
        cout << "Value: " << value << endl;
    }
    bool operator>(const Dummy& other) const {
        return value > other.value;
    }
    bool operator==(const Dummy& other) const {
        return value == other.value;
    }
};

int main() {
    ObjectTable<Dummy> table;
    table.add(new Dummy(3));
    table.add(new Dummy(1));
    table.add(new Dummy(2));

    cout << "Before sort:\n";
    table.showAll();

    table.sort();

    cout << "After sort:\n";
    table.showAll();

    return 0;
}
