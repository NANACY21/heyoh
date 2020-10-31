/*
算法名称:克鲁斯卡尔算法
算法类型:贪心算法
适用:无向连通网
存储结构:邻接矩阵
功能:求出无向连通网中的最小生成树,最小生成树不唯一,但边权总和一样
*/
#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
#define MaxInt 3000//极大值
#define MVNum 100//最大顶点数
using namespace std;
typedef struct//图的邻接矩阵(顺序)存储结构
{
    char vexs[MVNum];//顶点表
    int visited[MVNum];//顶点访问标记数组,与顶点表一一对应
    int arcs[MVNum][MVNum];//邻接矩阵
    int vexnum;//图当前点数
    int arcnum;//图当前边数
}AMGraph;
typedef struct edge//辅助数组Edge
{
    char duandian1;//边的端点
    char duandian2;//边的另一端点
    int lowcost;//边权
}edge,Edge[MVNum];
int Vexset[MVNum];//辅助数组Vexset
void LJJZWXW_ij(int *i,AMGraph &LJJZWXW,char *a);//确定顶点在邻接矩阵无向网中的位置,即顶点数组的下标
void LJJZWXWchuangjian(AMGraph &LJJZWXW,Edge &a);
void Kruskal(AMGraph &LJJZWXW,Edge &a);
void LJJZWXW_ij(int *i,AMGraph &LJJZWXW,char *a)//确定顶点在邻接矩阵无向图中的位置,即顶点数组的下标
{
    if(LJJZWXW.vexnum==0)
    {
        cout<<"没有邻接矩阵无向网"<<endl;
    }
    else
    {
        for(int j=0;j<LJJZWXW.vexnum;j++)
        {
            if(LJJZWXW.vexs[j]==*a)
            {
                *i=j;
            }
        }
    }
}
void LJJZWXWchuangjian(AMGraph &LJJZWXW,Edge &a)
{
    int i,j;
    cout<<"输入该邻接矩阵无向网的顶点数:";
    cin>>LJJZWXW.vexnum;
    cout<<"输入该邻接矩阵无向网的边数:";
    cin>>LJJZWXW.arcnum;
    for(int i=0;i<LJJZWXW.vexnum;++i)//依次输入点的信息
    {
        cout<<"输入顶点:";
        cin>>LJJZWXW.vexs[i];
    }
    for(int i=0;i<LJJZWXW.vexnum;++i)
    {
        LJJZWXW.visited[i]=0;
    }
    for(int i=0;i<LJJZWXW.vexnum;++i)//初始化邻接矩阵,边的权值均置为MaxInt
    {
        for(int j=0;j<LJJZWXW.vexnum;++j)
        {
            LJJZWXW.arcs[i][j]=MaxInt;
        }
    }
    for(int k=0;k<LJJZWXW.arcnum;++k)
    {
        char v1,v2;
        int w;
        cout<<"输入边:";
        cin>>v1>>v2;
        cout<<"输入这条边的权值:";
        cin>>w;
        LJJZWXW_ij(&i,LJJZWXW,&v1);//确定顶点v1在LJJZWXW中的位置,即顶点数组下标
        LJJZWXW_ij(&j,LJJZWXW,&v2);//确定顶点v2在LJJZWXW中的位置,即顶点数组下标
        LJJZWXW.arcs[i][j]=w;//顶点数组下标为i的顶点到顶点数组下标为j的顶点有边
        LJJZWXW.arcs[j][i]=LJJZWXW.arcs[i][j];//因为是无向图
        a[k].duandian1=v1;//
        a[k].duandian2=v2;//
        a[k].lowcost=w;//
    }
    cout<<"邻接矩阵无向网已创建("<<LJJZWXW.vexnum<<"个顶点,"<<LJJZWXW.arcnum<<"条边)"<<endl;
}
void Kruskal(AMGraph &LJJZWXW,Edge &a)
{
    int i,j,k;edge t;//把a数组(已存邻接矩阵无向网所有边)中元素按边权从小到大排序
    for(i=0;i<LJJZWXW.arcnum-1;i++)
    {
        k=i;
        for(j=i+1;j<LJJZWXW.arcnum;j++)
        {
            if(a[j].lowcost<a[k].lowcost)
            {
                k=j;
            }
        }
        if(k!=i)
        {
            t=a[k];
            a[k]=a[i];
            a[i]=t;
        }
    }//
    for(i=0;i<LJJZWXW.vexnum;++i)
    {
        Vexset[i]=i;
    }
    cout<<"该邻接矩阵无向网的一个最小生成树(子网)的所有边为:"<<endl;
    for(i=0;i<LJJZWXW.arcnum;++i)
    {
        int ij1,ij2,vs1,vs2;
        LJJZWXW_ij(&ij1,LJJZWXW,&a[i].duandian1);
        LJJZWXW_ij(&ij2,LJJZWXW,&a[i].duandian2);
        vs1=Vexset[ij1];
        vs2=Vexset[ij2];
        if(vs1!=vs2)
        {
            cout<<a[i].duandian1<<a[i].duandian2<<" , ";
            for(j=0;j<LJJZWXW.vexnum;++j)
            {
                if(Vexset[j]==vs2)
                {
                    Vexset[j]=vs1;
                }
            }
        }
    }
}
main()
{
    AMGraph LJJZWXW;
    Edge a;
    LJJZWXWchuangjian(LJJZWXW,a);
    Kruskal(LJJZWXW,a);
}
