//指针,赋值,得空吗?//shiyan6yiok,shiyan8栈ok,文件未ok DL,GDSJ,KSYD
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
typedef struct jingdian
{
    string name;
    string jianjie;
}JINGDIAN;
typedef struct//图的邻接矩阵(顺序)存储结构
{
    JINGDIAN vexs[MVNum];//顶点表
    int visited[MVNum];//顶点访问标记数组,与顶点表一一对应
    int arcs[MVNum][MVNum];//邻接矩阵
    int vexnum;//图当前点数
    int arcnum;//图当前边数
}AMGraph;
//----------Dijkstra算法辅助数据结构----------
int S[MVNum];//辅助数组S,用于记录从源点到终点是否已被确定最短路径长度,1表示确定,0表示尚未确定
int Path_Dijkstra[MVNum];//辅助数组Path,用于记录从源点到终点的当前最短路径上终点的直接前驱顶点序号
int D_Dijkstra[MVNum];//辅助数组D,用于记录从源点到终点的当前最短路径长度
//----------Floyd算法辅助数据结构-------------
int Path_Floyd[MVNum][MVNum];//辅助二维数组Path,Path[i][j],用于记录最短路径上顶点(下标为j)的前一顶点的序号
int D_Floyd[MVNum][MVNum];//辅助二维数组D,D[i][j],用于记录顶点(下标为i)和顶点(下标为j)之间的最短路径长度
//--------------------------------------------
void cunrufile(AMGraph &LJJZYXW);
void duchufile(AMGraph &LJJZYXW);
void LJJZYXW_ij(int *i,AMGraph &LJJZYXW,string *a);//确定顶点在邻接矩阵有向网中的位置,即顶点数组的下标
void LJJZYXWchuangjian(AMGraph &LJJZYXW);
void Dijkstra(AMGraph &LJJZYXW);
void Floyd(AMGraph &LJJZYXW);
void menu1();
void menu2(AMGraph &LJJZYXW);
void menu3(AMGraph &LJJZYXW);
void cunrufile(AMGraph &LJJZYXW)
{
    FILE *a=NULL;//a=文件的地址值
    if((a=fopen("D:\\校园.txt","wb"))==NULL)//判断文件是否成功打开(文件名:后缀表达式)
    {
        //cout<<"打开.txt格式的演示失败!"<<endl
        cout<<"没有文件"<<endl;
        exit(0);
    }
    fwrite(&LJJZYXW,sizeof(AMGraph),1,a);//向文件中写入数据
    fclose(a);//关闭由函数fopen()打开的a指向的文件
    cout<<"已将校园存入文件"<<endl;
}
void duchufile(AMGraph &LJJZYXW)
{
    FILE *a=NULL;
    a=fopen("D:\\校园.txt","rb");
    if((a=fopen("D:\\校园.txt","r"))==NULL)//判断文件是否成功打开(文件名:后缀表达式)
    {
        cout<<"没有文件"<<endl;
        exit(0);
        //cout<<"打开.txt格式的演示失败!"<<endl
    }
    fread(&LJJZYXW,sizeof(AMGraph),1,a);//读文件中数据到结构体
    fclose(a);
}
void LJJZYXW_ij(int *i,AMGraph &LJJZYXW,string *a)//确定顶点在邻接矩阵有向图中的位置,即顶点数组的下标
{
    if(LJJZYXW.vexnum==0)
    {
        cout<<"没有邻接矩阵有向网"<<endl;
    }
    else
    {
        for(int j=0;j<LJJZYXW.vexnum;j++)
        {
            if(LJJZYXW.vexs[j].name==*a)
            {
                *i=j;
            }
        }
    }
}
void LJJZYXWchuangjian(AMGraph &LJJZYXW)
{
    int i,j;
    cout<<"-------------校园创建-------------"<<endl;
    cout<<"输入该校园景点数:";
    cin>>LJJZYXW.vexnum;
    cout<<"输入该校园路径数(景点间相邻接即为1条路径):";
    cin>>LJJZYXW.arcnum;
    for(int i=0;i<LJJZYXW.vexnum;++i)//依次输入点的信息
    {
        cout<<"输入景点:";
        cin>>LJJZYXW.vexs[i].name;
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
        string v1,v2;
        int w;
        cout<<"输入路径起点:";
        cin>>v1;
        cout<<"输入路径终点:";
        cin>>v2;
        cout<<"输入经过这条路径的时间(单位:/分钟):";
        cin>>w;
        LJJZYXW_ij(&i,LJJZYXW,&v1);//确定顶点v1在LJJZWXW中的位置,即顶点数组下标
        LJJZYXW_ij(&j,LJJZYXW,&v2);//确定顶点v2在LJJZWXW中的位置,即顶点数组下标
        LJJZYXW.arcs[i][j]=w;//顶点数组下标为i的顶点到顶点数组下标为j的顶点有边
    }
    cout<<"--校园已创建("<<LJJZYXW.vexnum<<"个景点,"<<LJJZYXW.arcnum<<"条路径)--"<<endl;
    cunrufile(LJJZYXW);//把校园存入文件
}
void Dijkstra(AMGraph &LJJZYXW)
{
    string a,b;
    int i,j,k,l,Min;
    cout<<"输入1个景点,"<<endl;
    cout<<"求该景点到其它所有景点的最短路径:";
    cin>>a;
    for(i=0;i<LJJZYXW.vexnum;i++)
    {
        if(LJJZYXW.vexs[i].name==a)
        {
            break;
        }
    }
    if(i==LJJZYXW.vexnum)
    {
        cout<<"没有此景点"<<endl;
        menu3(LJJZYXW);
    }
    LJJZYXW_ij(&j,LJJZYXW,&a);
    for(i=0;i<LJJZYXW.vexnum;i++)
    {
        S[i]=0;//S初始为空集
        D_Dijkstra[i]=LJJZYXW.arcs[j][i];
        if(D_Dijkstra[i]<MaxInt)
        {
            Path_Dijkstra[i]=j;
        }
        else
        {
            Path_Dijkstra[i]=-1;
        }
    }
    S[j]=1;
    D_Dijkstra[j]=0;
    for(k=1;k<LJJZYXW.vexnum;k++)
    {
        Min=MaxInt;
        for(l=0;l<LJJZYXW.vexnum;l++)
        {
            if(S[l]==0&&D_Dijkstra[l]<Min)
            {
                i=l;
                Min=D_Dijkstra[l];
            }
        }
        S[i]=1;
        for(l=0;l<LJJZYXW.vexnum;l++)
        {
            if(S[l]==0&&(D_Dijkstra[i]+LJJZYXW.arcs[i][l]<D_Dijkstra[l]))
            {
                D_Dijkstra[l]=D_Dijkstra[i]+LJJZYXW.arcs[i][l];
                Path_Dijkstra[l]=i;
            }
        }
    }//---------------------------------------------
    stack <int>linshi;
    cout<<"输入终点:";
    cin>>b;
    for(i=0;i<LJJZYXW.vexnum;i++)
    {
        if(LJJZYXW.vexs[i].name==b)
        {
            break;
        }
    }
    if(i==LJJZYXW.vexnum)
    {
        cout<<"没有此景点"<<endl;
        menu3(LJJZYXW);
    }
    LJJZYXW_ij(&i,LJJZYXW,&b);
    linshi.push(i);
    while(Path_Dijkstra[i]!=-1)
    {
        i=Path_Dijkstra[i];
        linshi.push(i);
    }
    while(!linshi.empty())
    {
        i=linshi.top();
        cout<<LJJZYXW.vexs[i].name<<"  ";
        linshi.pop();
    }
}
void Floyd(AMGraph &LJJZYXW)
{
    int i,j,k;
    string a,b;
    for(i=0;i<LJJZYXW.vexnum;++i)
    {
        for(j=0;j<LJJZYXW.vexnum;++j)
        {
            D_Floyd[i][j]=LJJZYXW.arcs[i][j];
            if(D_Floyd[i][j]<MaxInt&&i!=j)
            {
                Path_Floyd[i][j]=i;
            }
            else
            {
                Path_Floyd[i][j]=-1;
            }
        }
    }
    for(k=0;k<LJJZYXW.vexnum;++k)
    {
        for(i=0;i<LJJZYXW.vexnum;++i)
        {
            for(j=0;j<LJJZYXW.vexnum;++j)
            {
                if(D_Floyd[i][k]+D_Floyd[k][j]<D_Floyd[i][j])
                {
                    D_Floyd[i][j]=D_Floyd[i][k]+D_Floyd[k][j];
                    Path_Floyd[i][j]=Path_Floyd[k][j];
                }
            }
        }
    }//-----------------------------------------------
    stack <int>linshi;
    cout<<"输入起点:";
    cin>>a;
    cout<<"输入终点:";
    cin>>b;
    LJJZYXW_ij(&i,LJJZYXW,&a);
    LJJZYXW_ij(&j,LJJZYXW,&b);
    linshi.push(j);
    while(j!=i)
    {
        j=Path_Floyd[i][j];
        linshi.push(j);
    }
    while(!linshi.empty())
    {
        i=linshi.top();
        cout<<LJJZYXW.vexs[i].name<<"  ";
        linshi.pop();
    }
}
void menu1()
{
    cout<<"|---------------------------------------|"<<endl;
    cout<<"|              校园导游程序             |"<<endl;
    cout<<"|---------------------------------------|"<<endl;
    cout<<"|     (1)景点信息查询                   |"<<endl;
    cout<<"|---------------------------------------|"<<endl;
    cout<<"|     (2)校门口到其他景点的路经查询     |"<<endl;
    cout<<"|---------------------------------------|"<<endl;
    cout<<"|     (3)校园各景点间的路经查询         |"<<endl;
    cout<<"|---------------------------------------|"<<endl;
    cout<<"|     (4)返回                           |"<<endl;
    cout<<"|---------------------------------------|"<<endl;
}
void menu2(AMGraph &LJJZYXW)
{
    int a,b;
    do{
        cin>>a;
        if(a<1||a>4)
        {
            cout<<"(输入有误)(1-4)";
            b=1;
            getchar();
        }
        else
        {
            b=0;
        }
    }while(b==1);
    switch(a)
    {
        case 1:

            break;
        case 2:
            Dijkstra(LJJZYXW);
            break;
        case 3:
            Floyd(LJJZYXW);
            break;
        case 4:
            exit(0);
            break;
    }
    cout<<endl;
    menu3(LJJZYXW);
}
void menu3(AMGraph &LJJZYXW)
{
    char a,b;
    cout<<"继续?(y or n)";
    do
    {
        cin>>b;
        if(b!='y'&&b!='n')
        {
            cout<<"(输入有误)(y or n)";
            a='y';
            getchar();
        }
        else
        {
            a=0;
        }
    }while(a=='y');
    switch(b)
    {
        case 'y':
            menu2(LJJZYXW);
            break;
        case 'n':
            exit(0);
    }
}
main()
{
    AMGraph LJJZYXW,linshiLJJZYXW;
    char a,b;
    menu1();
    cout<<"选取文件中的校园?(y or n)";
    do
    {
        cin>>b;
        if(b!='y'&&b!='n')
        {
            cout<<"(输入有误)(y or n)";
            a='y';
            getchar();
        }
        else
        {
            a=0;
        }
    }while(a=='y');
    switch(b)
    {
        case 'y':
            duchufile(linshiLJJZYXW);
            cout<<linshiLJJZYXW.vexs[0].name<<endl;
            //menu2(linshiLJJZYXW);
            break;
        case 'n':
            LJJZYXWchuangjian(LJJZYXW);
            menu2(LJJZYXW);
            break;
    }
}
