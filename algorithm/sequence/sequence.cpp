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
/*排序算法合集*/
/*顺序表存储结构*/
typedef struct
{
    int *elem;//存储空间的基地址
    int length;//表长(当前长度)
    int left;//数组第一个元素下标
    int right;//数组最后一个元素下标
    int mode;//众数
    int time;//众数重数
    int n;//顺序表元素数
    int MIS;//最大子段和
    int MI_left;//最大子段左索引
    int MI_right;//最大子段右索引
}SqList;
/*--------------------------------------------------*/
void SXB_init(SqList &L);
void SXB_create(SqList &L);
void SXB_display(SqList &L);
/*--------------------------------------------------*/
void menu1();
void menu2(SqList &L);
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
void menu1()
{
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|            (1)创建一维数组             |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|        内部排序                        |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|          插入排序                      |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|            (2)直接插入排序             |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|            (3)折半插入排序             |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|            (4)希尔排序                 |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|          交换排序                      |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|            (5)冒泡排序                 |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|            (6)快速排序                 |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|          选择排序                      |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|            (7)简单选择排序             |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|            (8)树形选择排序             |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|            (9)堆排序                   |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|          归并排序                      |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|            (10)2-路归并排序            |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|          分配排序                      |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|            (11)基数排序                |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|        外部排序                        |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
    cout<<"|            (12)退出                    |"<<endl;
    cout<<"|----------------------------------------|"<<endl;
}
void menu2(SqList &L)
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
            my_insertsort(L);
            break;
        case 3:
            my_binsertsort(L);
            break;
        case 4:
            my_shellsort(L,dt,(int)(log(L.n+1)/log(2)));
            break;
        case 5:
            my_bubblesort(L);
            break;
        case 6:
            my_quicksort(L,L.left,L.right);
            break;
        case 7:
            my_selectsort(L);
            break;
        case 8:

            break;
        case 9:
            my_heapsort(L);
            break;
        case 10:
            my_mergesort(L,L.left,L.right);
            break;
        case 11:

            break;
        case 12:
            exit(0);
    }
    menu2(L);
}
main()
{
    SqList L;
    menu1();
    menu2(L);
}
