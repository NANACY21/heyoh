#include<stdio.h>
#include<stdlib.h>
#define N 10
typedef struct student STUDENT;    //STUDENT作用<=>int
struct student
{
    long studentID;
    char studentName[N];
    char studentSex[N];
    int age;
    int score;
    STUDENT *next;
};
STUDENT *AppendNode(STUDENT *head)    //新建节点将其添加至链表的结尾,返回添加节点后的链表的头指针
{
    STUDENT *p=NULL,*pr=head;
    long studentID;
    char studentName[N];
    char studentSex[N];
    int age;
    int score;
    p=(STUDENT *)malloc(sizeof(STUDENT));    //新建节点的地址值赋值给p
    if(p==NULL)    //p如果是空地址
    {
        printf("没有足够的内存分配!\n");
        exit(0);
    }
    if(head==NULL)    //若原链表为空表
    {
        head=p;    //将新建节点的地址值赋值给head，head是头指针
    }
    else    //如果原链表不是空链表，则将这个新建的节点添加到链表的表尾
    {
        while(pr->next!=NULL)    //若没到表尾，则移动pr直到pr指向表尾
        {
            pr=pr->next;    //将pr节点的下一节点的地址值赋值给pr
        }
        pr->next=p;    //新建节点的地址值赋值给末节点的指针域
    }
    printf("输入节点数据 (学号 姓名 性别 年龄 C语言成绩)");
    scanf("%d %s %s %d %d",&studentID,&studentName,&studentSex,&age,&score);
    p->studentID=studentID;    //将输入的节点数据赋值给新建节点的数据域
    int i,j;
    for(i=0;i<N;i++)
    {
        p->studentName[i]=studentName[i];
    }
    for(j=0;j<N;j++)
    {
        p->studentSex[j]=studentSex[j];
    }
    p->age=age;
    p->score=score;
    p->next=NULL;    //将新建节点置为表尾
    return head;    //返回添加节点后的链表的头指针
}
void DisplyNode(STUDENT *head)    //显示链表中所有节点的数据
{
    STUDENT *p;
    p=head;
    int j=1;
    while(p!=NULL)    //若不是表尾，则循环打印节点的值
    {
        printf(" %d %d %s %s %d %d\n",j,p->studentID,p->studentName,p->studentSex,p->age,p->score);    //打印第j个节点的数据
        p=p->next;    //下一节点的地址值赋给p
        j++;
    }
}
void DeleteMemory(STUDENT *head)
{
    STUDENT *p=head,*pr=NULL;
    while(p!=NULL)
    {
        pr=p;
        p=p->next;
        free(pr);
    }
}
STUDENT *DeleteNode(STUDENT *head,long nodeData)    //删除链表中的任意一个节点
{
    STUDENT *p=head,*pr=head;
    if(head==NULL)    //若链表为空，退出程序
    {
        printf("链表为空!\n");
        return(head);
    }
    while(nodeData!=p->studentID&&p->next!=NULL)    //未找到该节点，且没到链表的结尾
    {
        pr=p;    //pr用于保存当前节点的地址值
        p=p->next;    //当前节点的下一节点的地址值赋值给p
    }
    if(nodeData==p->studentID)    //若当前节点的一个节点值为nodeData，则已找到该待删除节点
    {
        if(p==head)    //若待删除节点为头节点
        {
            head=p->next;    //把待删除节点的下一节点的地址值赋值给头指针
        }
        else    //若待删除节点不是头节点
        {
            pr->next=p->next;    //把待删除节点的下一节点的地址值赋值给待删节点的前一节点的指针域
        }
        free(p);
    }
    else
    {
        printf("这个节点没有找到!\n");
    }
    return head;
}
main()
{
    int i=0;
    char a;
    long nodeData;    //定义一个长整形变量
    STUDENT *head=NULL;    //定义一个头指针//先把空地址赋值给head
    printf("你想添加1个新的节点吗?(Y or N)");
    scanf("%c",&a);
    while(a=='y'||a=='Y')
    {
        head=AppendNode(head);    //新建节点将其添加添加至链表的结尾,返回添加节点后的链表的头指针
        DisplyNode(head);    //显示链表中所有节点的数据
        printf("你想添加1个新的节点吗?(Y or N)");
        scanf(" %c",&a);
        i++;
    }
    printf("已建立单向链表,%d个新节点已添加.\n",i);
    printf("输入一个学生的学号,以删除该学生的全部信息并重新显示该单项链表:");
    scanf("%d",&nodeData);
    head=DeleteNode(head,nodeData);    //删除链表中任意一个节点
    DisplyNode(head);    //重新显示链表中所有节点的数据
    DeleteMemory(head);
    printf("\n已完成.");
}




