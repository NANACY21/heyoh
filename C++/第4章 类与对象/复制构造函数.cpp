#include <iostream>
using namespace std;
class Point
{
public:
    Point(int xx=0,int yy=0)    //构造函数，可为Point类的对象初始值化
    {
        x=xx;
        y=yy;
    }
    Point(Point &p);
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
private:
    int x,y;
};
Point::Point(Point &p)
{
    x=p.x;
    y=p.y;
    cout<<"Calling the copy constructor"<<endl;
}
void f(Point p)
{
    cout<<p.getX()<<endl;
}
Point g()
{
    Point a(3,4);    //构造函数起作用
    return a;
}
main()
{
    //同类的对象间的，a为b、c初始化值
    Point a(1,2);    //构造函数起作用，为对象a初始值化
    Point b(a);    //即Point b=a;调用了复制构造函数
    Point c=a;    //即Point c(a);调用了复制构造函数
    cout<<b.getX()<<endl;
    //若函数形参是类的对象，调用函数时，调用了复制构造函数
    f(a);
    //若函数返回值是类的对象，返回函数值时，调用了复制构造函数
    b=g();
    cout<<b.getX()<<","<<b.getY()<<endl;
    //C++书112页4-2例题
}
