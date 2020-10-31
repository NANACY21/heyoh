#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
#include<queue>//队列,优先队列
#include<vector>//向量
#include<algorithm>//sort()库函数
#include<iomanip>
#define N 3 /* 有3类资源*/
using namespace std;
typedef struct/* 进程类 */
{
    string name;//名
    int Max_A;//该进程总共需要 Max_A 个A类资源
    int Max_B;//该进程总共需要 Max_B 个B类资源
    int Max_C;//该进程总共需要 Max_C 个C类资源
    int Allocation_A;//当前已分给该进程 Allocation_A 个A类资源
    int Allocation_B;//当前已分给该进程 Allocation_B 个B类资源
    int Allocation_C;//当前已分给该进程 Allocation_C 个C类资源
    int Need_A;//该进程还需 Need_A 个A类资源
    int Need_B;//该进程还需 Need_B 个B类资源
    int Need_C;//该进程还需 Need_C 个C类资源
    bool finished;//该进程是否已完成
}process;
int A = 10;
int B = 5;
int C = 7;
int n = 0;//进程个数
void init(process arg0[]);//初始化
void process_situation_time(process arg0[]);
bool safety(process arg0[],int &Available_A,int &Available_B,int &Available_C);//判断系统是否为安全状态
void request_resource(process arg0[],int &Available_A,int &Available_B,int &Available_C);
void init(process arg0[])//初始化
{
    for(int i=0;i<n;i++)
    {
        cout<<"进程名:";
        cin>>arg0[i].name;
        cout<<arg0[i].name<<"总共分别需要A B C三类资源的个数:";
        cin>>arg0[i].Max_A;
        cin>>arg0[i].Max_B;
        cin>>arg0[i].Max_C;
        arg0[i].finished=false;
    }
}
void process_situation_time(process arg0[])
{
    int i,time,Available_A = A,Available_B = B,Available_C = C;
    cout<<"输入时刻以检查这一时刻的系统安全性:";
    cin>>time;
    cout<<"先了解这一时刻的资源分配情况"<<endl;
    for(i=0;i<n;i++)
    {
        cout<<"当前时刻"<<arg0[i].name<<"已分的A B C三类资源的个数:";
        cin>>arg0[i].Allocation_A;
        cin>>arg0[i].Allocation_B;
        cin>>arg0[i].Allocation_C;
        arg0[i].Need_A = arg0[i].Max_A - arg0[i].Allocation_A;
        arg0[i].Need_B = arg0[i].Max_B - arg0[i].Allocation_B;
        arg0[i].Need_C = arg0[i].Max_C - arg0[i].Allocation_C;
        Available_A = Available_A - arg0[i].Allocation_A;
        Available_B = Available_B - arg0[i].Allocation_B;
        Available_C = Available_C - arg0[i].Allocation_C;
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<time<<"时刻的资源分配表"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<setw(10)<<"进程名"<<"|"<<setw(14)<<"总共需要的资源"<<"|"<<setw(14)<<"当前已分的资源"<<"|"<<setw(14)<<"还需要的资源"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<setw(10)<<arg0[i].name<<"|"<<"A "<<setw(2)<<arg0[i].Max_A<<" "<<"B "<<setw(2)<<arg0[i].Max_B<<" "<<"C "<<setw(2)<<arg0[i].Max_C<<"|"<<"A "<<setw(2)<<arg0[i].Allocation_A<<" "<<"B "<<setw(2)<<arg0[i].Allocation_B<<" "<<"C "<<setw(2)<<arg0[i].Allocation_C<<"|"<<"A "<<setw(2)<<arg0[i].Need_A<<" "<<"B "<<setw(2)<<arg0[i].Need_B<<" "<<"C "<<setw(2)<<arg0[i].Need_C<<"|"<<endl;
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<time<<"时刻可利用的A类资源有"<<Available_A<<"个  可利用的B类资源有"<<Available_B<<"个  可利用的C类资源有"<<Available_C<<"个"<<endl;
    if(safety(arg0,Available_A,Available_B,Available_C)==false)
    {
        cout<<time<<"时刻该系统是不安全的"<<endl;
        /*for(i=0;i<n;i++)
        {
            arg0[i].finished=false;
        }*/
    }
    else
    {
        cout<<time<<"时刻该系统是安全的"<<endl;
        //有一个安全序列

        request_resource(arg0,Available_A,Available_B,Available_C);
    }
}
bool safety(process arg0[],int &Available_A,int &Available_B,int &Available_C)//判断系统是否为安全状态
{
    int i;
    int AA = Available_A;
    int BB = Available_B;
    int CC = Available_C;
    for(i=0;i<n;i++)
    {
        if(arg0[i].finished==false && arg0[i].Need_A<=AA && arg0[i].Need_B<=BB && arg0[i].Need_C<=CC)
        {
            AA = AA + arg0[i].Allocation_A;
            BB = BB + arg0[i].Allocation_B;
            CC = CC + arg0[i].Allocation_C;
            arg0[i].finished=true;
            i=-1;
        }
    }
    for(i=0;i<n;i++)
    {
        if(arg0[i].finished==false)
        {
            return false;
        }
    }
    return true;
}
void request_resource(process arg0[],int &Available_A,int &Available_B,int &Available_C)
{
    int i,a,b,c;
    int AA = Available_A;
    int BB = Available_B;
    int CC = Available_C;
    string str;
    cout<<"请求资源的进程:";
    cin>>str;
    for(i=0;i<n;i++)
    {
        if(arg0[i].name==str)
        {
            break;
        }
    }
    if(i==n)
    {
        cout<<"该进程不存在"<<endl;
    }
    else
    {
        cout<<str<<"分别请求的A B C三类资源的个数:";
        cin>>a>>b>>c;
        if(a<=arg0[i].Need_A && b<=arg0[i].Need_B && c<=arg0[i].Need_C && a<=Available_A && b<=Available_B && c<=Available_C)
        {
            arg0[i].Allocation_A += a;
            arg0[i].Allocation_B += b;
            arg0[i].Allocation_C += c;
            arg0[i].Need_A -= a;
            arg0[i].Need_B -= b;
            arg0[i].Need_C -= c;
            AA -= a;
            BB -= b;
            CC -= c;
            if(safety(arg0,AA,BB,CC)==false)
            {
                cout<<"暂时无法为"<<str<<"分配资源"<<endl;
                arg0[i].Allocation_A -= a;
                arg0[i].Allocation_B -= b;
                arg0[i].Allocation_C -= c;
                arg0[i].Need_A += a;
                arg0[i].Need_B += b;
                arg0[i].Need_C += c;
                AA += a;
                BB += b;
                CC += c;
                /*for(int i=0;i<n;i++)
                {
                    arg0[i].finished=false;
                }*/
            }
            else
            {
                cout<<"已为"<<str<<"分配资源"<<endl;
            }
        }
        else
        {
            cout<<"暂时无法为"<<str<<"分配资源"<<endl;
        }
    }
}
main()
{
    cout<<"    银行家算法"<<endl;
    cout<<"现有"<<N<<"类资源  "<<"A类资源有"<<A<<"个  B类资源有"<<B<<"个  C类资源有"<<C<<"个"<<endl;
    cout<<"进程个数:";
    cin>>n;
    process pro[n];
    int time;
    init(pro);//初始化
    process_situation_time(pro);
}
