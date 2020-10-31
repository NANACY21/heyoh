/*
算法名称:迪杰斯特拉算法
算法类型:贪心算法
适用:有向网,无向网
存储结构:邻接矩阵
功能：计算有向网中任意2个结点之间的可行的最短路径（权值之和最小），（权值>0）
*/
#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
#include<stack>
#define MaxInt 9999//极大值
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
int S[MVNum];//辅助数组S,用于记录从源点到终点是否已被确定最短路径长度,1表示确定,0表示尚未确定
int Path[MVNum];//辅助数组Path,用于记录从源点到终点的当前最短路径上终点的直接前驱顶点序号
int D[MVNum];//辅助数组D,用于记录从源点到终点的当前最短路径长度
void LJJZYXW_ij(int *i,AMGraph &LJJZYXW,char *a);//确定顶点在邻接矩阵有向网中的位置,即顶点数组的下标
void LJJZYXWchuangjian(AMGraph &LJJZYXW);
void Dijkstra(AMGraph &LJJZYXW);
void welcome(AMGraph &LJJZYXW);
void LJJZYXW_ij(int *i,AMGraph &LJJZYXW,char *a)//确定顶点在邻接矩阵有向图中的位置,即顶点数组的下标
{
    if(LJJZYXW.vexnum==0)
    {
        cout<<"没有邻接矩阵有向网"<<endl;
    }
    else
    {
        for(int j=0;j<LJJZYXW.vexnum;j++)
        {
            if(LJJZYXW.vexs[j]==*a)
            {
                *i=j;
            }
        }
    }
}
void LJJZYXWchuangjian(AMGraph &LJJZYXW)
{
    int i,j;
    cout<<"输入该邻接矩阵有向网的顶点数:";
    cin>>LJJZYXW.vexnum;
    cout<<"输入该邻接矩阵有向网的弧数:";
    cin>>LJJZYXW.arcnum;
    for(int i=0;i<LJJZYXW.vexnum;++i)//依次输入点的信息
    {
        cout<<"输入顶点:";
        cin>>LJJZYXW.vexs[i];
    }
    for(int i=0;i<LJJZYXW.vexnum;++i)
    {
        LJJZYXW.visited[i]=0;
    }
    for(int i=0;i<LJJZYXW.vexnum;++i)//初始化邻接矩阵,边的权值均置为MaxInt
    {
        for(int j=0;j<LJJZYXW.vexnum;++j)
        {
            LJJZYXW.arcs[i][j]=MaxInt;
        }
    }
    for(int k=0;k<LJJZYXW.arcnum;++k)
    {
        char v1,v2;
        int w;
        cout<<"输入弧(始点终点):";
        cin>>v1>>v2;
        cout<<"输入这条弧的权值:";
        cin>>w;
        LJJZYXW_ij(&i,LJJZYXW,&v1);//确定顶点v1在LJJZWXW中的位置,即顶点数组下标
        LJJZYXW_ij(&j,LJJZYXW,&v2);//确定顶点v2在LJJZWXW中的位置,即顶点数组下标
        LJJZYXW.arcs[i][j]=w;//顶点数组下标为i的顶点到顶点数组下标为j的顶点有边
    }
    cout<<"邻接矩阵有向网已创建("<<LJJZYXW.vexnum<<"个顶点,"<<LJJZYXW.arcnum<<"条边)"<<endl;
}
void Dijkstra(AMGraph &LJJZYXW)
{
    char a,b;
    int i,j,k,l,Min;
    cout<<"输入该邻接矩阵有向网的一个顶点,"<<endl;
    cout<<"求该顶点到该邻接矩阵有向网中其它所有顶点的最短路径";cin>>a;
    LJJZYXW_ij(&j,LJJZYXW,&a);
    for(i=0;i<LJJZYXW.vexnum;i++)
    {
        S[i]=0;//S初始为空集
        D[i]=LJJZYXW.arcs[j][i];
        if(D[i]<MaxInt)
        {
            Path[i]=j;
        }
        else
        {
            Path[i]=-1;
        }
    }
    S[j]=1;
    D[j]=0;
    for(k=1;k<LJJZYXW.vexnum;k++)
    {
        Min=MaxInt;
        for(l=0;l<LJJZYXW.vexnum;l++)
        {
            if(S[l]==0&&D[l]<Min)
            {
                i=l;
                Min=D[l];
            }
        }
        S[i]=1;
        for(l=0;l<LJJZYXW.vexnum;l++)
        {
            if(S[l]==0&&(D[i]+LJJZYXW.arcs[i][l]<D[l]))
            {
                D[l]=D[i]+LJJZYXW.arcs[i][l];
                Path[l]=i;
            }
        }
    }//---------------------------------------------
    stack <int>linshi;
    cout<<"输入终点";
    cin>>b;
    LJJZYXW_ij(&i,LJJZYXW,&b);
    linshi.push(i);
    while(Path[i]!=-1)
    {
        i=Path[i];
        linshi.push(i);
    }
    while(!linshi.empty())
    {
        i=linshi.top();
        cout<<LJJZYXW.vexs[i]<<" ";
        linshi.pop();
    }
    welcome(LJJZYXW);
}
void welcome(AMGraph &LJJZYXW)
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
            Dijkstra(LJJZYXW);
            break;
        case 'N':
            exit(0);
    }
}
main()
{
    AMGraph LJJZYXW;
    LJJZYXWchuangjian(LJJZYXW);
    welcome(LJJZYXW);
}
