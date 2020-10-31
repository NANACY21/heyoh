#include<iostream>
#include<string.h>
#define N 20
using namespace std;
class DATE
{
private:
    int year,month,day;
public:
    DATE(int YEAR=0,int MONTH=0,int DAY=0) //DATE类构造函数
    {
        year=YEAR;
        month=MONTH;
        day=DAY;
    }
    void cinn()
    {
        cin>>year>>month>>day;
    }
    void coutt()
    {
        cout<<year<<"年"<<month<<"月"<<day<<"日";
    }
};
class PEOPLE //类的组合
{
private:
     char number[N],ID[N],sex[N];
     DATE birthday;
public:
    PEOPLE():birthday()
    {

    }
    PEOPLE(char NUMBER[N],char IDD[N],char SEX[N],int YEAR,int MONTH,int DAY):birthday(YEAR,MONTH,DAY)
    {
        strcpy(number,NUMBER);
        strcpy(ID,IDD);
        strcpy(sex,SEX);
    }
    PEOPLE(PEOPLE &p)
    {
        strcpy(number,p.number);
        strcpy(ID,p.ID);
        strcpy(sex,p.sex);
        birthday=p.birthday;
    }
    ~PEOPLE()
    {
        cout<<number<<"号人员已经录入"<<endl;
    }
    void cinn()
    {
        cout<<"输入(录入)数据 number(编号) ID(身份证号) sex(性别) birthday(出生日期) "<<endl;
        cin>>number;
        cin>>ID;
        cin>>sex;
        birthday.cinn();
    }
    void coutt()
    {
        cout<<"编号:"<<number<<endl;
        cout<<"身份证号:"<<ID<<endl;
        cout<<"性别:"<<sex<<endl;
        cout<<"生日:";
        birthday.coutt();
        cout<<endl;
    }
};
main()
{
    PEOPLE a;
    a.cinn();
    a.coutt();
}



















