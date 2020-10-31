#include <iostream>
using namespace std;
#define PI 3.14
class CIRCLE
{
public:
    void compute()
    {
        cout<<"请输入圆的半径";cin>>r;
        area=r*r*PI;
        cout<<"这个圆的面积是"<<area<<endl;
    }
private:
    int r;double area;
};
class RECTANGLE
{
public:
    void compute()
    {
        cout<<"请输入长方形的长、宽";cin>>l>>h;
        area=l*h;
        cout<<"这个长方形的面积是"<<area<<endl;
    }
private:
    int l,h,area;
};
class SQUARE
{
public:
    void compute()
    {
        cout<<"请输入正方形的边长";cin>>a;
        area=a*a;
        cout<<"这个正方形的面积是"<<area<<endl;
    }
private:
    int a,area;
};
main()
{
    cout<<"选择要计算的图形 (1)圆(2)长方形(3)正方形 ";
    int a,b;
    do{
    cin>>a;
    if(a<1||a>3)
    {
        cout<<"输入有误(1-3)";
        b=1;
        cin>>a;
    }
    else
    {
        b=0;
    }
    }while(b==1);
    switch(a)
    {
        case 1:CIRCLE a;a.compute();break;
        case 2:RECTANGLE b;b.compute();break;
        case 3:SQUARE c;c.compute();break;
    }

}
