#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
using namespace std;
typedef struct LNode
{
    int data;//通用类型标识符ElemType,ElemType data
    LNode *next;
}LNode,*LinkList;
void DFX_init(LinkList &head);
void DFX_create(LinkList &head,int n);
void DFX_display(LinkList &head);
void chazhaocharu(LinkList &head,int n);
void nizhi(LinkList &head);
void nizhihebing(LinkList &head3_1,LinkList &head1,LinkList &head2);
void charu(LinkList &head);
void shanchu(LinkList &head);
void hebing(LinkList &head3_1,LinkList &head1,LinkList &head2);
void jiaoji(LinkList &head3_1,LinkList &head1,LinkList &head2);
void Shanchu(LinkList &head);
void zfzguolv(LinkList &head);
void menu(LinkList &head3_1,LinkList &head1,LinkList &head2,int n);
void welcome(LinkList &head3_1,LinkList &head1,LinkList &head2,int n);
void DFX_init(LinkList &head)//构造一个空链表head
{
    head=new LNode;head->next=NULL;
    cout<<"已初始化单向非循环链表(已有头结点,头结点->next空)"<<endl;
}
void DFX_create(LinkList &head,int n)
{
    LNode *linshihead,*p;//*linshihead是尾指针
    linshihead=head;//尾指针初始化,指向头结点
    cout<<"在该单向非循环链表中你想建立多少个结点?(除头结点)";cin>>n;
    for(int i=0;i<n;i++)
    {
        p=new LNode;
        cout<<"输入第"<<i+1<<"个结点要存放的数据:";cin>>p->data;p->next=NULL;
        linshihead->next=p;//尾插
        linshihead=p;//尾指针后移
    }
    cout<<"已新建单向非循环链表(含"<<n<<"个结点)";
}
void DFX_display(LinkList &head)//显示链表中所有结点的数据
{
    LNode *linshihead;linshihead=head;
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
void chazhaocharu(LinkList &head,int n)//根据用户输入的新结点,查找适合的新结点插入位置
{
    LNode *linshihead,*p;linshihead=head;
    p=new LNode;p->next=NULL;
    cout<<"输入新增结点要存放的数据:";cin>>p->data;
    for(int i=0;i<n;i++)
    {
        if(linshihead->next->next==NULL)
        {
            linshihead->next->next=p;
            break;
        }
        if(linshihead->next->data<p->data)
        {
            if(linshihead->next->next->data<p->data)
            {
                linshihead=linshihead->next;
            }
            else
            {
                p->next=linshihead->next->next;
                linshihead->next->next=p;
                break;
            }
        }
        else
        {
            p->next=linshihead->next;
            linshihead->next=p;
            break;
        }
    }
}
void nizhi(LinkList &head)
{
    LNode *linshihead,*p1=NULL,*p2=NULL;
    linshihead=head->next;
    head->next=NULL;
    while(linshihead!=NULL)
    {
        p2=linshihead->next;
        linshihead->next=p1;
        p1=linshihead;
        linshihead=p2;
    }
    head->next=p1;
}
void nizhihebing(LinkList &head3_1,LinkList &head1,LinkList &head2)
{
    LNode *linshihead3_1,*linshihead1,*linshihead2,*p;
    linshihead1=head1->next;linshihead2=head2->next;
    head3_1=head1;
    linshihead3_1=head3_1;
    head3_1->next=NULL;
    while(linshihead1||linshihead2)
    {
        if(!linshihead1)
        {
            p=linshihead2;
            linshihead2=linshihead2->next;
        }
        else if(!linshihead2)
        {
            p=linshihead1;
            linshihead1=linshihead1->next;
        }
        else if(linshihead1->data<=linshihead2->data)
        {
            p=linshihead1;
            linshihead1=linshihead1->next;
        }
        else
        {
            p=linshihead2;
            linshihead2=linshihead2->next;
        }
        p->next=head3_1->next;
        head3_1->next=p;
    }
    delete head2;
}
void charu(LinkList &head)//由用户直接确定新结点插入位置
{
    cout<<"你想在该单向非循环链表第几个结点后插入新结点?";
    int i,j=0;cin>>i;i=i+1;
    LNode *linshihead,*p;linshihead=head;
    while((linshihead)&&(j<i-1))
    {
        linshihead=linshihead->next;
        ++j;
    }
    if(!linshihead||(j>i-1))
    {
        cout<<"错误,即将结束程序";
        exit(0);
    }
    p=new LNode;
    cout<<"输入新结点要存放的数据:";cin>>p->data;
    p->next=linshihead->next;
    linshihead->next=p;
}
void shanchu(LinkList &head)
{
    cout<<"你想删除该单向非循环链表的第几个元素?";
    int i,j=0;cin>>i;
    LNode *linshihead,*p;linshihead=head;
    while((linshihead->next)&&(j<i-1))
    {
        linshihead=linshihead->next;
        ++j;
    }
    if(!(linshihead->next)||(j>i-1))
    {
        cout<<"错误,即将结束程序";
        exit(0);
    }
    p=linshihead->next;
    linshihead->next=p->next;
    delete p;
}
void hebing(LinkList &head3_1,LinkList &head1,LinkList &head2)//将2个递增单向非循环链表合并为1个递增单向链表,合并后的单向非循环链表使用第1条单向非循环链表的地址,释放第2条单向非循环链表的头指针
{
    LNode *linshihead3_1,*linshihead1,*linshihead2;
    linshihead1=head1->next;linshihead2=head2->next;
    head3_1=head1;
    linshihead3_1=head3_1;
    while(linshihead1&&linshihead2)
    {
        if(linshihead1->data<linshihead2->data)
        {
            linshihead3_1->next=linshihead1;
            linshihead3_1=linshihead1;
            linshihead1=linshihead1->next;
        }
        else if(linshihead1->data==linshihead2->data)
        {
            linshihead3_1->next=linshihead1;
            linshihead3_1=linshihead1;
            linshihead1=linshihead1->next;
            linshihead2=linshihead2->next;
        }
        else
        {
            linshihead3_1->next=linshihead2;
            linshihead3_1=linshihead2;//linshihead2指向已揪出的那个
            linshihead2=linshihead2->next;
        }
    }
    linshihead3_1->next=linshihead1?linshihead1:linshihead2;
    delete head2;
}
void jiaoji(LinkList &head3_1,LinkList &head1,LinkList &head2)
{
    int i=0;
    LNode *linshihead3_1,*linshihead1,*linshihead2;
    linshihead1=head1->next;linshihead2=head2->next;
    head3_1=head1;
    linshihead3_1=head3_1;
    while(linshihead1&&linshihead2)
    {
        if(linshihead1->data<linshihead2->data)
        {
            linshihead1=linshihead1->next;
        }
        else if(linshihead1->data==linshihead2->data)
        {
            linshihead3_1->next=linshihead1;
            linshihead3_1=linshihead1;
            linshihead1=linshihead1->next;
            linshihead2=linshihead2->next;
            linshihead3_1->next=NULL;
            i++;
        }
        else
        {
            linshihead2=linshihead2->next;
        }
    }
    if(i==0)
    {
        head3_1->next=NULL;cout<<"无交集";
    }
    delete head2;
}
void Shanchu(LinkList &head)
{
    if(!head)
    {
        cout<<"已删除单向非循环链表并释放存储空间"<<endl;
    }
    else
    {
        delete head;cout<<"已删除单向非循环链表并释放存储空间"<<endl;
    }
}
void zfzguolv(LinkList &head)
{
    LNode *linshi=NULL,*q=NULL;
    linshi=head;
    while(linshi->next!=NULL)
    {
        if(linshi->data!=linshi->next->data)
        {
            linshi=linshi->next;
        }
        else
        {
            q=linshi->next;
            linshi->next=q->next;
            delete q;
        }
    }
}
void menu(LinkList &head3_1,LinkList &head1,LinkList &head2,int n)
{
    int c,d;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|              (1)插数                 |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|              (2)逆置                 |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|              (3)逆置合并             |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|              (4)插入                 |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|              (5)删除                 |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|              (6)合并                 |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|              (7)交集                 |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|              (8)重复值过滤           |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|              (9)返回                 |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    do{
        cin>>c;
        if(c<1||c>8)
        {
            cout<<"(输入有误)(1-8)";
            d=1;
            getchar();
        }
        else
            d=0;
    }while(d==1);
    switch(c)
    {
        case 1:
            chazhaocharu(head1,n);
            DFX_display(head1);
            break;
        case 2:
            nizhi(head1);
            DFX_display(head1);
            break;
        case 3:
            cout<<"执行此功能还需创建一条单向非循环链表"<<endl;
            DFX_init(head2);DFX_create(head2,n);DFX_display(head2);
            DFX_init(head3_1);
            nizhihebing(head3_1,head1,head2);
            DFX_display(head3_1);
            Shanchu(head3_1);Shanchu(head1);Shanchu(head2);
            DFX_init(head1);DFX_create(head1,n);DFX_display(head1);
            break;
        case 4:
            charu(head1);
            DFX_display(head1);
            break;
        case 5:
            shanchu(head1);
            DFX_display(head1);
            break;
        case 6:
            cout<<"执行此功能还需创建一条单向非循环链表"<<endl;
            DFX_init(head2);DFX_create(head2,n);DFX_display(head2);
            DFX_init(head3_1);
            hebing(head3_1,head1,head2);
            DFX_display(head3_1);
            Shanchu(head3_1);Shanchu(head1);Shanchu(head2);
            DFX_init(head1);DFX_create(head1,n);DFX_display(head1);
            break;
        case 7:
            cout<<"执行此功能还需创建一条单向非循环链表"<<endl;
            DFX_init(head2);DFX_create(head2,n);DFX_display(head2);
            DFX_init(head3_1);
            jiaoji(head3_1,head1,head2);
            DFX_display(head3_1);
            Shanchu(head3_1);Shanchu(head1);Shanchu(head2);
            DFX_init(head1);DFX_create(head1,n);DFX_display(head1);
            break;
        case 8:
            zfzguolv(head1);
            DFX_display(head1);
            break;
        case 9:
            welcome(head3_1,head1,head2,n);
            break;
    }
    welcome(head3_1,head1,head2,n);
}
void welcome(LinkList &head3_1,LinkList &head1,LinkList &head2,int n)
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
            menu(head3_1,head1,head2,n);
            break;
        case 'N':
            exit(0);
    }
}
main()
{
    LinkList head1=NULL;
    LinkList head2=NULL;
    LinkList head3_1=NULL;
    int n;
    DFX_init(head1);
    DFX_create(head1,n);
    DFX_display(head1);
    welcome(head3_1,head1,head2,n);
}
