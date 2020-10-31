#include<iostream>
#include<cmath>
using namespace std;
class Point
{
public:
    Point(int X=0,int Y=0);
    int getx();
    int gety();
    friend float dist(Point &A,Point &B);    //友元函数(非成员函数)声明
private:
    int x,y;
};
Point::Point(int X,int Y)
{
    x=X;
    y=Y;
}
int Point::getx()
{
    return x;
}
int Point::gety()
{
    return y;
}
float dist(Point &A,Point &B)    //友元函数实现
{
    double x=A.x-B.x;    //通过对象访问私有数据成员
    double y=A.y-B.y;
    return sqrt(x*x+y*y);
}
main()
{
    Point A(0,0),B(3,4);    //定义Point类对象
    cout<<"两点间距是:"<<dist(A,B)<<endl;;
}
