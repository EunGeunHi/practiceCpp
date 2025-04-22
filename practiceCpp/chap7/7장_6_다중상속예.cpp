//7장-16.MULTIPLE.CPP
//다중 상속의 두 가지 예제를 갖고 있는 program

#include <iostream>
using namespace std;
#include <cstring>
#include <string>

//Person을 기술하는 class 정의
class Person{
    string name ;
    string address ;
    int addrdef ;	//이진 값: 정의된 주소
public:
    Person (string n) : name (n){
        addrdef = 0 ;
    }

    Person (string n, string a) :name (n) ,address (a){
        addrdef = 1 ;
    }

    void Address (string a){
        address = a ;
        addrdef = 1 ;
    }

    string Address ( ){
        return address ;
    }

    void Name (string n){
        name = n ;
    }

    string Name ( ){
        return name ;
    }

    virtual void Print ( ){
    cout << "Person::Print() - "<< name << endl ;

    //주소는 정의되었을 때만 인쇄된다.
    if (addrdef)
        cout << address << endl ;
    }
} ;
ostream& operator<<(ostream& s, Person& p) {
    //구현하는 실습
}
//사람의 법률적 데이터를 포함하고 있는 class
class JuriData{
    string juriCode ;    //법률적 code(사회보장번호일 수 있다)
public:
    JuriData (string jc) : juriCode (jc)
    { }

    string JuriCode ( ){
        return juriCode ;
    }
    void JuriCode (string jc){
        juriCode = jc ;
    }

    void Print ( ){
        cout << "JuriData::Print() - Juridical code: " << juriCode << endl ;
    }
} ;

//class Person과 JuriData로부터 유도된 class JuriPerson
//법률적 관점에서 사람을 기술한다.
class JuriPerson : public Person, public JuriData{

public:
    JuriPerson (string n, string jc) : Person (n) ,JuriData (jc)
    { }

    JuriPerson(string n, string a, string jc) : Person (n,a), JuriData (jc)
    { }

    void Print ( ){
        cout<<"JuriPerson::Print() -"<<endl;
        Person :: Print ( ) ;
        JuriData :: Print ( ) ;
    }
} ;

//많아야 20명인 그룹을 정의하는 class

class PeopleSet{
    Person *group [20] ;//객체 집합을 저장 검색 
    int number ;

public:
    PeopleSet () :
    number (0)
    { }

    void AddP (Person * p){
        group [number] = p ;
        number ++ ;
    }

    Person * SelectP (int n){
        return group [n] ;
    }

    int MembersNumber ( ){
        return number ;
    }

    void Print ( ){
        cout<< "PeopleSet::Print() - The group is made of " << number << " members:" << endl ;
        for (int i = 0; i < number; i++){
            //print a sequence number, a delimeter
            //and member's data
            cout << (i+1) << "." << "\t" ;
            group [i] -> Print ( ) ;
        }
    }
} ;

//다중 상속: 한 법률 회사(company)는 법률적인 entity에 
//(또는 사람) 해당되나 또한 그 자신이 법률적인 데이터를 갖고 있는
//사람 그룹 또는 회사들의 그룹이다
class Company : public PeopleSet, public JuriPerson{
    string companyName ;
    Person * leader ;

public:
    Company (string s, string n, string jc) : JuriPerson(n, jc), companyName (s){
        leader = new Person ("undefined") ;
    }
    void CompanyName (string cn){
        companyName = cn ;
    }

    string CompanyName ( ){
        return companyName ;
    }

    Person * Leader ( ){
        return leader ;
    }
  
    void Leader (Person * p){
        leader = p ;
    }

    void Print ( ){
        cout << "Company::Print() - " << companyName << endl << endl;
        JuriPerson :: Print ( );
        PeopleSet :: Print ( );
    }
};
//방금 정의된 class의 사용에 대한 테스트 program
//몇 개의 법인을 갖고 있는 회사 객체를 만든다.
void main(){
    //회사와 주소를 정의한다
    Company a ("PDC", "Penguin Dalambertian Club", "PDCPOLI86");
    a.Address ("by Room B67, Polytechnic of Milan") ;
    //법인들을 회사 객체에 추가한다.
    a.AddP (new JuriPerson ("Marco", "MRCBRT34")) ;
    a.AddP (new JuriPerson ("Luca", "LCANNN74")) ;
    a.AddP (new JuriPerson ("Andrea", "NDRBRR47")) ;
    a.AddP (new JuriPerson ("Giulio", "GLOLPR67")) ;
    a.AddP (new JuriPerson ("Diana", "DNABND84")) ;
    a.AddP (new JuriPerson ("Massimo & Lella", "MSSLLLPCT27"));
	a.AddP (new JuriPerson ("Francesco & Camilla", "FRNCMLRCC28")) ;
    a.AddP (new JuriPerson ("Graziano", "GRZRVZ76")) ;
    a.AddP (new JuriPerson ("Flavio & Flavio", "FLVCSTBSN54")) ;
    a.AddP (new JuriPerson ("Lorella", "LRLCLM58")) ;
    //회사 데이터를 인쇄한다.
    a.Print ( ) ;
    //cout << a; //구현한다.
	system("pause");
}