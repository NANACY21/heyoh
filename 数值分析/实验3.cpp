#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
#include<queue>//队列,优先队列
#include<vector>//向量
#include"graphics.h"
#define N 10
using namespace std;
/*
x    0    10    20    30    40    50    60    70    80    90
y   68  67.1  66.4  65.6  64.6  61.8  61.0  60.8  60.4    60
*/
struct point
{
    double x;//节点的横坐标
    double y;//节点的纵坐标
};
point fx[N];
void fx_create();
void get_result();
void fx_create()
{
    for(int i=0;i<N;i++)
    {
        cout<<"输入第"<<i+1<<"个点横纵坐标(按空格键以分隔):";
        cin>>fx[i].x;cin>>fx[i].y;
    }
}
void get_result()
{
    int x;cout<<"输入x的值:";cin>>x;
    //int fai0=1,fai1=x;
    double fai[2][2]={{0,0},{0,0}},a[2],ffai[2];
    for(int i=0;i<10;i++)
    {
        fai[0][0]+=1;
        fai[0][1]+=fx[i].x;
        fai[1][1]+=fx[i].x*fx[i].x;
        ffai[0]+=fx[i].y;
        ffai[1]+=fx[i].y*fx[i].x;
    }
    fai[1][0] = fai[0][1];
    a[0] = (float)(ffai[0]*fai[1][1] - fai[0][1]*ffai[1]) / (float)(fai[0][0]*fai[1][1] - fai[0][1]*fai[1][0]);
    a[1] = (float)(ffai[0]*fai[1][0] - fai[0][0]*ffai[1]) / (float)(fai[0][1]*fai[1][0] - fai[0][0]*fai[1][1]);
    cout<<a[0] + a[1]*x<<endl;
}
main()
{
    cout<<"实验3:"<<endl;
    cout<<"利用曲线拟合的线性最小二乘法求被逼近函数f(x)在点x=55处的近似值"<<endl;
    cout<<"并画出实验数据和直线"<<endl;
    fx_create();
    get_result();
}
