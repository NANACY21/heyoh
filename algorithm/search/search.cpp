#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<cstdlib>//
#include<math.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<string>//?
#include<iostream>
#include<stack>//栈
#include<queue>//队列,优先队列
#include<algorithm>//堆
#include<vector>//向量
#define MaxInt 9999//极大值
#define MVNum 100//最大顶点数
#define bag 40//书包的容量(最大能承受bag斤的重量,无需考虑体积问题)
using namespace std;
/*查找算法合集*/
/*顺序表存储结构*/
typedef struct
{
    int key;//关键字域
    int otherinfo;//其它域
}ElemType;
typedef struct
{
    ElemType *elem;//存储空间的基地址
    int length;//表长(当前长度)
    int left;//顺序表第一个元素下标
    int right;//顺序表最后一个元素下标
    int n;//顺序表数据元素数
}SStable;
/*二叉排序树的二叉链表存储表示*/
typedef struct BSTNode
{
    ElemType data;//每个结点的数据域包括关键字项和其它数据项
    struct BSTNode *lchild,*rchild;//左右孩子指针
}BSTNode,*BSTree;
/*二叉链表二叉排序树遍历辅助链栈存储结构*/
typedef struct StackNode
{
    BSTNode *dizhi;
    StackNode *next;
}StackNode,*LinkStack;
/*--------------------------------------------------*/
void SXB_init(SStable &L);
void SXB_create(SStable &L);
void SXB_display(SStable &L);
/*--------------------------------------------------*/
void search_seq(SStable &L);//顺序查找
/*--------------------------------------------------*/
void search_seq_alt(SStable &L);//设置监视哨的顺序查找
/*--------------------------------------------------*/
void search_bin(SStable &L);//折半查找
/*--------------------------------------------------*/
void insert_BST(BSTree &T,ElemType e);//创建二叉链表二叉排序树
void creat_BST(BSTree &T);
/*--------------------------------------------------*/
void BST_zx_traversal(BSTree &T,LinkStack &LZ);//二叉链表二叉排序树中序遍历-显示(非递归)
/*--------------------------------------------------*/
BSTree search_BST(BSTree &T,int key);//二叉链表二叉排序树的查找
/*--------------------------------------------------*/
void delete_BST(BSTree &T);//二叉链表二叉排序树的结点删除
/*--------------------------------------------------*/
void LZ_init(LinkStack &LZ);//二叉链表二叉排序树遍历辅助链栈初始化
void LZruzhan(BSTree &T,LinkStack &LZ);//二叉链表二叉排序树遍历辅助链栈入栈
void LZchuzhan(BSTree &T,LinkStack &LZ);//二叉链表二叉排序树遍历辅助链栈出栈
int LZpanduan(LinkStack &LZ);//二叉链表二叉排序树遍历辅助链栈为空则返回1,否则返回2
/*--------------------------------------------------*/
void menu1();
void menu2(SStable &L,BSTree &T,LinkStack &LZ);
/*--------------------------------------------------*/
void SXB_init(SStable &L)
{
    L.elem=new ElemType[MVNum];
    if(!L.elem)
    {
        exit(0);
    }
    L.length=0;
    L.n=0;
}
void SXB_create(SStable &L)
{
    cout<<"你想输入多少数据元素?";
    cin>>L.n;
    for(int i=1;i<=L.n;i++)
    {
        cout<<"请输入第"<<i<<"个数据元素:";
        cin>>L.elem[i].key;
        ++L.length;
    }
    L.left=1;
    L.right=L.length;
}
void SXB_display(SStable &L)
{
    for(int i=1;i<=L.length;i++)
    {
        cout<<L.elem[i].key<<"   ";
    }
    cout<<endl;
}
void search_seq(SStable &L)//顺序查找
{
    int key;
    int i,flag=0;
    cout<<"请输入关键字 ";
    cin>>key;
    for(i=L.length;i>=1;--i)
    {
        if(L.elem[i].key==key)//如果相等//从后往前找
        {
            cout<<"该关键字属于顺序表第"<<i<<"个数据元素"<<endl;
        }
        else
        {
            flag++;
        }
    }
    if(flag==L.length)
    {
        cout<<"该顺序表中没有这个关键字"<<endl;
    }
}
void search_seq_alt(SStable &L)//设置监视哨的顺序查找
{
    int key;
    int i;
    cout<<"请输入关键字 ";
    cin>>key;
    L.elem[0].key=key;//哨兵
    for(i=L.length;L.elem[i].key!=key;--i);//L.elem[i].key!=key不成立时跳出循环
    if(i==0)
    {
        cout<<"该顺序表中没有这个关键字"<<endl;
    }
    else
    {
        cout<<"该关键字属于顺序表第"<<i<<"个数据元素"<<endl;
    }
}
void search_bin(SStable &L)//折半查找
{
    int i,left,right,mid,key,flag=0;
    cout<<"请输入关键字 ";
    cin>>key;
    left=1;right=L.length;//置查找区间值
    while(left<=right)
    {
        mid=(left+right)/2;
        if(key==L.elem[mid].key)//找到待查元素
        {
            cout<<"该关键字属于顺序表第"<<mid<<"个数据元素"<<endl;
            flag=1;
            break;
        }
        else if(key<L.elem[mid].key)//继续在前一子表进行查找
        {
            right=mid-1;
        }
        else//继续在后一子表进行查找
        {
            left=mid+1;
        }
    }
    if(flag==0)
    {
        cout<<"该顺序表中没有这个关键字"<<endl;
    }
    /*string key;cin>>key;
    int temp_key=atoi(key.c_str());//字符串类型转整形*/
}
void insert_BST(BSTree &T,ElemType e)//创建二叉链表二叉排序树
{//二叉链表二叉排序树的结点插入:
 //当二叉链表二叉排序树T中不存在关键字等于S->data.key的数据元素时,则插入该元素
    if(!T)//如果T是空树
    {                 //找到插入位置,递归结束
        BSTNode *S;
        S=new BSTNode;//生成新结点*S
        S->data=e;//新结点*S的数据域置为e
        S->lchild=S->rchild=NULL;//新结点*S作为叶子结点
        T=S;//把新结点*S链接到已找到的插入位置
    }
    else if(e.key<T->data.key)
    {
        insert_BST(T->lchild,e);//将*S插入左子树
    }
    else if(e.key>T->data.key)
    {
        insert_BST(T->rchild,e);//将*S插入右子树
    }
}
void creat_BST(BSTree &T)
{//依次读入一个关键字为S->data.key的结点,将此结点插入二叉链表二叉排序树T中
    int ENDFLAG=0;//ENDFLAG为自定义常量,作为输入结束标志
    ElemType e;
    T=NULL;//二叉链表二叉排序树T初始化为空树
    cout<<"输入新结点的数据域的关键字(输入数字0以结束输入) ";//一个结点的数据域即一个数据元素
    cin>>e.key;
    while(e.key!=ENDFLAG)//ENDFLAG为自定义常量,作为输入结束标志
    {
        insert_BST(T,e);//将此结点插入二叉链表二叉排序树T中
        cout<<"输入新结点的数据域的关键字(输入数字0以结束输入) ";//一个结点的数据域即一个数据元素
        cin>>e.key;
    }
}
void BST_zx_traversal(BSTree &T,LinkStack &LZ)//二叉链表二叉排序树中序遍历-显示(非递归)
{
    if(T==NULL)
    {
        cout<<"请先创建二叉链表二叉树"<<endl;
    }
    else
    {
        int i=1;
        LZ_init(LZ);
        BSTNode *p,*q;
        p=T;q=new BSTNode;
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
                cout<<q->data.key<<"  ";
                p=q->rchild;
            }
        }
        cout<<endl;
    }
}
BSTree search_BST(BSTree &T,int key)//二叉链表二叉排序树的查找
{//在根指针T所指二叉链表二叉排序树中递归地查找某关键字等于e.key的数据元素
 //若查找成功,则返回指向该数据元素结点的指针,否则返回空指针
 //亦可通过中序遍历,找到该关键字属于该二叉链表二叉排序树中序遍历序列第几个数据元素
    if((!T)||(key==T->data.key))
    {            //查找结束
        return T;
    }
    else if(key<T->data.key)
    {
        return search_BST(T->lchild,key);//在左子树中继续查找
    }
    else
    {
        return search_BST(T->rchild,key);//在右子树中继续查找
    }
}
void delete_BST(BSTree &T)//二叉链表二叉排序树的结点删除
{//从二叉链表二叉树T中删除关键字等于key的结点
    int key;
    cout<<"请输入关键字 ";
    cin>>key;
    BSTNode *p,*f;
    p=T;f=NULL;//初始化
    /*-----下面的while循环从根开始查找关键字等于key的结点*p-----*/
    while(p)
    {
        if(p->data.key==key)//找到关键字等于key的结点*p,结束循环
        {
            break;
        }
        f=p;//*f为*p的双亲结点
        if(p->data.key>key)
        {
            p=p->lchild;//在*p的左子树中继续寻找
        }
        else//在*p的右子树中继续寻找
        {
            p=p->rchild;
        }
    }
    if(!p)//找不到被删结点则返回
    {
        return;
    }
    /*-----考虑3种情况实现p所指子树内部的处理:*p左右子树均不空、无右子树、无左子树-----*/
    BSTNode *q;
    q=p;
    if((p->lchild)&&(p->rchild))//被删结点*p左右子树均不空
    {
        BSTNode *s;
        s=p->lchild;
        while(s->rchild)//在*p的左子树中继续查找其前驱结点,即最右下结点
        {
            q=s;s=s->rchild;//向右到尽头
        }
        p->data=s->data;//s指向被删结点的"前驱"
        if(q!=p)
        {
            q->rchild=s->lchild;//重接*q的右子树
        }
        else
        {
            q->lchild=s->lchild;//重接*q的左子树
        }
        delete s;
        return;
    }
    else if(!p->rchild)//被删结点*p无右子树,只需重接其左子树
    {
        p=p->lchild;
    }
    else if(!p->lchild)//被删结点*p无左子树,只需重接其右子树
    {
        p=p->rchild;
    }
    /*-----将p所指的子树挂接到其双亲结点*f相应的位置-----*/
    if(!f)//被删结点为根结点
    {
        T=p;
    }
    else if(q==f->lchild)
    {
        f->lchild=p;//挂接到*f的左子树位置
    }
    else
    {
        f->rchild=p;//挂接到*f的右子树位置
    }
    delete q;
    cout<<"已删除包含该关键字的结点"<<endl;
}
void LZ_init(LinkStack &LZ)//二叉链表二叉排序树遍历辅助链栈初始化
{
    LZ=NULL;//不设头结点
}
void LZruzhan(BSTree &T,LinkStack &LZ)//二叉链表二叉排序树遍历辅助链栈入栈
{
    StackNode *p;
    p=new StackNode;
    p->dizhi=T;
    p->next=LZ;
    LZ=p;
}
void LZchuzhan(BSTree &T,LinkStack &LZ)//二叉链表二叉排序树遍历辅助链栈出栈
{
    StackNode *p;
    T=LZ->dizhi;
    p=LZ;
    LZ=LZ->next;
    delete p;
}
int LZpanduan(LinkStack &LZ)//二叉链表二叉排序树遍历辅助链栈为空则返回1,否则返回2
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
void menu1()
{
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|     线性表的查找                           |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (1)创建顺序表                      |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (2)顺序查找                        |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (3)设置监视哨的顺序查找            |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (4)折半查找                        |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (5)分块查找                        |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|     树表的查找                             |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|       二叉排序树                           |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (6)创建二叉链表二叉排序树          |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (7)二叉链表二叉排序树的中序遍历    |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (8)二叉链表二叉排序树的查找        |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (9)二叉链表二叉排序树的结点插入    |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (10)二叉链表二叉排序树的结点删除   |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|       平衡二叉树                           |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (11)创建平衡二叉树                 |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (12)平衡二叉树的平衡调整方法       |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (13)平衡二叉树的结点插入           |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|       B-树                                 |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (14)创建B-树                       |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (15)B-树的查找                     |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (16)B-树的结点插入                 |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (17)B-树的结点删除                 |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|       B+树                                 |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|     散列表的查找                           |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (18)创建散列表                     |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (19)散列表的查找                   |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
    cout<<"|         (20)退出                           |"<<endl;
    cout<<"|--------------------------------------------|"<<endl;
}
void menu2(SStable &L,BSTree &T,LinkStack &LZ)
{
    int b,c;
    cout<<"----------------------------------------------"<<endl;
    cout<<"选择功能";
    do{
        cin>>b;
        if(b<1||b>20)
        {
            cout<<"(输入有误)(1-20)";
            c=1;
            getchar();
        }
        else
        {
            c=0;
        }
    }while(c==1);
    cout<<"----------------------------------------------"<<endl;
    switch(b)
    {
        case 1:
            SXB_init(L);
            SXB_create(L);
            SXB_display(L);
            break;
        case 2:
            search_seq(L);
            break;
        case 3:
            search_seq_alt(L);
            break;
        case 4:
            search_bin(L);
            break;
        case 5:

            break;
        case 6:
            creat_BST(T);
            break;
        case 7:
            BST_zx_traversal(T,LZ);
            break;
        case 8:
            int key;
            cout<<"请输入关键字 ";
            cin>>key;
            if(search_BST(T,key)==NULL)
            {
                cout<<"没有二叉链表二叉排序树"<<endl;
            }
            else
            {
                cout<<"该关键字属于"<<search_BST(T,key)->data.key<<"数据元素"<<endl;
            }
            break;
        case 9:
            ElemType e;
            cout<<"输入新结点的数据域的关键字 ";//一个结点的数据域即一个数据元素
            cin>>e.key;
            insert_BST(T,e);
            break;
        case 10:
            delete_BST(T);
            break;
        case 11:

            break;
        case 12:

            break;
        case 13:

            break;
        case 14:

            break;
        case 15:

            break;
        case 16:

            break;
        case 17:

            break;
        case 18:

            break;
        case 19:

            break;
        case 20:
            exit(0);
    }
    menu2(L,T,LZ);
}
main()
{
    //查找还包括外部查找
    SStable L;//顺序表
    BSTree T=NULL;//二叉链表二叉排序树
    LinkStack LZ=NULL;//二叉链表二叉排序树遍历辅助链栈地址
    menu1();
    menu2(L,T,LZ);
}
