/*
简单路径:图深度优先搜索遍历的改进
最短路径(路径长度最少):图广度优先搜索遍历的改进
*/
#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<math.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
#include<stack>//栈
#include<queue>//队列,优先队列
#include<algorithm>//堆
#include<vector>//向量
#define MaxInt 9999//极大值
#define MVNum 100//最大顶点数
#define bag 40//书包的容量(最大能承受bag斤的重量,无需考虑体积问题)
using namespace std;
/*图的邻接矩阵(顺序)存储结构*/
typedef struct
{
    char vexs[MVNum];//顶点表
    int visited[MVNum];//顶点访问标记数组,与顶点表一一对应
    int arcs[MVNum][MVNum];//邻接矩阵
    int vexnum;//图当前点数
    int arcnum;//图当前边数
}AMGraph;
/*图的邻接表(链式)存储结构*/
typedef struct ArcNode//边结点
{
    int adjvex;//该边所指向的顶点的位置
    struct ArcNode *nextarc;//指向下一条边的指针
    //OtherInfo info;//和边相关的信息,一般是边权,不是网则无
}ArcNode;
typedef struct VNode//顶点信息
{
    char data;
    int visited;//顶点访问标记,与顶点一一对应
    ArcNode *firstarc;//指向第一条依附该顶点的边的指针
    VNode *jiazhang;
}VNode,AdjList[MVNum];//AdjList表示邻接表类型
typedef struct//邻接表
{
    AdjList vertices;
    int vexnum;//图当前点数
    int arcnum;//图当前边数
}ALGraph;
void LJJZWXT_ij(int *i,AMGraph &LJJZWXT,char *a);//确定顶点在邻接矩阵无向图中的位置,即顶点数组的下标
void LJJZWXT_create(AMGraph &LJJZWXT);//邻接矩阵无向图创建
void LJJZWXT_DFS(AMGraph &LJJZWXT);//邻接矩阵无向图深度优先搜索遍历
void LJJZWXT_BFS(AMGraph &LJJZWXT);//邻接矩阵无向图广度优先搜索遍历
void LJBWXT_ij(int *i,AMGraph &LJJZWXT,char *a);//确定顶点在邻接表无向图中的位置,即顶点数组的下标
void LJBWXT_create(ALGraph &LJBWXT);//邻接表无向图创建
void LJBWXT_DFS(ALGraph &LJBWXT);//邻接表无向图深度优先搜索遍历
void LJBWXT_BFS(ALGraph &LJBWXT);//邻接表无向图广度优先搜索遍历
void LJJZWXT_jdlj(AMGraph &LJJZWXT);//求邻接矩阵无向图顶点到另一顶点的一条简单路径
void LJBWXT_zdlj(ALGraph &LJBWXT);//求邻接表无向图顶点到另一顶点的最短路径
void menu(AMGraph &LJJZWXT,ALGraph &LJBWXT);
void welcome(AMGraph &LJJZWXT,ALGraph &LJBWXT);
void LJJZWXT_ij(int *i,AMGraph &LJJZWXT,char *a)//确定顶点在邻接矩阵无向图中的位置,即顶点数组的下标
{
    if(LJJZWXT.vexnum==0)
    {
        cout<<"没有邻接矩阵无向图"<<endl;
    }
    else
    {
        for(int j=0;j<LJJZWXT.vexnum;j++)
        {
            if(LJJZWXT.vexs[j]==*a)
            {
                *i=j;
            }
        }
    }
}
void LJJZWXT_create(AMGraph &LJJZWXT)//邻接矩阵无向图创建
{
    int i,j;
    cout<<"输入该邻接矩阵无向图的顶点数:";
    cin>>LJJZWXT.vexnum;
    cout<<"输入该邻接矩阵无向图的边数:";
    cin>>LJJZWXT.arcnum;
    for(int i=0;i<LJJZWXT.vexnum;++i)//依次输入点的信息
    {
        cout<<"输入顶点:";
        cin>>LJJZWXT.vexs[i];
    }
    for(int i=0;i<LJJZWXT.vexnum;++i)
    {
        LJJZWXT.visited[i]=0;
    }
    for(int i=0;i<LJJZWXT.vexnum;++i)//初始化邻接矩阵,边的权值均置为0
    {
        for(int j=0;j<LJJZWXT.vexnum;++j)
        {
            LJJZWXT.arcs[i][j]=0;
        }
    }
    for(int k=0;k<LJJZWXT.arcnum;++k)
    {
        char v1,v2;
        cout<<"输入边:";
        cin>>v1>>v2;
        LJJZWXT_ij(&i,LJJZWXT,&v1);//确定顶点v1在LJJZWXT中的位置,即顶点数组下标
        LJJZWXT_ij(&j,LJJZWXT,&v2);//确定顶点v2在LJJZWXT中的位置,即顶点数组下标
        LJJZWXT.arcs[i][j]=1;//顶点数组下标为i的顶点到顶点数组下标为j的顶点有边
        LJJZWXT.arcs[j][i]=LJJZWXT.arcs[i][j];//因为是无向图
    }
    cout<<"邻接矩阵无向图已创建("<<LJJZWXT.vexnum<<"个顶点,"<<LJJZWXT.arcnum<<"条边)"<<endl;
}
void LJJZWXT_DFS(AMGraph &LJJZWXT)//邻接矩阵无向图深度优先搜索遍历
{
    if(LJJZWXT.vexnum==0)
    {
        cout<<"没有邻接矩阵无向图"<<endl;
    }
    else
    {
        stack <char>temp;
        int i;char a,b;
        for(i=0;i<LJJZWXT.vexnum;i++)
        {
            LJJZWXT.visited[i]=0;
        }
        cout<<"输入顶点,以该顶点为起始点深度优先搜索遍历邻接矩阵无向图:";
        A:cin>>a;
        for(i=0;i<LJJZWXT.vexnum;i++)
        {
            if(LJJZWXT.vexs[i]==a)
            {
                cout<<a<<"  ";
                LJJZWXT_ij(&i,LJJZWXT,&a);
                LJJZWXT.visited[i]=1;
                temp.push(a);
                break;
            }
        }
        if(i==LJJZWXT.vexnum)
        {
            cout<<a<<"不是该邻接矩阵无向图的顶点"<<endl;
            goto A;
        }
        while(!temp.empty())
        {
            b=temp.top();
            LJJZWXT_ij(&i,LJJZWXT,&b);
            int k;
            for(k=0;k<LJJZWXT.vexnum;k++)
            {
                if(LJJZWXT.arcs[i][k]==1&&LJJZWXT.visited[k]==0)
                {
                    cout<<LJJZWXT.vexs[k]<<"  ";LJJZWXT.visited[k]=1;
                    temp.push(LJJZWXT.vexs[k]);
                    break;
                }
            }
            if(k==LJJZWXT.vexnum)
            {
                temp.pop();
            }
        }
    }
}
void LJJZWXT_BFS(AMGraph &LJJZWXT)//邻接矩阵无向图广度优先搜索遍历
{
    if(LJJZWXT.vexnum==0)
    {
        cout<<"没有邻接矩阵无向图"<<endl;
    }
    else
    {
        queue <char>temp;
        int i;char a,b;
        for(i=0;i<LJJZWXT.vexnum;i++)
        {
            LJJZWXT.visited[i]=0;
        }
        cout<<"输入顶点,以该顶点为起始点广度优先搜索遍历邻接矩阵无向图:";
        A:cin>>a;
        for(i=0;i<LJJZWXT.vexnum;i++)
        {
            if(LJJZWXT.vexs[i]==a)
            {
                cout<<a<<"  ";
                LJJZWXT_ij(&i,LJJZWXT,&a);
                LJJZWXT.visited[i]=1;
                temp.push(a);
                break;
            }
        }
        if(i==LJJZWXT.vexnum)
        {
            cout<<a<<"不是该邻接矩阵无向图的顶点"<<endl;
            goto A;
        }
        while(!temp.empty())
        {
            b=temp.front();
            LJJZWXT_ij(&i,LJJZWXT,&b);
            int k;
            for(k=0;k<LJJZWXT.vexnum;k++)
            {
                if(LJJZWXT.arcs[i][k]==1&&LJJZWXT.visited[k]==0)
                {
                    cout<<LJJZWXT.vexs[k]<<"  ";LJJZWXT.visited[k]=1;
                    temp.push(LJJZWXT.vexs[k]);
                }
            }
            temp.pop();
        }
    }
}
void LJBWXT_ij(int *i,ALGraph &LJBWXT,char *a)//确定顶点在邻接表无向图中的位置,即顶点数组的下标
{
    if(LJBWXT.vexnum==0)
    {
        cout<<"没有无向图"<<endl;
    }
    else
    {
        for(int j=0;j<LJBWXT.vexnum;j++)
        {
            if(LJBWXT.vertices[j].data==*a)
            {
                *i=j;
            }
        }
    }
}
void LJBWXT_create(ALGraph &LJBWXT)//邻接表无向图创建
{
    int i,j;
    cout<<"输入该邻接表无向图的顶点数:";
    cin>>LJBWXT.vexnum;
    cout<<"输入该邻接表无向图的边数:";
    cin>>LJBWXT.arcnum;
    for(int i=0;i<LJBWXT.vexnum;++i)
    {
        cout<<"输入顶点:";
        cin>>LJBWXT.vertices[i].data;
        LJBWXT.vertices[i].visited=0;
        LJBWXT.vertices[i].firstarc=NULL;
    }
    for(int k=0;k<LJBWXT.arcnum;++k)
    {
        char v1,v2;
        cout<<"输入边:";
        cin>>v1>>v2;
        LJBWXT_ij(&i,LJBWXT,&v1);
        LJBWXT_ij(&j,LJBWXT,&v2);
        ArcNode *p1;p1=new ArcNode;
        p1->adjvex=j;
        p1->nextarc=LJBWXT.vertices[i].firstarc;////
        LJBWXT.vertices[i].firstarc=p1;////
        ArcNode *p2;p2=new ArcNode;
        p2->adjvex=i;
        p2->nextarc=LJBWXT.vertices[j].firstarc;
        LJBWXT.vertices[j].firstarc=p2;
    }
    cout<<"邻接表无向图已创建("<<LJBWXT.vexnum<<"个顶点,"<<LJBWXT.arcnum<<"条边)"<<endl;
}
void LJBWXT_DFS(ALGraph &LJBWXT)//邻接表无向图深度优先搜索遍历
{
    if(LJBWXT.vexnum==0)
    {
        cout<<"没有邻接矩阵无向图"<<endl;
    }
    else
    {
        stack <char>temp;
        int i;char a,b;
        ArcNode *linshifirstarc[LJBWXT.vexnum];
        for(i=0;i<LJBWXT.vexnum;i++)//初始化
        {
            linshifirstarc[i]=LJBWXT.vertices[i].firstarc;
            LJBWXT.vertices[i].visited=0;
        }
        cout<<"输入顶点,以该顶点为起始点深度优先搜索遍历邻接表无向图:";
        A:cin>>a;
        for(i=0;i<LJBWXT.vexnum;i++)
        {
            if(LJBWXT.vertices[i].data==a)
            {
                cout<<a<<"  ";
                LJBWXT_ij(&i,LJBWXT,&a);
                LJBWXT.vertices[i].visited=1;
                temp.push(a);
                break;
            }
        }
        if(i==LJBWXT.vexnum)
        {
            cout<<a<<"不是该邻接表无向图的顶点"<<endl;
            goto A;
        }
        while(!temp.empty())
        {
            b=temp.top();
            LJBWXT_ij(&i,LJBWXT,&b);
            int k;
            while(linshifirstarc[i]!=NULL)
            {
                if(LJBWXT.vertices[linshifirstarc[i]->adjvex].visited==0)
                {
                    cout<<LJBWXT.vertices[linshifirstarc[i]->adjvex].data<<"  ";
                    LJBWXT.vertices[linshifirstarc[i]->adjvex].visited=1;
                    temp.push(LJBWXT.vertices[linshifirstarc[i]->adjvex].data);
                    break;
                }
                linshifirstarc[i]=linshifirstarc[i]->nextarc;
            }
            if(linshifirstarc[i]==NULL)
            {
                temp.pop();
            }
        }
    }
}
void LJBWXT_BFS(ALGraph &LJBWXT)//邻接表无向图广度优先搜索遍历
{
    if(LJBWXT.vexnum==0)
    {
        cout<<"没有邻接矩阵无向图"<<endl;
    }
    else
    {
        queue <char>temp;
        int i;char a,b;
        ArcNode *linshifirstarc[LJBWXT.vexnum];
        for(i=0;i<LJBWXT.vexnum;i++)//初始化
        {
            linshifirstarc[i]=LJBWXT.vertices[i].firstarc;
            LJBWXT.vertices[i].visited=0;
        }
        cout<<"输入顶点,以该顶点为起始点广度优先搜索遍历邻接表无向图:";
        A:cin>>a;
        for(i=0;i<LJBWXT.vexnum;i++)
        {
            if(LJBWXT.vertices[i].data==a)
            {
                cout<<a<<"  ";
                LJBWXT_ij(&i,LJBWXT,&a);
                LJBWXT.vertices[i].visited=1;
                temp.push(a);
                break;
            }
        }
        if(i==LJBWXT.vexnum)
        {
            cout<<a<<"不是该邻接表无向图的顶点"<<endl;
            goto A;
        }
        while(!temp.empty())
        {
            b=temp.front();
            LJBWXT_ij(&i,LJBWXT,&b);
            int k;
            while(linshifirstarc[i]!=NULL)
            {
                if(LJBWXT.vertices[linshifirstarc[i]->adjvex].visited==0)
                {
                    cout<<LJBWXT.vertices[linshifirstarc[i]->adjvex].data<<"  ";
                    LJBWXT.vertices[linshifirstarc[i]->adjvex].visited=1;
                    temp.push(LJBWXT.vertices[linshifirstarc[i]->adjvex].data);
                }
                linshifirstarc[i]=linshifirstarc[i]->nextarc;
            }
            temp.pop();
        }
    }
}
void LJJZWXT_jdlj(AMGraph &LJJZWXT)//求邻接矩阵无向图顶点到另一顶点的一条简单路径
{
    if(LJJZWXT.vexnum==0)
    {
        cout<<"没有邻接矩阵无向图"<<endl;
    }
    else
    {
        stack <char>temp;
        int i,k;char a,b,c,d;
        for(i=0;i<LJJZWXT.vexnum;i++)
        {
            LJJZWXT.visited[i]=0;
        }
        cout<<"输入2个顶点:";
        A:cin>>a>>b;
        cout<<a<<"->"<<b<<"的一条简单路径为:";
        for(i=0;i<LJJZWXT.vexnum;i++)
        {
            if(LJJZWXT.vexs[i]==a)
            {
                LJJZWXT_ij(&i,LJJZWXT,&a);
                LJJZWXT.visited[i]=1;
                temp.push(a);
                break;
            }
        }
        if(i==LJJZWXT.vexnum)
        {
            cout<<a<<"不是该邻接矩阵无向图的顶点"<<endl;
            goto A;
        }
        while(!temp.empty())
        {
            c=temp.top();
            LJJZWXT_ij(&i,LJJZWXT,&c);
            for(k=0;k<LJJZWXT.vexnum;k++)
            {
                if(LJJZWXT.arcs[i][k]==1&&LJJZWXT.visited[k]==0)
                {
                    LJJZWXT.visited[k]=1;
                    temp.push(LJJZWXT.vexs[k]);
                    if(LJJZWXT.vexs[k]==b)
                    goto B;
                    break;
                }
            }
            if(k==LJJZWXT.vexnum)
            {
                temp.pop();
            }
        }
        if(temp.empty())
        {
            cout<<a<<b<<"之间没有简单路径"<<endl;
        }
        else
        {
            B:stack <char>temp1;
            while(!temp.empty())
            {
                d=temp.top();
                temp.pop();
                temp1.push(d);
            }
            while(!temp1.empty())//显示temp1栈中元素
            {
                cout<<temp1.top()<<"  ";
                temp1.pop();
            }
        }
    }
}
void LJBWXT_zdlj(ALGraph &LJBWXT)//求邻接表无向图顶点到另一顶点的最短路径
{
    if(LJBWXT.vexnum==0)
    {
        cout<<"没有邻接表无向图"<<endl;
        exit(0);
    }
    else
    {
        int s=0;
        stack <char>temp;
        queue <char>temp1;
        int i;char a,b,c;
        ArcNode *linshifirstarc[LJBWXT.vexnum];
        for(i=0;i<LJBWXT.vexnum;i++)//初始化
        {
            linshifirstarc[i]=LJBWXT.vertices[i].firstarc;
            LJBWXT.vertices[i].visited=0;
            LJBWXT.vertices[i].jiazhang=NULL;
        }
        cout<<"输入2个顶点:";
        A:cin>>a>>c;
        cout<<a<<"->"<<c<<"的最短路径为:";
        for(i=0;i<LJBWXT.vexnum;i++)
        {
            if(LJBWXT.vertices[i].data==a)
            {
                LJBWXT_ij(&i,LJBWXT,&a);
                LJBWXT.vertices[i].visited=1;
                temp1.push(a);
                break;
            }
        }
        if(i==LJBWXT.vexnum)
        {
            cout<<a<<"不是该邻接表无向图的顶点"<<endl;
            goto A;
        }
        while(!temp1.empty())
        {
            b=temp1.front();
            LJBWXT_ij(&i,LJBWXT,&b);
            int k;
            while(linshifirstarc[i]!=NULL)
            {
                if(LJBWXT.vertices[linshifirstarc[i]->adjvex].visited==0)
                {
                    LJBWXT.vertices[linshifirstarc[i]->adjvex].visited=1;
                    temp1.push(LJBWXT.vertices[linshifirstarc[i]->adjvex].data);
                    LJBWXT.vertices[linshifirstarc[i]->adjvex].jiazhang=&LJBWXT.vertices[i];
                    if(LJBWXT.vertices[linshifirstarc[i]->adjvex].data==c)
                    {
                        s=1;
                        goto B;
                    }
                }
                linshifirstarc[i]=linshifirstarc[i]->nextarc;
            }
            temp1.pop();
        }
        if(s==0)
        {
            cout<<a<<c<<"之间没有最短路径"<<endl;
        }
        else
        {
            B:VNode *p=NULL;
            LJBWXT_ij(&i,LJBWXT,&c);
            p=&LJBWXT.vertices[i];
            while(p!=NULL)
            {
                temp.push(p->data);
                p=p->jiazhang;
            }
            while(!temp.empty())//显示temp栈中元素
            {
                cout<<temp.top()<<"  ";
                temp.pop();
            }
        }
    }
}
void menu(AMGraph &LJJZWXT,ALGraph &LJBWXT)
{
    int c,d;
    cout<<"|-----------------------------------------------|"<<endl;
    cout<<"|(1)邻接矩阵无向图创建                          |"<<endl;
    cout<<"|-----------------------------------------------|"<<endl;
    cout<<"|(2)邻接表无向图创建                            |"<<endl;
    cout<<"|-----------------------------------------------|"<<endl;
    cout<<"|(3)邻接矩阵无向图深度优先搜索遍历              |"<<endl;
    cout<<"|-----------------------------------------------|"<<endl;
    cout<<"|(4)邻接矩阵无向图广度优先搜索遍历              |"<<endl;
    cout<<"|-----------------------------------------------|"<<endl;
    cout<<"|(5)邻接表无向图深度优先搜索遍历                |"<<endl;
    cout<<"|-----------------------------------------------|"<<endl;
    cout<<"|(6)邻接表无向图广度优先搜索遍历                |"<<endl;
    cout<<"|-----------------------------------------------|"<<endl;
    cout<<"|(7)求邻接矩阵无向图顶点到另一顶点的一条简单路径|"<<endl;
    cout<<"|-----------------------------------------------|"<<endl;
    cout<<"|(8)求邻接表无向图顶点到另一顶点的最短路径      |"<<endl;
    cout<<"|-----------------------------------------------|"<<endl;
    cout<<"|(9)返回                                        |"<<endl;
    cout<<"|-----------------------------------------------|"<<endl;
    do{
        cin>>c;
        if(c<1||c>9)
        {
            cout<<"(输入有误)(1-9)";
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
            LJJZWXT_create(LJJZWXT);
            break;
        case 2:
            LJBWXT_create(LJBWXT);
            break;
        case 3:
            LJJZWXT_DFS(LJJZWXT);
            break;
        case 4:
            LJJZWXT_BFS(LJJZWXT);
            break;
        case 5:
            LJBWXT_DFS(LJBWXT);
            break;
        case 6:
            LJBWXT_BFS(LJBWXT);
            break;
        case 7:
            LJJZWXT_jdlj(LJJZWXT);
            break;
        case 8:
            LJBWXT_zdlj(LJBWXT);
            break;
        case 9:
            welcome(LJJZWXT,LJBWXT);
            break;
    }
    welcome(LJJZWXT,LJBWXT);
}
void welcome(AMGraph &LJJZWXT,ALGraph &LJBWXT)
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
            menu(LJJZWXT,LJBWXT);
            break;
        case 'N':
            exit(0);
    }
}
main()
{
    AMGraph LJJZWXT;
    ALGraph LJBWXT;
    welcome(LJJZWXT,LJBWXT);
}

