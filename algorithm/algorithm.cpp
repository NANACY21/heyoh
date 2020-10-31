#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<math.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
#include<stack>//栈
#include<queue>//队列,优先队列
#include<algorithm>//堆,sort()库函数
#include<vector>//向量
#define MaxInt 9999//极大值
#define MVNum 100//最大顶点数
#define bag 40//书包的容量(最大能承受bag斤的重量,无需考虑体积问题)
using namespace std;
//算法合集
/*
----------------------------------------------------------------------
顺序表(SXB)
单向非循环链表(DFX) 其生成环节: init + create + display
双向非循环链表(SFX) 其生成环节: init + create + display
单向循环链表(DX)    其生成环节: create + display(create中包含初始化)
双向循环链表(SX)    其生成环节: create + display(create中包含初始化)
顺序栈(SXZ)
链栈(LZ)
顺序队列(SXD)
链队(LD)
顺序二叉树(SXECS)
二叉链表二叉树(ECLBECS)
邻接矩阵无向图(LJJZWXT)
邻接表无向图(LJBWXT)
----------------------------------------------------------------------
*/

/*
----------------------求众数及重数时间复杂度分析----------------------
分解过程时间复杂度:
O(n)
递归求解子问题时间复杂度:
由于把原问题一分为二,所以a=2,a:子问题的个数;子问题占原问题1/b,所以b=2
aT(n/b)    不用写O(..)了
合并时间复杂度:
O(1)
所以递归方程:
T(n)=θ(1)              n=1     θ:同阶 O:最大上限    O(1):不超过常量时间 θ(1):明确就是常量时间
T(n)=O(n)+aT(n/b)+O(1) n>1
因为 n^(logba)=n^(log22)=n,n与分解过程时间复杂度同阶,所以再乘个logn    若不同阶,则看谁的阶大
所以T(n)=O(nlogn)
----------------------------------------------------------------------
*/

