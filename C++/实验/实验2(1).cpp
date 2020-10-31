//形参个数不同或类型不同,可以重载
//重载函数功能要一样,但默认形参值重载时,需注意二义性
#include <iostream>
using namespace std;
int maxx(int x,int y)
{
    if(x>y)
    return x;
    else
    return y;
}
double maxx(double x,double y)
{
    if(x>y)
    return x;
    else
    return y;
}
int maxx(int x,int y=0,int z=0)
{
    if(x>y&&x>z)
    return x;
    else if(y>x&&y>z)
    return y;
    else
    return z;
}
double maxx(double x,double y,double z)
{
    if(x>y&&x>z)
    return x;
    else if(y>x&&y>z)
    return y;
    else
    return z;
}
main()
{
    int a,b,c;double d,e,f;
    cin>>d>>e>>f;cout<<maxx(d,e,f)<<endl;
    cin>>a>>b>>c;cout<<maxx(a,b,c)<<endl;
}
