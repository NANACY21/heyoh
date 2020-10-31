#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
#include<queue>//队列,优先队列
#include<vector>//向量
#define N 13
using namespace std;
/*
x    0    10    20    30    40    50    60    70    80    90    100    110    120
y    5     1   7.5     3   4.5   8.8  15.5   6.5    -5   -10     -2    4.5      7
*/
int n;//给定经过被插值函数的节点数
struct point
{
    double x;//节点的横坐标
    double y;//节点的纵坐标
};
point fx[N];//用于存经过被插值函数的这些节点
void fx_create();
void get_result();
void fx_create()
{
    int i;
    cout<<"输入给定经过被插值函数的节点数:";
    cin>>n;
    cout<<"输入经过被插值函数的"<<n<<"个节点:"<<endl;
    for(i=0;i<N;i++)
    {
        cout<<"请输入第"<<i+1<<"个节点横纵坐标(按空格键以分隔横纵坐标,输入完请按回车键):";
        cin>>fx[i].x;
        cin>>fx[i].y;
    }
}
void get_result()
{
    int k,i;
    double x,l_k,result=0;
    cout<<"求被插值函数f(x)在点x=?处的近似值? ";
    cin>>x;
    for(k=0;k<=n-1;k++)
    {
        for(i=0,l_k=1;i<=n-1;i++)
        {
            if(i==k)
            {
                continue;
            }
            l_k=l_k*(x-fx[i].x)/(fx[k].x-fx[i].x);
        }
        result=result+l_k*fx[k].y;
    }
    cout<<"被插值函数f(x)在点x="<<x<<"处的近似值为"<<result<<endl;
}
main()
{
    cout<<"实验1:"<<endl;
    cout<<"利用Lagrange插值多项式,求被插值函数f(x)在点x=65处的近似值"<<endl;
    cout<<"建议:画出Lagrange插值多项式的曲线"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    fx_create();
    get_result();
}
