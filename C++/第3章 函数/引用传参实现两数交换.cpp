#include<iostream>
using namespace std;
void swap(int &a,int &b)
{
    int t;
    t=a;
    a=b;
    b=t;
}
main()
{
    int x(5),y(10);
    cout<<"x="<<x<<";"<<"y="<<y<<endl;
    swap(x,y);    //即int &a=x;初始化
    cout<<"x="<<x<<";"<<"y="<<y<<endl;
    int i,j;
    int &ri=i;    //建立一个int型的引用ri,并将其初始化为变量i的一个别名
    j=10;
    ri=j;    //相当于i=j;
    cout<<i<<endl;
}