/*顺序表存储结构*/
typedef struct
{
    int *elem;//存储空间的基地址
    int length;//表长(当前长度)
    int left;//数组第1个元素下标
    int right;//数组最后1个元素下标
    int mode;//众数
    int time;//众数重数
    int n;//顺序表元素数
    int MIS;//最大子段和
    int MI_left;//最大子段左索引
    int MI_right;//最大子段右索引
}SqList;
/*背包问题存储结构*/
typedef struct thing
{
    string name;//名称
    double weight;//重量(单位:斤)
    double value;//价值(单位:元)
    double unit_weight_value;//单位重量价值(单位:元/斤)
}thing,things[MVNum];
typedef struct
{
    things data;
    int n;//物品数
    double dangqian_weight;//放入书包的物品的总重量;
    double dangqian_value;//放入书包的物品的总价值;
    int left;//数组第1个元素下标
    int right;//数组最后1个元素下标
}Things;
/*n后问题存储结构*/
typedef struct
{
    int n;//皇后个数
    int *result;//解的基地址
    long sum;//可行方案数
}Queen;
/*图的邻接矩阵(顺序)存储结构*/
typedef struct
{
    char vexs[MVNum];//顶点表
    int visited[MVNum];//顶点访问标记数组,与顶点表一一对应
    int arcs[MVNum][MVNum];//邻接矩阵
    int vexnum;//图当前点数
    int arcnum;//图当前边数
    int prev[MVNum];//前驱顶点数组
    int dist[MVNum];//最短距离数组
}AMGraph;
struct Usuall
{
    friend bool operator<(Usuall temp1,Usuall temp2)
    {
        return temp1.length<temp2.length;
    }
    int i;
    int length;
};
/*--------------------------------------------------*/
void SXB_init(SqList &L);
void SXB_create(SqList &L);
void SXB_display(SqList &L);
void SXB_mode_display(SqList &L);
/*--------------------------------------------------*/
void LJJZYXW_ij(int *i,AMGraph &LJJZYXW,char *a);//确定顶点在邻接矩阵有向网中的位置,即顶点数组的下标
void LJJZYXW_a(int *i,AMGraph &LJJZYXW,char *a);
void LJJZYXW_create(AMGraph &LJJZYXW);
/*--------------------------------------------------*/
void my_merge(SqList &L,int left,int mid,int right);
void my_mergesort(SqList &L,int left,int right);
/*--------------------------------------------------*/
int get_time(SqList &L,int left,int right);//返回一个有序数组中中间数出现的次数
void get_mode(SqList &L,int left,int right);
/*--------------------------------------------------*/
void things_create(Things &fruit);
void my_choosesort(Things &fruit);
void my_merge1(Things &fruit,int left,int mid,int right);
void my_mergesort1(Things &fruit,int left,int right);
void add_bag_best(Things &fruit);
/*--------------------------------------------------*/
void get_MIS(SqList &L);//求解一维数组元素最大子段和
/*--------------------------------------------------*/
void Queen_init(Queen &queen);
bool place(Queen &queen,int k);
void backtrack(Queen &queen,int t);
/*--------------------------------------------------*/
void queue_get_SSSP(AMGraph &LJJZYXW);
void priority_queue_get_SSSP(AMGraph &LJJZYXW);
void heap_get_SSSP(AMGraph &LJJZYXW);
/*--------------------------------------------------*/
void menu1();
void menu2(SqList &L,Things &fruit,Queen &queen,AMGraph &LJJZYXW);
/*--------------------------------------------------*/
void SXB_init(SqList &L)
{
    L.elem=new int[MVNum];
    if(!L.elem)
    {
        exit(0);
    }
    L.length=0;
    L.n=0;
}
void SXB_create(SqList &L)
{
    cout<<"你想输入多少数?";
    cin>>L.n;
    cout<<"请输入(按空格键以分隔每一个数,输入完请按回车键)"<<endl;
    for(int i=1;i<=L.n;i++)
    {
        cin>>L.elem[i];
        ++L.length;
    }
    L.left=1;
    L.right=L.length;
    L.mode=0;
    L.time=0;
    L.MIS=0;//一维数组最大子段和须设初值为0
    L.MI_left=1;
    L.MI_right=L.length;
}
void SXB_display(SqList &L)
{
    for(int i=1;i<=L.length;i++)
    {
        cout<<L.elem[i]<<" ";
    }
    cout<<endl;
}
void SXB_mode_display(SqList &L)
{
    cout<<"该集合中的众数是"<<L.mode<<",它的重数为"<<L.time<<"(出现了"<<L.time<<"次)"<<endl;
}
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
void LJJZYXW_a(int *i,AMGraph &LJJZYXW,char *a)
{
    if(LJJZYXW.vexnum==0)
    {
        cout<<"没有邻接矩阵有向网"<<endl;
    }
    else
    {
        for(int j=0;j<LJJZYXW.vexnum;j++)
        {
            if(j==*i)
            {
                *a=LJJZYXW.vexs[j];
            }
        }
    }
}
void LJJZYXW_create(AMGraph &LJJZYXW)
{
    int i,j;
    cout<<"输入顶点数和弧数(按空格键以分隔顶点数和弧数,输入完请按回车键)";
    cin>>LJJZYXW.vexnum>>LJJZYXW.arcnum;
    cout<<"输入顶点(按空格键以分隔每一个顶点,输入完请按回车键)";
    for(i=0;i<LJJZYXW.vexnum;++i)//依次输入点的信息
    {
        cin>>LJJZYXW.vexs[i];
    }
    for(i=0;i<LJJZYXW.vexnum;++i)
    {
        LJJZYXW.visited[i]=0;
    }
    for(i=0;i<LJJZYXW.vexnum;++i)//初始化邻接矩阵,边的权值均置为MaxInt
    {
        for(int j=0;j<LJJZYXW.vexnum;++j)
        {
            LJJZYXW.arcs[i][j]=MaxInt;
        }
    }
    for(int k=0;k<LJJZYXW.arcnum;++k)
    {
        char v1,v2;int w;
        cout<<"输入弧(始点终点)以及这条弧的权值(中间不用按空格)";
        cin>>v1>>v2>>w;
        LJJZYXW_ij(&i,LJJZYXW,&v1);//确定顶点v1在LJJZWXW中的位置,即顶点数组下标
        LJJZYXW_ij(&j,LJJZYXW,&v2);//确定顶点v2在LJJZWXW中的位置,即顶点数组下标
        LJJZYXW.arcs[i][j]=w;//顶点数组下标为i的顶点到顶点数组下标为j的顶点有边
    }
    cout<<"邻接矩阵有向网已创建("<<LJJZYXW.vexnum<<"个顶点,"<<LJJZYXW.arcnum<<"条边)"<<endl;
}
void my_merge(SqList &L,int left,int mid,int right)
{
    int i,j,k;
    i=left;
    j=mid+1;
    k=left;
    int temp[MVNum];
    while(i<=mid&&j<=right)
    {
        if(L.elem[i]<=L.elem[j])
        {
            temp[k++]=L.elem[i++];
        }
        else
        {
            temp[k++]=L.elem[j++];
        }
    }
    while(i<=mid)
    {
        temp[k++]=L.elem[i++];
    }
    while(j<=right)
    {
        temp[k++]=L.elem[j++];
    }
    for(i=1;i<=right;i++)
    {
        L.elem[i]=temp[i];
    }
}
void my_mergesort(SqList &L,int left,int right)
{
    if(left>=right)
    {
        return;
    }
    else
    {
        int mid=(left+right)/2;
        my_mergesort(L,left,mid);
        my_mergesort(L,mid+1,right);
        my_merge(L,left,mid,right);
    }
}
int get_time(SqList &L,int left,int right)//数组中中间数出现的次数
{
    int mid=(left+right)/2;//mid为中间数的下标
    int i,counts=0;
    for(i=left;i<=right;i++)
    {
        if(L.elem[i]==L.elem[mid])
        {
            counts++;
        }
    }
    return counts;
}
void get_mode(SqList &L,int left,int right)
{
    int b=(left+right)/2;//b为数组中间数的下标
    int c=get_time(L,left,right);//c为中间数(a[b])的重数
    if(c>L.time)//如果中间数的重数大于之前的众数//初始化重数和众数
    {
        L.time=c;
        L.mode=L.elem[b];//该数组的众数更新为中间数
    }
    if((right-b)>L.time)//如果数组右边元素个数大于中间数的重数,则右边可能出现众数,右递归
    {
        get_mode(L,b+1,right);
    }
    if(b-left+1>L.time)//如果数组左边元素个数大于中间数的重数,则左边可能出现众数,左递归
    {
        get_mode(L,1,b);
    }
}
void things_create(Things &fruit)
{
    cout<<"有多少种物品?";
    cin>>fruit.n;
    cout<<endl;
    for(int i=0;i<fruit.n;i++)
    {
        cout<<"第"<<i+1<<"种物品名称:";cin>>fruit.data[i].name;
        cout<<"斤数:";cin>>fruit.data[i].weight;
        cout<<"这"<<fruit.data[i].weight<<"斤"<<fruit.data[i].name<<"的价值(元)";cin>>fruit.data[i].value;
        cout<<"------------------------------------------"<<endl;
        fruit.data[i].unit_weight_value=fruit.data[i].value/fruit.data[i].weight;

    }
    fruit.dangqian_weight=0;
    fruit.dangqian_value=0;
    fruit.left=0;
    fruit.right=fruit.n-1;
}
void my_choosesort(Things &fruit)
{
    int i,j,k;
    thing temp;
    for(i=0;i<fruit.n-1;i++)
    {
        k=i;
        for(j=i+1;j<fruit.n;j++)
        {
            if(fruit.data[j].unit_weight_value>fruit.data[k].unit_weight_value)
            {
                k=j;
            }
        }
        if(k!=i)//i!=j
        {
            temp=fruit.data[k];
            fruit.data[k]=fruit.data[i];
            fruit.data[i]=temp;
        }
    }
}
void my_merge1(Things &fruit,int left,int mid,int right)
{
    int i,j,k;
    i=left;
    j=mid+1;
    k=left;
    thing temp[MVNum];
    while(i<=mid&&j<=right)
    {
        if(fruit.data[i].unit_weight_value>fruit.data[j].unit_weight_value)
        {
            temp[k]=fruit.data[i];
            i++;
        }
        else
        {
            temp[k]=fruit.data[j];
            j++;
        }
        k++;
    }
    while(i<=mid)
    {
        temp[k]=fruit.data[i];
        k++;
        i++;
    }
    while(j<=right)
    {
        temp[k]=fruit.data[j];
        k++;
        j++;
    }
    for(i=left;i<=right;i++)
    {
        fruit.data[i]=temp[i];
    }
}
void my_mergesort1(Things &fruit,int left,int right)
{
    if(left>=right)
    {
        return;
    }
    else
    {
        int mid=(left+right)/2;
        my_mergesort1(fruit,left,mid);
        my_mergesort1(fruit,mid+1,right);
        my_merge1(fruit,left,mid,right);
    }
}
void add_bag_best(Things &fruit)
{
    int i=0;
    cout<<"最优(总价值最大)装包方式为:"<<endl;
    cout<<"装";
    while(fruit.dangqian_weight<=bag&&i<fruit.n)
    {
        if(fruit.data[i].weight<=bag-fruit.dangqian_weight)
        {
            fruit.dangqian_weight=fruit.dangqian_weight+fruit.data[i].weight;
            fruit.dangqian_value=fruit.dangqian_value+fruit.data[i].value;
            cout<<fruit.data[i].weight<<"斤"<<fruit.data[i].name<<",";
            i++;
        }
        else
        {
            fruit.dangqian_value=fruit.dangqian_value+fruit.data[i].unit_weight_value*(bag-fruit.dangqian_weight);
            cout<<bag-fruit.dangqian_weight<<"斤"<<fruit.data[i].name<<",";
            fruit.dangqian_weight=bag;
            i++;
        }
    }
    cout<<"该书包内物品总价值为:"<<fruit.dangqian_value<<"元"<<endl;
}
void get_MIS(SqList &L)//求解一维数组元素最大子段和
{
    L.MIS=0;
    int i,temp_MIS=0,temp_MI_left;
    for(i=1;i<=L.length;i++)
    {
        if(temp_MIS>0)
        {
            temp_MIS=temp_MIS+L.elem[i];
        }
        else
        {
            temp_MIS=L.elem[i];
            temp_MI_left=i;
        }
        if(temp_MIS>L.MIS)
        {
            L.MIS=temp_MIS;
            L.MI_left=temp_MI_left;
            L.MI_right=i;
        }
    }
    cout<<"该集合中最大子段和为"<<L.MIS<<",最大子段左索引为"<<L.MI_left<<",右索引为"<<L.MI_right<<endl;
}
void Queen_init(Queen &queen)
{
    cout<<"----n*n格棋盘放置n个彼此不受攻击的皇后----"<<endl;
    cout<<"输入n(n必须大于等于4)";
    cin>>queen.n;
    queen.result=new int[queen.n+1];
    queen.sum=0;
    if(!queen.result)
    {
        exit(0);
    }
    cout<<"------------------------------------------"<<endl;
}
bool place(Queen &queen,int k)
{
    for(int i=1;i<k;i++)
    {
        if((abs(k-i)==abs(queen.result[k]-queen.result[i]))||(queen.result[i]==queen.result[k]))
        {
            return false;
        }
    }
    return true;
}
void backtrack(Queen &queen,int t)
{
    if(t>queen.n)
    {
        queen.sum++;
        cout<<"第"<<queen.sum<<"种可行方案"<<endl<<endl;
        for(int i=1;i<=queen.n;i++)
        {
            cout<<"第"<<i<<"个皇后放在第"<<i<<"行第"<<queen.result[i]<<"列"<<endl;
        }
        cout<<"------------------------------------------"<<endl;
    }
    else
    {
        for(int i=1;i<=queen.n;i++)
        {
            queen.result[t]=i;//第t个皇后放第i列
            if(place(queen,t))
            {
                backtrack(queen,t+1);
            }
        }
    }
}
void queue_get_SSSP(AMGraph &LJJZYXW)
{
    char a,b;
    int i,j;
    Usuall E,N;
    queue <Usuall>temp;//队列
    cout<<"---求源点到有向网其它所有顶点的最短路径---"<<endl;
    cout<<"输入源点和终点(中间不用按空格)";
    cin>>a>>b;
    LJJZYXW_ij(&i,LJJZYXW,&a);
    for(j=0;j<LJJZYXW.vexnum;j++)
    {
        LJJZYXW.dist[j]=MaxInt;
    }
    E.i=i;
    E.length=0;//源点到当前点的距离
    LJJZYXW.dist[i]=0;//源点到下标为i的点的路径长度,自己到自己为0
    temp.push(E);
    while(!temp.empty())
    {
        E=temp.front();
        temp.pop();
        if(LJJZYXW.dist[E.i]<E.length)//LJJZYXW.length表示源点到当前出队的点的路径长度
        {
            continue;//则不用更新
        }
        for(j=0;j<LJJZYXW.vexnum;j++)//
        {
            if((LJJZYXW.arcs[E.i][j]<MaxInt)&&(E.length+LJJZYXW.arcs[E.i][j]<LJJZYXW.dist[j]))
            {
                LJJZYXW.dist[j]=E.length+LJJZYXW.arcs[E.i][j];
                LJJZYXW.prev[j]=E.i;
                N.i=j;
                N.length=LJJZYXW.dist[j];
                temp.push(N);
            }
        }
    }
    LJJZYXW_ij(&i,LJJZYXW,&b);
    cout<<a<<"->"<<b<<"的最短路径为"<<LJJZYXW.dist[i]<<endl;
}
void priority_queue_get_SSSP(AMGraph &LJJZYXW)
{
    char a,b;
    int i,j;
    Usuall E,N;
    priority_queue <Usuall>temp;//优先队列,使用优先队列需设置优先级
    cout<<"---求源点到有向网其它所有顶点的最短路径---"<<endl;
    cout<<"输入源点和终点(中间不用按空格)";
    cin>>a>>b;
    LJJZYXW_ij(&i,LJJZYXW,&a);
    for(int k=0;k<LJJZYXW.vexnum;k++)
    {
        LJJZYXW.dist[k]=MaxInt;
    }
    E.i=i;
    E.length=0;
    LJJZYXW.dist[i]=0;//源点到下标为i的点的路径长度,自己到自己为0
    temp.push(E);
    while(!temp.empty())
    {
        E=temp.top();
        temp.pop();
        if(LJJZYXW.dist[E.i]<E.length)//LJJZYXW.length表示源点到当前出队的点的路径长度
        {
            continue;//则不用更新
        }
        for(j=0;j<LJJZYXW.vexnum;j++)//
        {
            if((LJJZYXW.arcs[E.i][j]<MaxInt)&&(E.length+LJJZYXW.arcs[E.i][j]<LJJZYXW.dist[j]))
            {
                LJJZYXW.dist[j]=E.length+LJJZYXW.arcs[E.i][j];
                LJJZYXW.prev[j]=E.i;
                N.i=j;
                N.length=LJJZYXW.dist[j];
                temp.push(N);//入队后自动制动位置
            }
        }
    }
    LJJZYXW_ij(&i,LJJZYXW,&b);
    cout<<"最短路径为"<<LJJZYXW.dist[i]<<endl;
}
void heap_get_SSSP(AMGraph &LJJZYXW)
{
    char a,b;
    int i,j;
    Usuall E,N;
    vector <Usuall>temp;//创建一个空的向量
    cout<<"---求源点到有向网其它所有顶点的最短路径---"<<endl;
    cout<<"输入源点和终点(中间不用按空格)";
    cin>>a>>b;
    LJJZYXW_ij(&i,LJJZYXW,&a);
    for(int k=0;k<LJJZYXW.vexnum;k++)
    {
        LJJZYXW.dist[k]=MaxInt;
    }
    E.i=i;
    E.length=0;
    LJJZYXW.dist[i]=0;//源点到下标为i的点的路径长度,自己到自己为0
    temp.push_back(E);
    while(!temp.empty())
    {
        E=temp.front();
        temp.erase(temp.begin());
        if(LJJZYXW.dist[E.i]<E.length)//LJJZYXW.length表示源点到当前出队的点的路径长度
        {
            continue;//则不用更新
        }
        for(j=0;j<LJJZYXW.vexnum;j++)//
        {
            if((LJJZYXW.arcs[E.i][j]<MaxInt)&&(E.length+LJJZYXW.arcs[E.i][j]<LJJZYXW.dist[j]))
            {
                LJJZYXW.dist[j]=E.length+LJJZYXW.arcs[E.i][j];
                LJJZYXW.prev[j]=E.i;
                N.i=j;
                N.length=LJJZYXW.dist[j];
                temp.push_back(N);
            }
        }
        /*优先队列可以用堆来实现*/
        make_heap(temp.begin(),temp.end());//把temp向量中所有元素弄成一个堆,默认大根堆
        sort_heap(temp.begin(),temp.end());//对已成为堆的temp向量做堆排序
    }
    LJJZYXW_ij(&i,LJJZYXW,&b);
    cout<<"最短路径为"<<LJJZYXW.dist[i]<<endl;
}
void menu1()
{
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|     (1)创建一维数组                    |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|     (2)创建邻接矩阵有向网              |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|        分治算法                        |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|     (3)归并排序                        |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|     (4)求众数及其重数                  |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|        贪心算法                        |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|     (5)背包问题(选择排序)              |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|     (6)背包问题(归并排序)              |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|        动态规划                        |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|     (7)求解最大子段和                  |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|        回溯算法                        |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|     (8)n后问题                         |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|        分支限界算法                    |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|     (9)单源最短路径问题(队列式)        |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|    (10)单源最短路径问题(优先队列式)    |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|    (11)单源最短路径问题(堆式)          |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|    (12)退出                            |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
}
void menu2(SqList &L,Things &fruit,Queen &queen,AMGraph &LJJZYXW)
{
    int b,c;
    cout<<"------------------------------------------"<<endl;
    cout<<"选择功能";
    do{
        cin>>b;
        if(b<1||b>12)
        {
            cout<<"(输入有误)(1-12)";
            c=1;
            getchar();
        }
        else
        {
            c=0;
        }
    }while(c==1);
    cout<<"------------------------------------------"<<endl;
    switch(b)
    {
        case 1:
            SXB_init(L);
            SXB_create(L);
            break;
        case 2:
            LJJZYXW_create(LJJZYXW);
            break;
        case 3:
            my_mergesort(L,L.left,L.right);
            SXB_display(L);
            break;
        case 4:
            my_mergesort(L,L.left,L.right);
            get_mode(L,L.left,L.right);
            SXB_mode_display(L);
            break;
        case 5:
            things_create(fruit);
            my_choosesort(fruit);
            add_bag_best(fruit);
            break;
        case 6:
            things_create(fruit);
            my_mergesort1(fruit,fruit.left,fruit.right);
            add_bag_best(fruit);
            break;
        case 7:
            get_MIS(L);
            break;
        case 8:
            Queen_init(queen);
            backtrack(queen,1);
            break;
        case 9:
            queue_get_SSSP(LJJZYXW);
            break;
        case 10:
            priority_queue_get_SSSP(LJJZYXW);
            break;
        case 11:
            heap_get_SSSP(LJJZYXW);
            break;
        case 12:
            exit(0);
    }
    menu2(L,fruit,queen,LJJZYXW);
}
int main()
{
    SqList L;
    Things fruit;
    Queen queen;
    AMGraph LJJZYXW;
    menu1();
    menu2(L, fruit, queen, LJJZYXW);
    return 0;
}
