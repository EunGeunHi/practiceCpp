
const int MAX = 100;
// ===========================
// Person 계층 구조
// ===========================
class Person {
private:
    string pid;
    string name;
    string city;
public:
    Person(string pid, string name, string city);
    virtual void show() const;
    virtual string getName() const;
    virtual string getPid() const;
    virtual bool operator>(const Person& other) const;
    virtual bool operator==(const Person& other) const;
    virtual ~Person();
};

class Student : public Person {
private:
    string sid;
    string dept;
public:
    Student(string pid, string name, string city, string sid, string dept);
    void show() const override;
    bool operator>(const Person& other) const override;
    bool operator==(const Person& other) const override;
};

class Employee : public Person {
private:
    string eno;
    string company;
    string role;
public:
    Employee(string pid, string name, string city, string eno, string company, string role);
    void show() const override;
    bool operator>(const Person& other) const override;
    bool operator==(const Person& other) const override;
};