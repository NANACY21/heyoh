#include<iostream>
#include<cmath>
using namespace std;
class Point
{
public:
    Point(int X=0,int Y=0);
    Point(Point &p);
    ~Point();
    int Getx();
    int Gety();
private:
    int x,y;
};
Point::Point(int X,int Y)
{
    x=X;
    y=Y;
    cout<<"已调用点类的构造函数"<<endl;
}
Point::Point(Point &p)
{
    x=p.x;
    y=p.y;
    cout<<"已调用点类的复制构造函数"<<endl;
}
Point::~Point()
{
    cout<<"已调用点类的析构函数"<<endl;
}
int Point::Getx()
{
    return x;
}
int Point::Gety()
{
    return y;
}
class Line
{
public:
    Line(Point a,Point b);
    Line(Line &l);
    ~Line();
    double Getlen();
private:
    Point A,B;
    double len;
};
Line::Line(Point a,Point b):A(a),B(b)
{
    double x=A.Getx()-B.Getx();
    double y=A.Gety()-B.Gety();
    len=sqrt(x*x+y*y);
    cout<<"已调用线类的构造函数"<<endl;
}
Line::Line(Line &l):A(l.A),B(l.B)
{
    cout<<"已调用线类的复制构造函数"<<endl;
    len=l.len;

}
Line::~Line()
{
    cout<<"已调用线类的析构函数"<<endl;
}
double Line::Getlen()
{
    return len;
}
main()
{
    Point C(1,2),D(4,6);    //建立Point类的对象
    Line E(C,D);    //建立Line类的对象
    Line F(E);    //利用复制构造函数建立一个新对象
    cout<<"E线的长是:";
    cout<<E.Getlen()<<endl;
    cout<<"F线的长是:";
    cout<<F.Getlen()<<endl;
}





















