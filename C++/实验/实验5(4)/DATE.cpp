#include<iostream>
#include<string.h>
#include"DATE.h"
using namespace std;
DATE::DATE()
{
    cout<<"calling constructor without parameters of DATE"<<endl;    //调用DATE类无参构造函数
}
DATE::DATE(int YEAR,int MONTH,int DAY)
{
    year=YEAR;
    month=MONTH;
    day=DAY;
    cout<<"calling constructor with parameters of DATE"<<endl;    //调用DATE类有参构造函数
}
DATE::DATE(DATE &d)
{
    year=d.year;
    month=d.month;
    day=d.month;
    cout<<"calling the copy constructor of DATE"<<endl;    //调用DATE类复制构造函数
}
DATE::~DATE()
{
    cout<<"calling destructor of DATE"<<endl;    //调用DATE类析构函数
}
void DATE::Cin()
{
    cin>>year>>month>>day;
}
void DATE::Cout()
{
    cout<<year<<","<<month<<","<<day<<".";
}
