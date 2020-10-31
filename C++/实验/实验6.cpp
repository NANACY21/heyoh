#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<string>
#include<string.h>
#include<stdlib.h>
#define N 20
using namespace std;
class STUDENT
{
public:
    string name; //学生姓名
    int math_score,chinese_score,english_score,physics_score,chemistry_score,biology_score; //六科课分数
    int aggregate_score; //总分
    STUDENT *next;
    friend ostream &operator<<(ostream &stream,STUDENT &a)
    {
        stream<<left<<setw(8)<<a.name<<left<<setw(6)<<a.math_score<<left<<setw(6)<<a.chinese_score<<left<<setw(6)<<a.english_score<<left<<setw(6)<<a.physics_score
        <<left<<setw(6)<<a.chemistry_score<<left<<setw(6)<<a.biology_score<<left<<setw(6)<<a.aggregate_score<<endl;
        return stream;
    }
};
STUDENT *delete_student(STUDENT *head);
void add_student(int,STUDENT **);
void show_all_student(STUDENT *);
void change_student_score(STUDENT *head);
void deletee(STUDENT *);
void menu(STUDENT *);
main()
{
    int n;
    cout<<"输入该班级学生人数 ";
    cin>>n;
    STUDENT *head=NULL;
    add_student(n,&head);
    A:menu(head);
    goto A;
    deletee(head);
}
void add_student(int n,STUDENT **p)
{
    int i=1;
    STUDENT *a;
    STUDENT *b;
    a=new STUDENT;
    *p=a;
    while(i<=n)
    {
        b=a;
        cout<<"第"<<i<<"个学生"<<endl;
        cout<<"姓名 ";
        cin>>b->name;
        cout<<b->name<<"的六科成绩"<<endl;
        cout<<"数学 ";cin>>b->math_score;
        cout<<"语文 ";cin>>b->chinese_score;
        cout<<"英语 ";cin>>b->english_score;
        cout<<"物理 ";cin>>b->physics_score;
        cout<<"化学 ";cin>>b->chemistry_score;
        cout<<"生物 ";cin>>b->biology_score;
        b->aggregate_score=(b->math_score)+(b->chinese_score)+(b->english_score)+(b->physics_score)+(b->chemistry_score)+(b->biology_score);
        a=new STUDENT;
        b->next=a;
        i++;
    }
    b->next=NULL;
    a=NULL;
    b=NULL;
    cout<<"已新增"<<i-1<<"个学生"<<endl;
}
STUDENT *delete_student(STUDENT *head)
{
    string name;
    cout<<"输入学生姓名,删除该学生 ";
    cin>>name;
    STUDENT *p=head,*pr=head;
    if(head==NULL)
    {
        return head;
    }
    while(name!=p->name&&p->next!=NULL)
    {
        pr=p;
        p=p->next;
    }
    if(name==p->name)
    {
        if(p==head)
        {
            head=p->next;
        }
        else
        {
            pr->next=p->next;
        }
        free(p);
    }
    else
    {
        cout<<"未找到该学生";
    }
    return head;

}
void change_student_score(STUDENT *head)
{
    string name;
    cout<<"输入学生姓名,修改其成绩 ";
    cin>>name;
    STUDENT *p=head,*pr=head;
    if(head==NULL)
    {
        cout<<"失败";
    }
    while(name!=p->name&&p->next!=NULL)
    {
        pr=p;
        p=p->next;
    }
    if(name==p->name)
    {
        int j,k;
        cout<<"选择更改科目(1)数学(2)语文(3)英语(4)物理(5)化学(6)生物 ";
        do{
            cin>>j;
            if(j<1||j>6)
            {
                cout<<"(输入有误)(1-6)";
                k=1;
                getchar();
            }
            else
                k=0;
        }while(k==1);
        switch(j)
        {
            case 1:
                int MATH_SCORE;
                cout<<"输入"<<p->name<<"新的数学分数 ";
                cin>>MATH_SCORE;
                p->math_score=MATH_SCORE;
                p->aggregate_score=(p->math_score)+(p->chinese_score)+(p->english_score)+(p->physics_score)+(p->chemistry_score)+(p->biology_score);
                break;
            case 2:
                int CHINESE_SCORE;
                cout<<"输入"<<p->name<<"新的语文分数 ";
                cin>>CHINESE_SCORE;
                p->chinese_score=CHINESE_SCORE;
                p->aggregate_score=(p->math_score)+(p->chinese_score)+(p->english_score)+(p->physics_score)+(p->chemistry_score)+(p->biology_score);
                break;
            case 3:
                int ENGLISH_SCORE;
                cout<<"输入"<<p->name<<"新的英语分数 ";
                cin>>ENGLISH_SCORE;
                p->english_score=ENGLISH_SCORE;
                p->aggregate_score=(p->math_score)+(p->chinese_score)+(p->english_score)+(p->physics_score)+(p->chemistry_score)+(p->biology_score);
                break;
            case 4:
                int PHYSICS_SCORE;
                cout<<"输入"<<p->name<<"新的物理分数 ";
                cin>>PHYSICS_SCORE;
                p->physics_score=PHYSICS_SCORE;
                p->aggregate_score=(p->math_score)+(p->chinese_score)+(p->english_score)+(p->physics_score)+(p->chemistry_score)+(p->biology_score);
                break;
            case 5:
                int CHEMISTRY_SCORE;
                cout<<"输入"<<p->name<<"新的化学分数 ";cin>>CHEMISTRY_SCORE;
                p->chemistry_score=CHEMISTRY_SCORE;
                p->aggregate_score=(p->math_score)+(p->chinese_score)+(p->english_score)+(p->physics_score)+(p->chemistry_score)+(p->biology_score);
                break;
            case 6:
                int BIOLOGY_SCORE;
                cout<<"输入"<<p->name<<"新的生物分数 ";cin>>BIOLOGY_SCORE;
                p->biology_score=BIOLOGY_SCORE;
                p->aggregate_score=(p->math_score)+(p->chinese_score)+(p->english_score)+(p->physics_score)+(p->chemistry_score)+(p->biology_score);
                break;
        }
    }
}
void show_all_student(STUDENT *head)
{
    STUDENT *p1;
    STUDENT *p2;
    p1=head;
    p2=p1;
    cout<<"        "<<left<<setw(6)<<"数学"<<left<<setw(6)<<"语文"<<left<<setw(6)<<"英语"<<left<<setw(6)<<"物理"<<left<<setw(6)<<"化学"<<left<<setw(6)<<"生物"<<left<<setw(6)<<"总分"<<endl;
    while(p2!=NULL)
    {
        cout<<left<<setw(8)<<p2->name<<left<<setw(6)<<p2->math_score<<left<<setw(6)<<p2->chinese_score<<left<<setw(6)<<p2->english_score
        <<left<<setw(6)<<p2->physics_score<<left<<setw(6)<<p2->chemistry_score<<left<<setw(6)<<p2->biology_score<<left<<setw(6)<<p2->aggregate_score;
        p1=p2;
        p2=p1->next;
        puts("");
    }
}
void deletee(STUDENT *p)
{
    STUDENT *p1;
    STUDENT *p2;
    p1=p;
    p2=p1;
    while(p2->next!=NULL)
    {
        p1=p2->next;
        delete p2;
        p2=p1;
    }
}
void menu(STUDENT *head)
{
    int c,d;
    cout<<"----------------------------------------"<<endl;
    cout<<"|           学生成绩管理系统           |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|              (1)显示成绩             |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|              (2)更改成绩             |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"|              (3)删除学生             |"<<endl;
    cout<<"|--------------------------------------|"<<endl;
    cout<<"                  (1-3)";
    do{
        cin>>c;
        if(c<1||c>3)
        {
            cout<<"        (输入有误)(1-3)";
            d=1;
            getchar();
        }
        else
            d=0;
    }while(d==1);
    switch(c)
    {
        case 1:
            show_all_student(head);
            break;
        case 2:
            change_student_score(head);
            //show_all_student(head);
            break;
        case 3:
            head=delete_student(head);
            //show_all_student(head);
            break;
    }
}
//王帅,孙霜洪,王磊,刘笑非,李篪
