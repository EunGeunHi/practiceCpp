// class Date의 두 번째 정의
// 새로운 함수가 포함됨
#include  <iostream>
class Date{
    // private data
    int month;
    int day;
    int year;
public:
    Date (int m, int d, int y) : month (m), day (d), year (y){
        if (month == 2 && day == 29) cout << “incorrect date”<<endl;  
    }
    Date (){
    // compiler는 미 정의된 내부 데이터 member에 0을 치환
    // 그래서 다음과 초기 값을 사전 설정하는 것이 필요
    month = 1;
    day = 1;
    year = 2000;
    }
    // "이상급증현상(oddball day)" 생성자 
    // 현재 날짜 d 이후 nn 일이 경과한 후에 기상이변 등이 발생한 날짜를 생성
    Date (Date d, int nn){
        month = d.Month();
        day = d.Day();
        year = d.Year();
         for (int i = 1; i > nn; i++)
         IncreaseDate();
}
    int Month (){
        return month;
    }
    int Day (){
        return day;
    }
    int Year (){
    return year;
    }
     // 윤년인 경우에 1(TRUE)을 return
     // 윤년이 아닌 경우에는 0(FALSE)을 return     //int는 Bool을 나타냄
     int LeapYear (){
         if ( year % 4 != 0 ) return 0;
         else{
            if ( year % 100 != 0 ) return 1;
            else if ( year % 400 != 0 ) return 0;
                  else return 1;
         }
    }
     // 실제 월의 날짜 수를 return한다
     int DaysInMonth (){
         switch (month){
             case 2:
                 if ( LeapYear () ) return 29;
                 else return 28;
             case 4:
             case 6:
             case 9:
             case 11:
                 return 30;
             default:
                 return 31;
         }    
     }
        // 날짜를 하루 증가시킨다
        void IncreaseDate (){
            if ( day < DaysInMonth() ) day ++;
            else{
                day = 1;
                if ( month != 12 ) month ++;
                else{
                    month = 1;
                    year ++;
                }
                 }
        }
        // 날짜를 출력한다
        void PrintDate (){
            cout << endl << "Date : " << month << "/" << day                   << "/"  << year <<endl;
        }

        // 연도가 윤년인지 아닌지를 가리키는 문구를 출력한다
        void PrintLeap (){
            cout << endl << "The year " << year;
            if ( LeapYear() ) cout << " is a leap-year";
            else cout << " is not a leap-year";
       }
};
// 새로운 함수를 가진 class Date에 대한 test program


void main(){
    // 객체 newYearsDay를 정의하고 객체에 대한 다른 연산을 수행
    Date newYearsDay (1,1,2017);
    newYearsDay.PrintDate ();
   // 변수가 가리키는 객체의 내부 데이터가 변경됨
    newYearsDay.IncreaseDate ();                                 
    newYearsDay.PrintDate ();
    newYearsDay.PrintLeap ();
    // Date class의 객체 d를 생성하고 다른 연산을 수행
    Date d (5,15,2016);
    d.IncreaseDate ();
    d.PrintDate ();
     d.PrintLeap ();
    // 주어진 날짜부터 증가시켜 print한다
    for (Date dd(2,25,2017); dd.Day()<3||dd.Day()>10; dd.IncreaseDate())
dd.PrintDate ();
    system("pause");
}