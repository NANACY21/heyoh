/*创建二叉树可以用先序遍历,也可以用插入法,如二叉链表二叉排序树的创建*/
/*先序遍历：中左右，中序遍历：左中右，后序遍历：左右中*/
#include<stdio.h>//c语言的输入输出
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
#define MAXSIZE 100
using namespace std;
typedef struct//顺序二叉树存储结构(用向量作存储结构)
{
    char *base;//存储空间的基地址
}SqBiTree;
typedef struct BiTNode//二叉链表二叉树存储结构(二叉链表作存储结构)
{
    char data;
    BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
typedef struct StackNode0//顺序二叉树遍历辅助链栈存储结构
{
    int data;
    StackNode0 *next;
}StackNode0,*LinkStack0;
typedef struct StackNode//二叉链表二叉树遍历辅助链栈存储结构
{
    BiTNode *dizhi;
    StackNode *next;
}StackNode,*LinkStack;
void SXECS_init(SqBiTree &SXECS);
void SXECS_create(SqBiTree &SXECS);
void SXECS_qx_traversal(SqBiTree &SXECS,LinkStack0 &LZ0);//顺序二叉树先序遍历-显示(非递归)
int SXECSjds(SqBiTree &SXECS);
void ECLBECS_init(BiTree &ECLBECS);
void ECLBECS_create(BiTree &ECLBECS);//递归
void ECLBECS_qx_traversal(BiTree &ECLBECS,LinkStack &LZ);//二叉链表二叉树先序遍历-显示(非递归)
void ECLBECS_zx_traversal(BiTree &ECLBECS,LinkStack &LZ);//二叉链表二叉树中序遍历-显示(非递归)
void ECLBECS_hx_traversal(BiTree &ECLBECS,LinkStack &LZ);//二叉链表二叉树后序遍历-显示(非递归)
void LZ0_init(LinkStack0 &LZ0);//顺序二叉树遍历辅助链栈初始化
void LZ0ruzhan(int *i,LinkStack0 &LZ0);//顺序二叉树遍历辅助链栈入栈
void LZ0chuzhan(int *i,LinkStack0 &LZ0);//顺序二叉树遍历辅助链栈出栈
int LZ0panduan(LinkStack0 &LZ0);//顺序二叉树遍历辅助链栈为空则返回1,否则返回2
void LZ_init(LinkStack &LZ);//二叉链表二叉树遍历辅助链栈初始化
void LZruzhan(BiTree &ECLBECS,LinkStack &LZ);//二叉链表二叉树遍历辅助链栈入栈
void LZchuzhan(BiTree &ECLBECS,LinkStack &LZ);//二叉链表二叉树遍历辅助链栈出栈
int LZpanduan(LinkStack &LZ);//二叉链表二叉树遍历辅助链栈为空则返回1,否则返回2
int ECLBECSgaodu(BiTree &ECLBECS);//递归
int ECLBECSyezijds(BiTree &ECLBECS);//递归
int ECLBECSjds(BiTree &ECLBECS);//递归
void menu(SqBiTree &SXECS,BiTree &ECLBECS,LinkStack0 &LZ0,LinkStack &LZ);
void welcome(SqBiTree &SXECS,BiTree &ECLBECS,LinkStack0 &LZ0,LinkStack &LZ);
void SXECS_init(SqBiTree &SXECS)
{
    SXECS.base=new char[MAXSIZE];//为顺序二叉树分配一个最大容量为n的数组空间
    if(!SXECS.base)//存储分配失败
    {
        exit(0);
    }
}
void SXECS_create(SqBiTree &SXECS)
{
    char p=NULL;int i=1;
    while(p!='N')
    {
        cout<<"输入该节点的数据:";
        cin>>p;
        SXECS.base[i]=p;
        i++;
    }
    cout<<"顺序二叉树创建成功"<<endl;
}
void SXECS_qx_traversal(SqBiTree &SXECS,LinkStack0 &LZ0)//顺序二叉树先序遍历-显示(非递归)
{
    if(SXECS.base==NULL)
    {
        cout<<"请先创建顺序二叉树"<<endl;
    }
    else
    {
        LZ0_init(LZ0);
        int i=1,j,k=SXECSjds(SXECS);
        while(LZ0panduan(LZ0)==2||(i>=1&&i<=k))
        {
            if((i>=1&&i<=k))
            {
                cout<<SXECS.base[i]<<"  ";
                LZ0ruzhan(&i,LZ0);
                i=i*2;
            }
            else
            {
                LZ0chuzhan(&j,LZ0);
                i=j*2+1;
            }
        }
    }
    cout<<endl;
}
int SXECSjds(SqBiTree &SXECS)
{
    if(SXECS.base==NULL)
    {
        cout<<"没有顺序二叉树"<<endl;
        return 0;
    }
    else
    {
        int i=0;
        while(SXECS.base[i]!='N')
        {
            i++;
        }
        return i-1;
    }
}
void ECLBECS_init(BiTree &ECLBECS)
{
    ECLBECS=NULL;
}
void ECLBECS_create(BiTree &ECLBECS)//递归
{
    char p;
    cout<<"输入该结点的数据:";
    cin>>p;
    if(p=='N')//如果输入字符'N',则没有该结点
    {
        ECLBECS=NULL;
    }
    else
    {
        ECLBECS=new BiTNode;
        ECLBECS->data=p;
        ECLBECS_create(ECLBECS->lchild);
        ECLBECS_create(ECLBECS->rchild);
    }
}
void ECLBECS_qx_traversal(BiTree &ECLBECS,LinkStack &LZ)//二叉链表二叉树先序遍历-显示(非递归)
{
    if(ECLBECS==NULL)
    {
        cout<<"请先创建二叉链表二叉树"<<endl;
    }
    else
    {
        LZ_init(LZ);
        BiTNode *p,*q;
        p=ECLBECS;q=new BiTNode;
        while(p||LZpanduan(LZ)==2)//当结点存在或栈不空
        {
            if(p)
            {
                cout<<p->data<<"  ";
                LZruzhan(p,LZ);
                p=p->lchild;
            }
            else
            {
                LZchuzhan(q,LZ);
                p=q->rchild;
            }
        }
        cout<<endl;
    }
}
void ECLBECS_zx_traversal(BiTree &ECLBECS,LinkStack &LZ)//二叉链表二叉树中序遍历-显示(非递归)
{
    if(ECLBECS==NULL)
    {
        cout<<"请先创建二叉链表二叉树"<<endl;
    }
    else
    {
        LZ_init(LZ);
        BiTNode *p,*q;
        p=ECLBECS;q=new BiTNode;
        while(p||LZpanduan(LZ)==2)//当结点存在或栈不空
        {
            if(p)
            {
                LZruzhan(p,LZ);
                p=p->lchild;
            }
            else
            {
                LZchuzhan(q,LZ);
                cout<<q->data<<"  ";
                p=q->rchild;
            }
        }
        cout<<endl;
    }
}
void ECLBECS_hx_traversal(BiTree &ECLBECS,LinkStack &LZ)//二叉链表二叉树后序遍历-显示(非递归)
{
    if(ECLBECS==NULL)
    {
        cout<<"请先创建二叉链表二叉树"<<endl;
    }
    else
    {
        LZ_init(LZ);//二叉链表二叉树辅助链栈初始化
        BiTNode *p,*q,*r=NULL;
        p=ECLBECS;q=new BiTNode;//p指向根结点
        while(p)//当p存在
        {
            LZruzhan(p,LZ);
            p=p->lchild;
        }
        while(LZpanduan(LZ)==2)//当栈不空
        {
            LZchuzhan(q,LZ);////
            if(q->rchild==NULL||q->rchild==r)
            {
                cout<<q->data<<"  ";
                r=q;
            }
            else
            {
                LZruzhan(q,LZ);////
                p=q->rchild;
                while(p)
                {
                    LZruzhan(p,LZ);
                    p=p->lchild;
                }
            }
        }
        cout<<endl;
    }
}
void LZ0_init(LinkStack0 &LZ0)//顺序二叉树遍历辅助链栈初始化
{
    LZ0=NULL;//不设头结点
}
void LZ0ruzhan(int *i,LinkStack0 &LZ0)//顺序二叉树遍历辅助链栈入栈
{
    StackNode0 *p;
    p=new StackNode0;
    p->data=*i;
    p->next=LZ0;
    LZ0=p;
}
void LZ0chuzhan(int *i,LinkStack0 &LZ0)//顺序二叉树遍历辅助链栈出栈
{
    StackNode0 *p;
    *i=LZ0->data;
    p=LZ0;
    LZ0=LZ0->next;
    delete p;
}
int LZ0panduan(LinkStack0 &LZ0)//顺序二叉树遍历辅助链栈为空则返回1,否则返回2
{
    if(LZ0==NULL)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}
void LZ_init(LinkStack &LZ)//二叉链表二叉树遍历辅助链栈初始化
{
    LZ=NULL;//不设头结点
}
void LZruzhan(BiTree &ECLBECS,LinkStack &LZ)//二叉链表二叉树遍历辅助链栈入栈
{
    StackNode *p;
    p=new StackNode;
    p->dizhi=ECLBECS;
    p->next=LZ;
    LZ=p;
}
void LZchuzhan(BiTree &ECLBECS,LinkStack &LZ)//二叉链表二叉树遍历辅助链栈出栈
{
    StackNode *p;
    ECLBECS=LZ->dizhi;
    p=LZ;
    LZ=LZ->next;
    delete p;
}
int LZpanduan(LinkStack &LZ)//二叉链表二叉树遍历辅助链栈为空则返回1,否则返回2
{
    if(LZ==NULL)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}
int ECLBECSgaodu(BiTree &ECLBECS)//递归
{
    int m=0,n=0;
    if(ECLBECS==NULL)
    {
        return 0;
    }
    else
    {
        m=ECLBECSgaodu(ECLBECS->lchild);
        n=ECLBECSgaodu(ECLBECS->rchild);
        if(m>n)
        {
            return m+1;
        }
        else
        {
            return n+1;
        }
    }
}
int ECLBECSyezijds(BiTree &ECLBECS)//递归
{
    if(ECLBECS==NULL)
    {
        cout<<"没有二叉链表二叉树"<<endl;
    }
    if(ECLBECS->lchild==NULL&&ECLBECS->rchild==NULL)
    {
        return 1;
    }
    else if(ECLBECS->lchild==NULL)
    {
        return ECLBECSyezijds(ECLBECS->rchild);
    }
    else if(ECLBECS->rchild==NULL)
    {
        return ECLBECSyezijds(ECLBECS->lchild);
    }
    else
    {
        return ECLBECSyezijds(ECLBECS->lchild)+ECLBECSyezijds(ECLBECS->rchild);
    }
}
int ECLBECSjds(BiTree &ECLBECS)//递归
{
    if(ECLBECS==NULL)
    {
        return 0;
    }
    else
    {
        return ECLBECSjds(ECLBECS->lchild)+ECLBECSjds(ECLBECS->rchild)+1;
    }
}
void menu(SqBiTree &SXECS,BiTree &ECLBECS,LinkStack0 &LZ0,LinkStack &LZ)
{
    int c,d;
    cout<<"|----------------------------------------------------|"<<endl;
    cout<<"|     (1)建立二叉链表二叉树                          |"<<endl;
    cout<<"|----------------------------------------------------|"<<endl;
    cout<<"|     (2)建立顺序二叉树                              |"<<endl;
    cout<<"|----------------------------------------------------|"<<endl;
    cout<<"|     (3)二叉链表二叉树的前序遍历                    |"<<endl;
    cout<<"|----------------------------------------------------|"<<endl;
    cout<<"|     (4)二叉链表二叉树的中序遍历                    |"<<endl;
    cout<<"|----------------------------------------------------|"<<endl;
    cout<<"|     (5)二叉链表二叉树的后序遍历                    |"<<endl;
    cout<<"|----------------------------------------------------|"<<endl;
    cout<<"|     (6)计算二叉链表二叉树的高度                    |"<<endl;
    cout<<"|----------------------------------------------------|"<<endl;
    cout<<"|     (7)计算二叉链表二叉树的结点数                  |"<<endl;
    cout<<"|----------------------------------------------------|"<<endl;
    cout<<"|     (8)计算二叉链表二叉树的叶子结点数              |"<<endl;
    cout<<"|----------------------------------------------------|"<<endl;
    cout<<"|     (9)顺序二叉树的前序遍历                        |"<<endl;
    cout<<"|----------------------------------------------------|"<<endl;
    cout<<"|     (10)返回                                       |"<<endl;
    cout<<"|----------------------------------------------------|"<<endl;
    do{
        cin>>c;
        if(c<1||c>10)
        {
            cout<<"(输入有误)(1-10)";
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
            ECLBECS_init(ECLBECS);//二叉链表二叉树初始化
            ECLBECS_create(ECLBECS);//二叉链表二叉树创建
            cout<<"创建二叉链表二叉树成功"<<endl;
            break;
        case 2:
            SXECS_init(SXECS);
            SXECS_create(SXECS);
            break;
        case 3:
            ECLBECS_qx_traversal(ECLBECS,LZ);//二叉链表二叉树先序遍历-显示//非递归
            break;
        case 4:
            ECLBECS_zx_traversal(ECLBECS,LZ);//二叉链表二叉树中序遍历-显示//非递归
            break;
        case 5:
            ECLBECS_hx_traversal(ECLBECS,LZ);//二叉链表二叉树后序遍历-显示//非递归
            break;
        case 6:
            if(ECLBECS==NULL)
            {
                cout<<"请先创建二叉链表二叉树"<<endl;
            }
            else
            {
                cout<<"该二叉链表二叉树的高度为"<<ECLBECSgaodu(ECLBECS)<<endl;
            }
            break;
        case 7:
            if(ECLBECS==NULL)
            {
                cout<<"请先创建二叉链表二叉树"<<endl;
            }
            else
            {
                cout<<"该二叉链表二叉树的结点数为"<<ECLBECSjds(ECLBECS)<<endl;
            }
            break;
        case 8:
            if(ECLBECS==NULL)
            {
                cout<<"请先创建二叉链表二叉树"<<endl;
            }
            else
            {
                cout<<"该二叉链表二叉树的叶子结点数为"<<ECLBECSyezijds(ECLBECS)<<endl;
            }
            break;
        case 9:
            SXECS_qx_traversal(SXECS,LZ0);
            break;
        case 10:
            welcome(SXECS,ECLBECS,LZ0,LZ);
            break;
    }
    welcome(SXECS,ECLBECS,LZ0,LZ);
}
void welcome(SqBiTree &SXECS,BiTree &ECLBECS,LinkStack0 &LZ0,LinkStack &LZ)
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
            menu(SXECS,ECLBECS,LZ0,LZ);
            break;
        case 'N':
            exit(0);
    }
}
int main()
{
    SqBiTree SXECS;//顺序二叉树地址
    BiTree ECLBECS=NULL;//二叉链表二叉树地址
    LinkStack0 LZ0=NULL;//顺序二叉树遍历辅助链栈地址
    LinkStack LZ=NULL;//二叉链表二叉树遍历辅助链栈地址
    welcome(SXECS,ECLBECS,LZ0,LZ);
    return 0;
}
