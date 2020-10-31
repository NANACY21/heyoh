#include <iostream>
using namespace std;
class Clock    //Clock是类名，class Clock{};是时钟类的定义，封装了时钟的数据和行为，分别称为Clock类的数据成员和函数成员
{
public:
    Clock(int newH=1,int newM=1,int newS=1);
    void setTime(int newH,int newM,int newS);    //行为，代码成员，成员函数
    void showTime();    //行为，代码成员，成员函数
private:
    int hour,minute,second;    //属性，数据成员
};
Clock::Clock(int newH,int newM,int newS)
{
    hour=newH;
    minute=newM;
    second=newS;
}
inline void Clock::showTime()
{
    cout<<hour<<":"<<minute<<":"<<second<<endl;
}
void Clock::setTime(int newH,int newM,int newS)
{
    hour=newH;
    minute=newM;
    second=newS;
}
main()
{
    Clock c(20,1),c2;    //建立对象c时，会调用构造函数，将实参值用作初始值
    c.showTime();
    c2.showTime();
    c.setTime(8,30,30);
    c.showTime();
}
