/*
算法名称:普里姆算法
算法类型:贪心算法
适用:无向连通网
存储结构:邻接矩阵
功能:求出无向连通网中的最小生成树,最小生成树不唯一,但边权总和一样
规则:生成最小生成树的规则是在红点和蓝点之间的边里找边权最小的
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
typedef struct vex//辅助数组存储结构,用来记录最小生成树顶点集到其余顶点集的权值最小的边
{
    char adjvex;//最小边在最小生成树顶点集中的那个顶点
    int lowcost;//最小边上的权值
}vex,closedge[MVNum];
void LJJZWXW_ij(int *i,AMGraph &LJJZWXW,char *a);//确定顶点在邻接矩阵无向网中的位置,即顶点数组的下标
void LJJZWXWchuangjian(AMGraph &LJJZWXW);
void Prim(AMGraph &LJJZWXW);
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
void LJJZWXWchuangjian(AMGraph &LJJZWXW)
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
    }
    cout<<"邻接矩阵无向网已创建("<<LJJZWXW.vexnum<<"个顶点,"<<LJJZWXW.arcnum<<"条边)"<<endl;
}
void Prim(AMGraph &LJJZWXW,closedge &a)
{
    char b;
    int c=0,i,j,k;
    cout<<"输入该邻接矩阵无向网的一个顶点,"<<endl;
    cout<<"从该顶点出发构造这个邻接矩阵无向网的最小生成树";cin>>b;
    LJJZWXW_ij(&k,LJJZWXW,&b);
    for(j=0;j<LJJZWXW.vexnum;++j)
    {
        if(j!=k)
        {
            a[j].adjvex=b;
            a[j].lowcost=LJJZWXW.arcs[k][j];
        }
    }
    a[k].lowcost=0;//自己到自己不花钱
    cout<<"该邻接矩阵无向网的一个最小生成树(子网)的所有边为:"<<endl;
    for(i=1;i<LJJZWXW.vexnum;++i)
    {
        int linshi=MaxInt;//寻找最小生成树的下一个顶点,返回找到的顶点下标
        for(j=0;j<LJJZWXW.vexnum;j++)
        {
            if(a[j].lowcost!=0&&a[j].lowcost<linshi)
            {
                linshi=a[j].lowcost;
                c=j;
            }
        }//
        cout<<a[c].adjvex<<LJJZWXW.vexs[c]<<" , ";
        a[c].lowcost=0;
        for(j=0;j<LJJZWXW.vexnum;++j)
        {
            if(LJJZWXW.arcs[c][j]<a[j].lowcost)
            {
                a[j]={LJJZWXW.vexs[c],LJJZWXW.arcs[c][j]};
            }
        }
    }
}
main()
{
    AMGraph LJJZWXW;//邻接矩阵无向网地址
    closedge a;//用来存储邻接矩阵无向网的最小生成树的所有边
    LJJZWXWchuangjian(LJJZWXW);
    Prim(LJJZWXW,a);
}
