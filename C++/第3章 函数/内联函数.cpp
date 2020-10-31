//功能简单、规模较小、使用频繁的函数可以设计为内联函数
#include <iostream>
using namespace std;
const double PI=3.1415926;
inline double calArea(double radius)    //内联函数，根据圆的半径计算面积
{
    return PI*radius*radius;
}
main()
{
    double r=3.0;
    double area=calArea(r);    //调用内联函数求圆面积，编译时此处被替换为calArea函数体语句
    cout<<area<<endl;
}
