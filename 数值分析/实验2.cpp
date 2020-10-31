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
int n;//给定经过被插值函数的节点数
struct point
{
    double x;//节点的横坐标
    double y;//节点的纵坐标
    double m;//一次导数
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
        cout<<"请输入第"<<i+1<<"个节点横纵坐标和1次导数(按空格键以分隔):";
        cin>>fx[i].x;
        cin>>fx[i].y;
        cin>>fx[i].m;
    }
}
void get_result()
{
    int i,j;
    double x;
    static double l,l1,result,a[N],b[N];
    cout<<"求被插值函数f(x)在点x=?处的近似值? ";
    cin>>x;
    for(i=0;i<=n-1;i++)
    {
        l=1.0;l1=0.0;
        for(j=0;j<=n-1;j++)
        {
            if(j!=i)
            {
                l=l * (x - fx[j].x)/(fx[i].x - fx[j].x);
                l1=l1+1.0/(fx[i].x-fx[j].x);
            }
        }
        l=l*l;
        a[i]=(1.0-2.0*(x-fx[i].x)*l1)*l;
        b[i]=(x-fx[i].x)*l;
    }
    result=0.0;
    for(i=0;i<=n-1;i++)
    {
        result=result+fx[i].y*a[i]+fx[i].m*b[i];
    }
    cout<<"被插值函数f(x)在点x="<<x<<"处的近似值为"<<result<<endl;
}
main()
{
/*
x        0.10        0.20        0.30        0.40        0.50
y    0.904837    0.818731    0.740818    0.670320    0.606531
m   -0.904837   -0.818731   -0.740818   -0.670320   -0.606531
x        0.60        0.70        0.80        0.90        1.00
y    0.548812    0.496585    0.449329    0.406570    0.367879
m   -0.548812   -0.496585   -0.449329   -0.406570   -0.367879
*/
    cout<<"实验2:"<<endl;
    cout<<"利用Hermite插值多项式,求被插值函数f(x)在点x=0.55处的近似值"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    fx_create();
    get_result();
    /*图像*/
    //int graphdriver=DETECT,graphmode;
    int a,b;
    a=300;
    b=300;
     cout<<"test"<<endl;
    initgraph(&a,&b,"C://tc");
    //initgraph(300,300);
    cout<<"test"<<endl;
    /*putpixel(0.10,0.904837,1);
    putpixel(0.20,0.818731,1);
    putpixel(0.30,0.740818,1);
    putpixel(0.40,0.670320,1);
    putpixel(0.50,0.606531,1);
    putpixel(0.60,0.548812,1);
    putpixel(0.70,0.496585,1);
    putpixel(0.80,0.449329,1);
    putpixel(0.90,0.406570,1);
    putpixel(1.00,0.367879,1);
    line(0.10,0.904837,0.20,0.818731);
    line(0.20,0.818731,0.30,0.740818);
    line(0.30,0.740818,0.40,0.670320);
    line(0.40,0.670320,0.50,0.606531);
    line(0.50,0.606531,0.60,0.548812);
    line(0.60,0.548812,0.70,0.496585);
    line(0.70,0.496585,0.80,0.449329);
    line(0.80,0.449329,0.90,0.406570);
    line(0.90,0.406570,1.00,0.367879);*/
    putpixel(1,1,4);
    putpixel(2,2,1);
    line(1,1,2,2);

    closegraph();
}

