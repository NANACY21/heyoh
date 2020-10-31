//对于(x,y),在一个程序中只能实现x+-y不变或x不变y+-.除非x+-整数y不变,x不变y+-浮点数
//利用友元函数可实现对象+数,数+对象
//利用指针指向访问任意中的输出函数
#include<iostream>
using namespace std;
class Point
{
private:
    int x,y;
public:
    Point();
    Point(int X,int Y);
    ~Point();
    Point operator+(int a);    //运算符重载:对象+数
    Point operator-(int a);    //运算符重载:对象-数
    Point operator+(Point &B);    //运算符重载:对象A+对象B
    Point operator-(Point &B);    //运算符重载:对象A-对象B
    Point &operator++();    //运算符重载:++对象
    Point &operator--();    //运算符重载:--对象
    Point operator++(int);    //运算符重载:对象++
    Point operator--(int);    //运算符重载:对象--
    void coutt();
};
Point::Point()
{
    cout<<"calling constructor without parameters of Point"<<endl;
}
Point::Point(int X,int Y)
{
    x=X;
    y=Y;
    cout<<"calling constructor with parameters of Point"<<endl;
}
Point::~Point()
{
    cout<<"calling destructor of Point"<<endl;
}
Point Point::operator+(int a)
{
    return Point(x+a,y);
}
Point Point::operator-(int a)
{
    return Point(x-a,y);
}
Point Point::operator+(Point &B)
{
    return Point(x+B.x,y+B.y);
}
Point Point::operator-(Point &B)
{
    return Point(x-B.x,y-B.y);
}
Point &Point::operator++()
{
    x++;
    y++;
    cout<<"调用前置++运算符"<<endl;
    return *this;
}
Point &Point::operator--()
{
    x--;
    y--;
    cout<<"调用前置--运算符"<<endl;
    return *this;
}
Point Point::operator++(int)
{
    Point A=*this;    //this的值是当前操作对象的地址
    ++(*this);
    cout<<"调用后置++运算符"<<endl; //调用后置运算符时又调用了一次前置运算符
    return A;
}
Point Point::operator--(int)
{
    Point A=*this;    //this的值是当前操作对象的地址
    --(*this);
    cout<<"调用后置--运算符"<<endl; //调用后置运算符时又调用了一次前置运算符
    return A;
}
void Point::coutt()
{
    cout<<"x="<<x<<";y="<<y<<endl;
}
main()
{
    Point A(1,1),B(3,4),C;
    ++A;
    --A;
    A.coutt();
    A++;
    A--;
    A.coutt();
    C=A+3;
    C.coutt();
    /*int a=1,b=2;
    int c=a+b;cout<<c<<endl;*/
}
