#include<iostream>
#include<string.h>
#include"PEOPLE.h"
#include"DATE.h"
#include"TEACHER.h"
using namespace std;
TEACHER::TEACHER()
{
    cout<<"calling constructor without parameters of TEACHER"<<endl;    //调用TEACHER类无参构造函数
}
TEACHER::TEACHER(char NUMBER[N],char ID1[N],char SEX[N],int YEAR,int MONTH,int DAY,char JOB[N],char DEPARTMENT[N],char JOB_TITLE[N]):PEOPLE(NUMBER,ID1,SEX,YEAR,MONTH,DAY)
{
    strcpy(job,JOB);
    strcpy(department,DEPARTMENT);
    strcpy(job_title,JOB_TITLE);
    cout<<"calling constructor with parameters of TEACHER"<<endl;    //调用TEACHER类有参构造函数
}
TEACHER::TEACHER(TEACHER &t):PEOPLE(t)
{
    strcpy(job,t.job);
    strcpy(department,t.department);
    strcpy(job_title,t.job_title);
    cout<<"calling the copy constructor of TEACHER"<<endl;    //调用TEACHER类复制构造函数
}
TEACHER::~TEACHER()
{
    cout<<"calling destructor of TEACHER"<<endl;    //调用TEACHER类析构函数
}
void TEACHER::Cin()
{
    cout<<"请输入该教师的职务 所在部门 职称:";
    cin>>job;
    cin>>department;
    cin>>job_title;
}
void TEACHER::Cout()
{
    cout<<"职务:"<<job<<endl;
    cout<<"所在部门:"<<department<<endl;
    cout<<"职称:"<<job_title<<endl;
}
