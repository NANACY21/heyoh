#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
using namespace std;
#define MAXSIZE 100
typedef struct//顺序表的存储结构
{
    int *elem;//存储空间的基地址
    int length;//表长(当前长度)
}SqList;
void SXB_init(SqList &L);
void SXB_create(SqList &L,int n);
void SXB_display(SqList &L);
void chashu(SqList &L,int e);//向顺序表中插数
void yiwei(SqList &L,int k);//将顺序表循环移位
void nizhi(SqList &L);//顺序表逆置
void menu(SqList &L,int e,int k);
void welcome(SqList &L,int e,int k);
void SXB_init(SqList &L)
{
    L.elem=new int[MAXSIZE];
    if(!L.elem)
    {
        exit(0);
    }
    L.length=0;
    cout<<"已初始化顺序表"<<endl;
}
void SXB_create(SqList &L,int n)
{
    cout<<"你想在该顺序表添加多少元素?";cin>>n;
    int i;
    for(i=0;i<n;i++)
    {
        cout<<"输入第"<<i+1<<"个元素:";
        cin>>L.elem[i];
        ++L.length;
    }
    cout<<"已创建顺序表,含"<<i<<"个元素"<<endl;
}
void SXB_display(SqList &L)
{
    for(int i=0;i<L.length;i++)
    {
        cout<<L.elem[i]<<"  ";
    }
    cout<<endl;
}
void chashu(SqList &L,int e)
{
    cout<<"输入新增元素:";
    cin>>e;
    int i,j;
    for(i=0;i<L.length;i++)
    {
        if((L.elem[i]<=e)&&(L.elem[i+1]>=e))
        {
            i++;
            i++;
            break;
        }
    }
    if(L.elem[0]>=e)
    {
        i=1;
    }
    if(e>=L.elem[L.length-1])
    {
        i=L.length+1;
    }
    for(j=L.length-1;j>=i-1;j--)
    {
        L.elem[j+1]=L.elem[j];
    }
    L.elem[i-1]=e;
    ++L.length;
}
void yiwei(SqList &L,int k)
{
    int i,j,t;
    cout<<"该顺序表你想顺序右移几位?";cin>>k;
    for(i=0;i<k;i++)
    {
        t=L.elem[L.length-1];
        for(j=L.length-1;j>0;j--)
        {
            L.elem[j]=L.elem[j-1];
        }
        L.elem[0]=t;
    }
}
void nizhi(SqList &L)
{
    int t;
    for(int i=0;i<L.length/2;i++)
    {
        t=L.elem[i];
        L.elem[i]=L.elem[L.length-i-1];
        L.elem[L.length-i-1]=t;
    }
}
void menu(SqList &L,int e,int k)
{
    int c,d;
    cout<<"|---------------------|"<<endl;
    cout<<"|     (1)插数         |"<<endl;
    cout<<"|---------------------|"<<endl;
    cout<<"|     (2)循环移位     |"<<endl;
    cout<<"|---------------------|"<<endl;
    cout<<"|     (3)逆置         |"<<endl;
    cout<<"|---------------------|"<<endl;
    cout<<"|     (4)返回         |"<<endl;
    cout<<"|---------------------|"<<endl;
    do{
        cin>>c;
        if(c<1||c>4)
        {
            cout<<"(输入有误)(1-4)";
            d=1;
            getchar();
        }
        else
        {
            d=0;
        }
    }while(d==1);
    switch(c)
    {
        case 1:
            chashu(L,e);
            SXB_display(L);
            break;
        case 2:
            yiwei(L,k);
            SXB_display(L);
            break;
        case 3:
            nizhi(L);
            SXB_display(L);
            break;
        case 4:
            welcome(L,e,k);
            break;
    }
    welcome(L,e,k);
}
void welcome(SqList &L,int e,int k)
{
    char a,b;
    cout<<"继续?(Y or N)";
    do
    {
        cin>>b;
        if(b!='N'&&b!='Y')
        {
            cout<<"(输入有误)(Y or N)";
            a='Y';
            getchar();
        }
        else
        {
            a=0;
        }
    }while(a=='Y');
    switch(b)
    {
        case 'Y':
            menu(L,e,k);
            break;
        case 'N':
            exit(0);
    }
}
main()
{
    SqList L;
    int n,e,k;
    SXB_init(L);//顺序表初始化
    SXB_create(L,n);//创建顺序表
    SXB_display(L);//显示顺序表
    welcome(L,e,k);
}
