#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
using namespace std;
typedef struct LNode//单向循环链表存储结构
{
    int data;//通用类型标识符ElemType,ElemType data
    LNode *next;
}LNode,*LinkList;
typedef struct LNodec//单向非循环链表存储结构//单向循环链表存储结构
{
    char data;//通用类型标识符ElemType,ElemType data
    LNodec *next;
}LNodec,*LinkListc;
typedef struct DuLNode//双向非循环链表存储结构
{
    int data;//通用类型标识符ElemType,ElemType data
    DuLNode *prior;
    DuLNode *next;
    int freq=0;//该结点被访问了几次
}DuLNode,*DuLinkList;
void DFX_init(LinkListc &head);
void DFX_create(LinkListc &head,int n);
void DFX_display(LinkListc &head);
void DX_create(LinkList &tail,int n);
void DX_display(LinkList &tail);
void SFX_init(DuLinkList &head2);
void SFX_create(DuLinkList &head2,int n);
void SFX_display(DuLinkList &head2);
void shanchu(LinkList &tail,int n);
void cunfang(LinkListc &head1,LinkListc &tail2,LinkListc &tail3,LinkListc &tail4);
void DXc_display(LinkListc &tail);
void jiaohuan(DuLNode *linshihead,DuLNode *maxfreq);
void paixu(DuLinkList &head);
void jisuan(DuLinkList &head,int e);
void fangwen(DuLinkList &head,int e);
void menu(LinkList &head3_1,LinkList &head1,LinkList &head2,int n,int e);
void welcome(LinkList &tail1,LinkListc &head1,LinkListc &tail2,LinkListc &tail3,LinkListc &tail4,DuLinkList &head2,int n,int e);
void DFX_init(LinkListc &head)//构造一个空链表head
{
    head=new LNodec;head->next=NULL;
    cout<<"已初始化单向非循环链表(已有头结点,头结点->next空)"<<endl;
}
void DFX_create(LinkListc &head,int n)
{
    LNodec *linshihead,*p;//*linshihead是尾指针
    linshihead=head;//尾指针初始化,指向头结点
    cout<<"在该单向非循环链表中你想建立多少个结点?(除头结点)";cin>>n;
    for(int i=0;i<n;i++)
    {
        p=new LNodec;
        cout<<"输入第"<<i+1<<"个结点要存放的数据:";cin>>p->data;p->next=NULL;
        linshihead->next=p;//尾插
        linshihead=p;//尾指针后移
    }
    cout<<"已新建单向非循环链表(含"<<n<<"个结点)";
}
void DFX_display(LinkListc &head)
{
    LNodec *linshihead;linshihead=head;
    while(linshihead!=NULL&&linshihead->next!=NULL)
    {
        cout<<linshihead->next->data<<"  ";
        linshihead=linshihead->next;//指针后移
    }
    if(linshihead==NULL)
    {
        cout<<"没有头结点"<<endl;
    }
    cout<<endl;
}
void DX_create(LinkList &tail,int n)
{
    LinkList head;
    head=new LNode;head->next=NULL;
    LNode *p;
    tail=head;
    cout<<"在该单向循环链表中你想建立多少个结点?(除头结点)";cin>>n;
    for(int i=0;i<n;i++)
    {
        p=new LNode;
        cout<<"输入第"<<i+1<<"个结点要存放的数据:";
        cin>>p->data;
        tail->next=p;//尾插
        p->next=head;
        tail=p;
    }
    cout<<"已新建单向循环链表(含"<<n<<"个结点)";
}
void DX_display(LinkList &tail)
{
    LNode *linshihead=tail->next->next;
    if((tail==NULL)||(tail->next==NULL)||(tail->next->next==NULL))
    {
        cout<<"该循环链表为空"<<endl;
    }
    while(linshihead!=tail->next)
    {
        cout<<linshihead->data<<"  ";
        linshihead=linshihead->next;//指针后移
    }
    cout<<endl;
}
void SFX_init(DuLinkList &head2)
{
    head2=new DuLNode;head2->next=NULL;
    cout<<"已初始化双向非循环链表(已有头结点,头结点->next空)"<<endl;
}
void SFX_create(DuLinkList &head2,int n)
{
    DuLNode *linshihead,*p;//*linshihead是尾指针
    linshihead=head2;//尾指针初始化,指向头结点
    cout<<"在该双向非循环链表中你想建立多少个结点?(除头结点)";cin>>n;
    for(int i=0;i<n;i++)
    {
        p=new DuLNode;
        cout<<"输入第"<<i+1<<"个结点要存放的数据:";cin>>p->data;p->next=NULL;
        linshihead->next=p;//尾插
        p->prior=linshihead;
        linshihead=p;//尾指针后移
    }
    cout<<"已新建双向非循环链表(含"<<n<<"个结点)";
}
void SFX_display(DuLinkList &head2)
{
    DuLNode *linshihead;linshihead=head2;
    while(linshihead!=NULL&&linshihead->next!=NULL)
    {
        cout<<linshihead->next->data<<"  ";
        linshihead=linshihead->next;//指针后移
    }
    cout<<endl;
}
void shanchu(LinkList &tail,int n)
{
    cout<<"输入结点数据,删除其前一个结点:";cin>>n;
    LNode *linshihead=tail->next->next;
    if(linshihead->data==n)
    {
        LNode *q=NULL;
        do
        {
            linshihead=linshihead->next;
        }
        while(linshihead->next->data!=tail->data);
        q=linshihead->next;
        linshihead->next=tail->next;
        delete q;
        tail=linshihead;
    }
    while(linshihead!=tail->next&&linshihead->next!=tail->next)
    {
        if(linshihead->next->data==n)
        {
            LNode *q=tail->next->next;
            while(linshihead!=tail->next&&linshihead->next!=tail->next)
            {
                if(q->next->next->data==linshihead->next->data)
                {
                    q->next=linshihead->next;
                    delete linshihead;
                    break;
                }
                q=q->next;
            }
        }
        linshihead=linshihead->next;//指针后移
    }
    if(linshihead->next==NULL)
    {
        cout<<"错误";
    }
}
void cunfang(LinkListc &head1,LinkListc &tail2,LinkListc &tail3,LinkListc &tail4)
{
    LinkListc head2,head3,head4;
    head2=new LNodec;head2->next=NULL;
    head3=new LNodec;head3->next=NULL;
    head4=new LNodec;head4->next=NULL;
    tail2=head2;tail3=head3;tail4=head4;
    LNodec *linshihead1;linshihead1=head1->next;
    while(linshihead1!=NULL)
    {
        if((linshihead1->data>=43)&&(linshihead1->data<=52))
        {
            tail2->next=linshihead1;
            linshihead1=linshihead1->next;
            tail2=tail2->next;
            tail2->next=head2;
        }
        else if((linshihead1->data>=65)&&(linshihead1->data<=90)||(linshihead1->data>=97)&&(linshihead1->data<=122))
        {
            tail3->next=linshihead1;
            linshihead1=linshihead1->next;
            tail3=tail3->next;
            tail3->next=head3;
        }
        else
        {
            tail4->next=linshihead1;
            linshihead1=linshihead1->next;
            tail4=tail4->next;
            tail4->next=head4;
        }
    }
}
void DXc_display(LinkListc &tail)
{
    LNodec *linshihead=tail->next->next;
    if((tail==NULL)||(tail->next==NULL)||(tail->next->next==NULL))
    {
        cout<<"该循环链表为空"<<endl;
    }
    while(linshihead!=tail->next)
    {
        cout<<linshihead->data<<"  ";
        linshihead=linshihead->next;//指针后移
    }
    cout<<endl;
}
void jiaohuan(DuLNode *linshihead,DuLNode *maxfreq)//交换双向非循环链表中任意两个结点(*maxfreg往前排)
{
    if(linshihead==maxfreq)//如果交换的是同一个结点
    {

    }
    if(maxfreq!=linshihead->next)//如果不相邻
    {
        linshihead->next->prior=maxfreq;//第一步
        maxfreq->prior->next=linshihead;//第二步
    }
    linshihead->prior->next=maxfreq;//第三步
    if(maxfreq->next!=NULL)
    {
        maxfreq->next->prior=linshihead;//第四步
    }
    ////结点交换完之后
    DuLNode *maxfreq_prior=maxfreq->prior;//先让maxfreq_prior指向maxfreq的前一结点
    DuLNode *linshihead_next=linshihead->next;//先让linshihead_next指向linshihead的后一结点
    ////结点交换完之后
    maxfreq->prior=linshihead->prior;//linshihead的前一结点让maxfreq->prior来存
    linshihead->next=maxfreq->next;//maxfreq的next让linshihead->next来存
    if(maxfreq==linshihead_next)//如果相邻
    {
        maxfreq->next=linshihead;
        linshihead->prior=maxfreq;
    }
    else
    {
        maxfreq->next=linshihead_next;
        linshihead->prior=maxfreq_prior;
    }
}
void paixu(DuLinkList &head)
{
    for(DuLNode *linshihead1=head->next;linshihead1->next!=NULL;linshihead1=linshihead1->next)
    {
        DuLNode *maxfreq=linshihead1;
        for(DuLNode *linshihead2=linshihead1->next;linshihead2!=NULL;linshihead2=linshihead2->next)
        {
            if(linshihead2->freq>maxfreq->freq)
            {
                maxfreq=linshihead2;
            }
        }
        jiaohuan(linshihead1,maxfreq);
        linshihead1=maxfreq;//再和后面的比
    }
}
void jisuan(DuLinkList &head,int e)
{
    cout<<"请输入:";cin>>e;
    DuLNode *linshihead;linshihead=head->next;
    while(linshihead&&linshihead->data!=e)//查找
    {
        linshihead=linshihead->next;
    }
    linshihead->freq=linshihead->freq+1;//找到后freq+1
    paixu(head);//双向非循环链表按结点的freg值递减的排序
    SFX_display(head);
    fangwen(head,e);
}
void fangwen(DuLinkList &head2,int e)
{
    char a,b;
    cout<<"访问该双向非循环链表的结点吗?(Y or N)";
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
            jisuan(head2,e);
            break;
        case 'N':
            SFX_display(head2);
            break;
    }
}
void menu(LinkList &tail1,LinkListc &head1,LinkListc &tail2,LinkListc &tail3,LinkListc &tail4,DuLinkList &head2,int n,int e)
{
    int c,d;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|      (1)单向循环链表的结点删除       |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|      (2)单向非循环链表结点分类       |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|      (3)双向非循环链表的排序         |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|              (4)返回                 |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
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
            DX_create(tail1,n);
            DX_display(tail1);
            shanchu(tail1,n);
            DX_display(tail1);
            break;
        case 2:
            DFX_init(head1);
            DFX_create(head1,n);
            DFX_display(head1);
            cunfang(head1,tail2,tail3,tail4);
            DXc_display(tail2);
            DXc_display(tail3);
            DXc_display(tail4);
            break;
        case 3:
            SFX_init(head2);
            SFX_create(head2,n);
            SFX_display(head2);
            fangwen(head2,e);
            break;
        case 4:
            welcome(tail1,head1,tail2,tail3,tail4,head2,n,e);
            break;
    }
    welcome(tail1,head1,tail2,tail3,tail4,head2,n,e);
}
void welcome(LinkList &tail1,LinkListc &head1,LinkListc &tail2,LinkListc &tail3,LinkListc &tail4,DuLinkList &head2,int n,int e)
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
            menu(tail1,head1,tail2,tail3,tail4,head2,n,e);
            break;
        case 'N':
            exit(0);
            break;
    }
}
main()
{
    LinkList tail1=NULL;//单向循环链表地址
    LinkListc head1=NULL;//单向非循环链表地址
    LinkListc tail2=NULL;//单向循环链表地址
    LinkListc tail3=NULL;//单向循环链表地址
    LinkListc tail4=NULL;//单向循环链表地址
    DuLinkList head2=NULL;//双向非循环链表地址
    int n,e;
    welcome(tail1,head1,tail2,tail3,tail4,head2,n,e);
}
