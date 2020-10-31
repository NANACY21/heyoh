#include <iostream>
using namespace std;
typedef struct //C++中结构体的一般格式
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
}TIME;
main()
{
    //TIME *a=new TIME();
    TIME b;
    TIME *a;
    a=&b;
    cout<<"输入年 月 日 小时 分钟 秒"<<endl;
    cin>>a->year;
    cin>>a->month;
    cin>>a->day;
    cin>>a->hour;
    cin>>a->minute;
    cin>>a->second;
    cout<<a->year<<"年";
    cout<<a->month<<"月";
    cout<<a->day<<"日";
    cout<<a->hour<<"时";
    cout<<a->minute<<"分";
    cout<<a->second<<"秒";
}
