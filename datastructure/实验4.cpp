#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
using namespace std;
#define MAXSIZE 100
typedef struct//顺序栈存储结构
{
    char *top;//栈顶指针
    char *base;//栈底指针
    int stacksize;//栈可用的最大容量
}SqStack;
typedef struct StackNode//链栈存储结构
{
    char data;
    StackNode *next;
}StackNode,*LinkStack;
typedef struct//顺序队列存储结构(顺序队列逻辑上看成一个环,故顺序队列是循环队列)
{
    int *base;//存储空间的基地址
    int frontt;//头指针
    int rear;//尾指针
}SqQueue;
typedef struct QNode//链队存储结构(带头结点的单向循环链表,不同于教材)
{
    int data;
    QNode *next;
}QNode,*QueuePtr;
void SXZ_init(SqStack &SXZ);
void SXZruzhan(SqStack &SXZ);
void SXZ_create(SqStack &LZ,int n);
void SXZ_display(SqStack &SXZ);
void SXZchuzhan(SqStack &SXZ);
int SXZyss(SqStack &SXZ);
void LZ_init(LinkStack &LZ);
void LZruzhan(LinkStack &LZ);
void LZ_create(LinkStack &LZ);
void LZ_display(LinkStack &LZ);
void LZchuzhan(LinkStack &LZ);
int LZjds(LinkStack &LZ);
void SXD_init(SqQueue &SXD);
void SXDrudui(SqQueue &SXD);
void SXD_display(SqQueue &SXD);
void SXDchudui(SqQueue &SXD);
int SXDyss(SqQueue &SXD);//顺序队列元素数(顺序队列长度)
void LD_init(QueuePtr &tail);
void LD_rudui(QueuePtr &tail);
void LD_chudui(QueuePtr &tail,int &arg0);
void LD_display(QueuePtr &tail);//带头结点的单向循环链表的遍历
bool LD_empty(QueuePtr &tail);
void SXDxx(SqStack &SXZ1,SqStack &SXZ2,LinkStack &LZ1,LinkStack &LZ2,SqQueue &SXD,QueuePtr &tail,int n);
void LDxx(SqStack &SXZ1,SqStack &SXZ2,LinkStack &LZ1,LinkStack &LZ2,SqQueue &SXD,QueuePtr &tail,int n);
void panduan(LinkStack &LZ1,LinkStack &LZ2);
void saomiao(SqStack &SXZ1,SqStack &SXZ2);
void menu(SqStack &SXZ1,SqStack &SXZ2,LinkStack &LZ1,LinkStack &LZ2,SqQueue &SXD,QueuePtr &tail,int n);
void welcome(SqStack &SXZ1,SqStack &SXZ2,LinkStack &LZ1,LinkStack &LZ2,SqQueue &SXD,QueuePtr &tail,int n);
void SXZ_init(SqStack &SXZ)
{
    SXZ.base=new char[MAXSIZE];//顺序栈栈底指针存整个顺序栈的地址
    if(!SXZ.base)//申请失败
    {
        exit(0);
    }
    SXZ.top=SXZ.base;//初始化栈顶指针
    SXZ.stacksize=MAXSIZE;
}
void SXZruzhan(SqStack &SXZ)
{
    char p;
    if(SXZ.top-SXZ.base==SXZ.stacksize)
    {
        cout<<"该顺序栈已满"<<endl;
        exit(0);
    }
    cout<<"输入该结点的数据:";
    cin>>p;
    *SXZ.top=p;SXZ.top++;//*SXZ.top++=p;
}
void SXZ_create(SqStack &SXZ,int n)
{
    cout<<"你想向该顺序栈栈中添加多少结点?";cin>>n;
    while(n--)
    {
        SXZruzhan(SXZ);
    }
}
void SXZ_display(SqStack &SXZ)
{
    char *p;p=SXZ.base;
    if(SXZ.base==SXZ.top)
    {
        cout<<"该顺序栈为空"<<endl;
        exit(0);
    }
    while(p!=SXZ.top)
    {
        cout<<*p;
        p++;////
    }
    cout<<endl;
}
void SXZchuzhan(SqStack &SXZ)
{
    if(SXZ.base==SXZ.top)
    {
        exit(0);
    }
    SXZ.top--;
}
int SXZyss(SqStack &SXZ)
{
    if(SXZ.base==SXZ.top)
    {
        exit(0);
    }
    return SXZ.top-SXZ.base;
}
void LZ_init(LinkStack &LZ)
{
    LZ=NULL;//不设头结点
}
void LZruzhan(LinkStack &LZ)
{
    StackNode *p;
    p=new StackNode;
    cout<<"输入该结点的数据:";
    cin>>p->data;
    p->next=LZ;
    LZ=p;
}
void LZ_create(LinkStack &LZ,int n)
{
    cout<<"你想向该链栈中添加多少结点?";cin>>n;
    while(n--)
    {
        LZruzhan(LZ);
    }
}
void LZ_display(LinkStack &LZ)
{
    StackNode *linshiLZ;
    linshiLZ=LZ;
    while(linshiLZ!=NULL)
    {
        cout<<linshiLZ->data;
        linshiLZ=linshiLZ->next;
    }
    cout<<endl;
}
void LZchuzhan(LinkStack &LZ)
{
    StackNode *p;
    if(LZ==NULL)
    {
        exit(0);
    }
    p=LZ;
    LZ=LZ->next;
    delete p;
}
int LZjds(LinkStack &LZ)
{
    int i=0;
    StackNode *p;p=LZ;
    while(p!=NULL)
    {
        i++;
        p=p->next;
    }
    return i;
}
void SXD_init(SqQueue &SXD)
{
    SXD.base=new int[MAXSIZE];//为队列分配一个最大容量为MAXSIZE的数组空间
    if(!SXD.base)//存储分配失败
    {
        exit(0);
    }
    SXD.frontt=SXD.rear=0;//头指针和尾指针置为零,队列为空
}
void SXDrudui(SqQueue &SXD)
{
    int p;
    if((SXD.rear+1)%MAXSIZE==SXD.frontt)//尾指针在循环意义上加1后等于头指针,表明队满
    {
        cout<<"该顺序队列已满"<<endl;
        exit(0);
    }
    cout<<"输入该结点的数据:";
    cin>>p;
    SXD.base[SXD.rear]=p;//新元素插入队尾
    SXD.rear=(SXD.rear+1)%MAXSIZE;//队尾指针加1
}
void SXD_display(SqQueue &SXD)
{//else和exit(0)有你没我
    int p;
    if(SXD.frontt==SXD.rear)
    {
        cout<<"该顺序队列为空"<<endl;
        //exit(0);
    }
    else
    {
        p=SXD.frontt;
        for(int i=0;i<(SXD.rear-SXD.frontt+MAXSIZE)%MAXSIZE;i++)
        {
            cout<<SXD.base[p]<<"  ";
            p++;
        }
        cout<<endl;
    }
}
void SXDchudui(SqQueue &SXD)
{
    if(SXD.frontt==SXD.rear)
    {
        cout<<"该顺序队列为空"<<endl;
        exit(0);
    }
    SXD.frontt=(SXD.frontt+1)%MAXSIZE;//队头指针加1
}
int SXDyss(SqQueue &SXD)//顺序队列元素个数(顺序队列长度)
{
    return (SXD.rear-SXD.frontt+MAXSIZE)%MAXSIZE;
}
void LD_init(QueuePtr &tail)
{
    tail=new QNode;
    tail->next=tail;
}
void LD_rudui(QueuePtr &tail)
{
    if(tail==NULL)
    {
        cout<<"没有头结点"<<endl;
        exit(0);
    }
    QNode *p=new QNode;
    p->next=NULL;
    cout<<"输入该结点的数据:";
    cin>>p->data;
    p->next=tail->next;
    tail->next=p;
    tail=p;
}
void LD_chudui(QueuePtr &tail,int &arg0)
{
    QNode *p;
    if(tail==NULL)//如果没有头结点
    {
        cout<<"没有头结点"<<endl;
        exit(0);
    }
    if(tail->next==tail)//如果只有头结点
    {
        cout<<"该链队为空"<<endl;
    }
    else if(tail->next->next==tail)
    {
        arg0=tail->data;
        p=tail->next;
        p->next=p;
        delete p;
        tail=p;
    }
    else
    {
        p=tail->next->next;
        arg0=p->data;
        tail->next->next=p->next;
        delete p;
    }
}
void LD_display(QueuePtr &tail)//带头结点的单向循环链表的遍历
{
    if(tail==NULL)
    {
        cout<<"没有头结点"<<endl;
        exit(0);
    }
    QNode *p=tail->next->next;
    if(tail->next==tail)//若只有头结点
    {
        cout<<"该链队为空"<<endl;
    }
    else
    {
        while(p!=tail)
        {
            cout<<p->data<<"  ";
            p=p->next;//指针后移
        }
        if(p==tail)
        {
            cout<<p->data;
        }
        cout<<endl;
    }
}
bool LD_empty(QueuePtr &tail)
{
    if(tail->next==tail)//如果链队为空则返回true
    {
        return true;
    }
    else
    {
        return false;
    }
}
void SXDxx(SqStack &SXZ1,SqStack &SXZ2,LinkStack &LZ1,LinkStack &LZ2,SqQueue &SXD,QueuePtr &tail,int n)
{
    int c,d;
    cout<<"|-------------------|"<<endl;
    cout<<"| (1)顺序队列置队空 |"<<endl;
    cout<<"|-------------------|"<<endl;
    cout<<"| (2)顺序队列入队   |"<<endl;
    cout<<"|-------------------|"<<endl;
    cout<<"| (3)顺序队列出队   |"<<endl;
    cout<<"|-------------------|"<<endl;
    cout<<"| (4)返回           |"<<endl;
    cout<<"|-------------------|"<<endl;
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
            SXD_init(SXD);
            SXD_display(SXD);
            break;
        case 2:
            SXDrudui(SXD);
            SXD_display(SXD);
            break;
        case 3:
            SXDchudui(SXD);
            SXD_display(SXD);
            break;
        case 4:
            menu(SXZ1,SXZ2,LZ1,LZ2,SXD,tail,n);
            break;
    }
    menu(SXZ1,SXZ2,LZ1,LZ2,SXD,tail,n);
}
void LDxx(SqStack &SXZ1,SqStack &SXZ2,LinkStack &LZ1,LinkStack &LZ2,SqQueue &SXD,QueuePtr &tail,int n)
{
    int c,d;
    int arg0;//存链队出队元素
    cout<<"|-------------------|"<<endl;
    cout<<"|   (1)链队置队空   |"<<endl;//置队空(初始化):使链队为空,使链队(单向循环链表)只含1个头结点
    cout<<"|-------------------|"<<endl;
    cout<<"|   (2)链队入队     |"<<endl;
    cout<<"|-------------------|"<<endl;
    cout<<"|   (3)链队出队     |"<<endl;
    cout<<"|-------------------|"<<endl;
    cout<<"|   (4)返回         |"<<endl;
    cout<<"|-------------------|"<<endl;
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
            LD_init(tail);
            LD_display(tail);
            break;
        case 2:
            LD_rudui(tail);
            LD_display(tail);
            break;
        case 3:
            LD_chudui(tail,arg0);
            LD_display(tail);
            break;
        case 4:
            menu(SXZ1,SXZ2,LZ1,LZ2,SXD,tail,n);
            break;
    }
    menu(SXZ1,SXZ2,LZ1,LZ2,SXD,tail,n);
}
void panduan(LinkStack &LZ1,LinkStack &LZ2)
{
    StackNode *p,*q,*a,*b;
    int i,j;j=LZjds(LZ1)/2;
    for(i=0;i<j;i++)
    {
        if(LZ1==NULL)
        {
            exit(0);
        }
        p=LZ1;
        LZ1=LZ1->next;
        q=p;
        q->next=LZ2;
        LZ2=q;
    }
    a=LZ1;b=LZ2;
    if(LZjds(LZ1)==LZjds(LZ2))
    {
        while(a!=NULL&&b!=NULL&&a->data==b->data)
        {
            a=a->next;
            b=b->next;
        }
        if(a==b)
        {
            cout<<"是中心对称"<<endl;
        }
        else
        {
            cout<<"不是中心对称"<<endl;
        }
    }
    else
    {
        a=a->next;
        while(a!=NULL&&b!=NULL&&a->data==b->data)
        {
            a=a->next;
            b=b->next;
        }
        if(a==b)
        {
            cout<<"是中心对称"<<endl;
        }
        else
        {
            cout<<"不是中心对称"<<endl;
        }
    }
}
void saomiao(SqStack &SXZ1,SqStack &SXZ2)
{
    if(SXZ1.base==SXZ1.top)
    {
        cout<<"该顺序栈为空"<<endl;
        exit(0);
    }
    char *p,q;p=SXZ1.base;int i=0;
    while(p!=SXZ1.top)
    {
        if(*p=='(')
        {
            if(SXZ2.top-SXZ2.base==SXZ2.stacksize)
            {
                cout<<"该顺序栈已满"<<endl;
                exit(0);
            }
            q=*p;
            *SXZ2.top=q;
            SXZ2.top++;
            p++;
        }
        else if(*p==')')
        {
            if(SXZ2.base==SXZ2.top)
            {
                i=1;
            }
            SXZ2.top--;
            p++;
        }
        else
        {
            p++;
        }
    }
    if(SXZ2.base==SXZ2.top)
    {
        cout<<"该算术表达式圆括号配对"<<endl;
    }
    else if(i==1)
    {
        cout<<"该算术表达式有圆括号缺失"<<endl;
    }
    else
    {
        cout<<"该算术表达式有圆括号缺失"<<endl;
    }
}
void menu(SqStack &SXZ1,SqStack &SXZ2,LinkStack &LZ1,LinkStack &LZ2,SqQueue &SXD,QueuePtr &tail,int n)
{
    int c,d;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|     (1)判断字符串是否成中心对称      |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|     (2)判断算术表达式圆括号是否配对  |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|     (3)顺序队列的操作                |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|     (4)链队的操作                    |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|     (5)返回                          |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    do{
        cin>>c;
        if(c<1||c>5)
        {
            cout<<"(输入有误)(1-5)";
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
            LZ_init(LZ1);
            LZ_create(LZ1,n);
            LZ_display(LZ1);
            LZ_init(LZ2);
            panduan(LZ1,LZ2);
            break;
        case 2:
            SXZ_init(SXZ1);
            SXZ_create(SXZ1,n);
            SXZ_display(SXZ1);
            SXZ_init(SXZ2);
            saomiao(SXZ1,SXZ2);
            break;
        case 3:
            SXDxx(SXZ1,SXZ2,LZ1,LZ2,SXD,tail,n);
            break;
        case 4:
            LDxx(SXZ1,SXZ2,LZ1,LZ2,SXD,tail,n);
            break;
        case 5:
            welcome(SXZ1,SXZ2,LZ1,LZ2,SXD,tail,n);
            break;
    }
    welcome(SXZ1,SXZ2,LZ1,LZ2,SXD,tail,n);
}
void welcome(SqStack &SXZ1,SqStack &SXZ2,LinkStack &LZ1,LinkStack &LZ2,SqQueue &SXD,QueuePtr &tail,int n)
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
            menu(SXZ1,SXZ2,LZ1,LZ2,SXD,tail,n);
            break;
        case 'N':
            exit(0);
    }
}
main()
{
    SqStack SXZ1,SXZ2;
    LinkStack LZ1,LZ2;
    SqQueue SXD;
    QueuePtr tail=NULL;
    int n;
    welcome(SXZ1,SXZ2,LZ1,LZ2,SXD,tail,n);
}
