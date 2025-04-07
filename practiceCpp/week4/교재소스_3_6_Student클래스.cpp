#include <iostream>
#include <string.h>

class Student {
private:
	char* name;
	int age;
	char* city;

public:
	Student(char* name, int age, char* city) {
		this->name = strdup(name);
		this->age = age;
		this->city = strdup(city);
	}

	~Student() {
		free(name);
		free(city);
	}
	void show() {
		std::cout << "Name: " << name << ", Age: " << age << ", City: " << city << std::endl;
	}
};

int main() {
	Student sset2[5] = {
			{"John", 20, "New York"},
			{"Alice", 22, "Los Angeles"},
			{"Bob", 21, "Chicago"},
			{"Emily", 19, "San Francisco"},
			{"Michael", 23, "Seattle"}
	};
	/*
	Student sset2[5] = {
	Student("John", 20, "New York"),
	Student("Alice", 22, "Los Angeles"),
	Student("Bob", 21, "Chicago"),
	Student("Emily", 19, "San Francisco"),
	Student("Michael", 23, "Seattle")
};
	
	*/
	for (int i = 0; i < 5; ++i)
		sset2[i].show();

}