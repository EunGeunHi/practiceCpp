#include <iostream>
#include <string>

using namespace std;

class Beverage {
protected:
	string name;
	int price;
public:
	Beverage(const string& name, int price): name(name), price(price) {}
	virtual ~Beverage() {}
	virtual void show() const = 0;
	const string& getName() const { return name; }
	int getPrice() { return price; }
	void setPrice(int price) { this->price = price; }
};

class MilkBase : virtual public Beverage {//todo
protected:
  string milkType;
	bool isFoamed;
public:
    MilkBase(const string& name, int price, const string& milkType, bool isFoamed)
			:Beverage(name,price), milkType(milkType), isFoamed(isFoamed) {}
};

class Coffee : virtual public Beverage {//todo
protected:
    string beanOrigin;
public:
    Coffee(const string& name, int price, const string& beanOrigin)
			:Beverage(name,price),beanOrigin(beanOrigin) {}
    void show() const override{
			cout<< "커피: "<<name << " ("<< beanOrigin <<") - "<<price<<"원"<<endl;
		}
};

class Tea : virtual public Beverage {//todo
protected:
    string teaType;
public:
    Tea(const string& name, int price, const string&teaType)
			:Beverage(name,price),teaType(teaType) {}
    void show()const override{
			cout<< "차: "<<name << " ("<< teaType <<") - "<<price<<"원"<<endl;
		}
};

class Latte : public MilkBase, public Coffee {//todo
public:
    Latte(const string& name, int price, const string& beanOrigin, const string& milkType, bool isFoamed)
			:Beverage(name,price),MilkBase(name,price,milkType,isFoamed),Coffee(name,price,beanOrigin) {}
    void show()const override{
			cout<< "라떼: "<<name << " ("<< beanOrigin <<" + "<<milkType <<") - "<<price<<"원 [";
			cout<< (isFoamed ? "폼 있음]" : "폼 없음]") << endl; 
		}
};

class MilkTea : public MilkBase, public Tea {//todo
public:
    MilkTea(const string& name, int price,const string& teaType, const string& milkType, bool isFoamed)
			:Beverage(name,price), MilkBase(name,price,milkType,isFoamed),Tea(name,price,teaType) {}
    void show()const override{
			cout<< "밀크티: "<<name << " ("<< teaType <<" + "<< milkType <<") - "<<price<<"원 [";
			cout<< (isFoamed ? "폼 있음]" : "폼 없음]") << endl; 
		}
};


void printByReference(const Beverage& b) { //todo
	b.show();
}

class BeverageStocks {
private:
	static const int N = 10;
	Beverage* beverages[N];
	int count = 0;
public:
	BeverageStocks() {};
	~BeverageStocks() {
		for (int i = 0; i < count; ++i) delete beverages[i];
	}
	void add(Beverage* beverages[], int size) {//todo
		for (int i=0; i<size; i++){
			this->beverages[i] = beverages[i];
			count++;
		}
		cout<<"[음료 추가 완료]"<<endl;
	}
	void delBeverage(const string& name) {//todo
		for (int i=0; i<count; i++){
			if (beverages[i]->getName() == name){
				delete beverages[i];
				for(int j=i; j<count; j++){
					beverages[j] = beverages[j+1];
				}
				count--;
				cout<< "[ 삭제된 음료: "<<name <<"]"<<endl;
			}
		}	
	}

	void update(const string& name, int price) {//todo
		for (int i=0; i<count; i++){
			if (beverages[i]->getName() == name){
				int temp = beverages[i]->getPrice();
				beverages[i]->setPrice(price);
				cout<< "[음료 가격 변경 : "<<name<<" "<<temp <<" -> "<<price<<"원]"<<endl;
			}
		}
	}

	void search(const string& name) {//todo
		//printByReference() 사용하여 출력
		for (int i=0; i<count; i++){
			if (beverages[i]->getName() == name){
				printByReference(*beverages[i]);
			}
		}
	}

	void showAll() {//todo
		for (int i=0; i<count; i++){
			printByReference(*beverages[i]);
		}
	}
		
};

enum Menu { ADD = 1, DELETE, UPDATE, SEARCH, PRINTALL, EXIT};

int main() {
	const int numBeverages = 7;
	Beverage* beverages[numBeverages];
	BeverageStocks stock;

	beverages[0] = new Coffee("아메리카노", 3000, "에티오피아 예가체프");
	beverages[1] = new Coffee("콜드브루", 4900, "에티오피아 블렌드");
	beverages[2] = new Tea("얼그레이티", 3800, "얼그레이");
	beverages[3] = new Tea("우롱티", 3500, "우롱");
	beverages[4] = new Latte("카페모카", 5000, "과테말라 안티구아","초코 우유", true);
	beverages[5] = new Latte("카페라떼", 4800, "에티오피아 예가체프", "우유", true);
	beverages[6] = new MilkTea("우롱밀크티", 6000, "우롱", "우유", true);

	int selection;
    while (true) {
		cout << "----------------------------------" << endl << "메뉴 입력: ";
		cin >> selection;
		cout << "----------------------------------" << endl;
		string name;
		switch (static_cast<Menu>(selection)) {
			case ADD:
				stock.add(beverages, numBeverages);
				break;
			case DELETE:
				cout << "삭제할 음료 이름을 입력하세요: ";
				cin >> name;
				stock.delBeverage(name);
				break;
			case UPDATE:
				int price;
				cout << "변경할 음료 이름을 입력하세요: ";
				cin >> name;
				cout << "변경할 가격을 입력하세요: ";
				cin >> price;
				stock.update(name, price);
				break;
			case SEARCH:
				cout << "검색할 음료 이름을 입력하세요: ";
				cin >> name;
				stock.search(name);
				break;
			case PRINTALL:
				cout << "[모든 음료 리스트]" << endl;
				stock.showAll();
				break;
			case EXIT:
				cout << "[프로그램종료]";
				return 0;
		}
	}


	return 0;
}