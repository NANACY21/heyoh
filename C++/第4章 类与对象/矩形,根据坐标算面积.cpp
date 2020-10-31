#include <iostream>
#include <cmath>
using namespace std;
class Point
{
public:
    Point(int X=0,int Y=0)
    {
        x=X;
        y=Y;
    }
    Point(Point &p)
    {
        x=p.x;
        y=p.y;
    }
    int Getx()
    {
        return x;
    }
    int Gety()
    {
        return y;
    }
private:
    int x,y;
};
class Rectangle
{
public:
    Rectangle(Point a,Point b);
    Rectangle(Rectangle &r);
    double Getarea()
    {
        return area;
    }
private:
    Point A,B;
    double area;
};
Rectangle::Rectangle(Point a,Point b):A(a),B(b)
{
    double x=A.Getx()-B.Getx();
    double y=A.Gety()-B.Gety();
    area=fabs(x*y);
}
Rectangle::Rectangle(Rectangle &r):A(r.A),B(r.B)
{
    area=r.area;
}
main()
{
    Point A(1,2),B(2,4);
    Rectangle rectangle(A,B);
    cout<<"这个矩形的面积是";
    cout<<rectangle.Getarea()<<endl;
}
