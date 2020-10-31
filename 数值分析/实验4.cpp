#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
#include<math.h>
#include<queue>//队列,优先队列
#include<vector>//向量
using namespace std;
long double f(long double x);
long double f(long double x)
{
    return exp(x)*cos(x);
}
main()
{
    long double ypxl=0.000001;
    int n=1;
    long double a=0.00,b=3.14159265358979323846;
    long double h = b - a;
    long double Tn = (h/2) * (f(a)+f(b));
    long double Hn;
    long double temp=0.00;
    for(int i=0;i<=n-1;i++)
    {
        temp += f(a + ((2*i + 1)*h / (long double)2));
    }
    Hn = temp * h;
    long double T2n=(Tn + Hn) / 2;
    n = 2 * n;
    h = h / 2;
    while(fabs(T2n - Tn) >= ypxl)
    {
        Tn=T2n;
        temp=0.00;
        for(int i=0;i<=n-1;i++)
        {
            temp += f(a + ((2*i + 1)*h / (long double)2));
        }
        Hn = temp * h;
        T2n=(Tn + Hn) / 2;
        n = 2 * n;
        h = h / 2;
    }
    cout<<"Tn:"<<T2n<<"    n/2:"<<n/2<<endl;
}
