#include<iostream>
using namespace std;
class Point
{
public:
    Point(int X=0,int Y=0)
    {
        x=X;
        y=Y;
        count++;    //在构造函数中对count累加,所有对象共同维护同一个count
    }
    Point(Point &p)
    {
        x=p.x;
        y=p.y;
        count++;
    }
    ~Point()
    {
        count--;
    }
    int getx()
    {
        return x;
    }
    int gety()
    {
        return y;
    }
    static void ShowCount()
    {
        cout<<"  对象个数:"<<count<<endl;
    }
private:
    int x,y;
    static int count;    //静态数据成员声明,用于记录点的个数
};
int Point::count=0;    //静态数据成员定义及初始化,使用类名限定,静态数据成员初始化不放在构造函数,放类外
main()
{
    //count用于记录构造函数和复制构造函数一共调用的次数,即对象个数
    Point a(9);    //定义对象a,调用构造函数,count增1
    cout<<"Point A:"<<a.getx()<<","<<a.gety();
    Point::ShowCount();    //输出对象个数
    Point b(a);    //定义对象b,调用复制构造函数,count增1
    cout<<"Point B:"<<a.getx()<<","<<b.gety();
    Point::ShowCount();    //输出对象个数,Point::showCount();<=>b.showCount();
}
