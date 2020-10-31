//形参个数不同或类型不同,可以重载
//重载函数功能要一样,但默认形参值重载时,需注意二义性
#include <iostream>
using namespace std;
template<typename A>
A maxx(A x,A y,A z)
{
    if(x>y&&x>z)
    return x;
    else if(y>x&&y>z)
    return y;
    else
    return z;
}
template<typename B>
B maxx(B x,B y)
{
    if(x>y)
    return x;
    else
    return y;
}
main()
{
    double a,b;cin>>a>>b;
    cout<<maxx(a,b)<<endl;
}
