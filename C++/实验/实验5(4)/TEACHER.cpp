#include<iostream>
#include<string.h>
#include"PEOPLE.h"
#include"DATE.h"
#include"TEACHER.h"
using namespace std;
TEACHER::TEACHER()
{
    cout<<"calling constructor without parameters of TEACHER"<<endl;    //����TEACHER���޲ι��캯��
}
TEACHER::TEACHER(char NUMBER[N],char ID1[N],char SEX[N],int YEAR,int MONTH,int DAY,char JOB[N],char DEPARTMENT[N],char JOB_TITLE[N]):PEOPLE(NUMBER,ID1,SEX,YEAR,MONTH,DAY)
{
    strcpy(job,JOB);
    strcpy(department,DEPARTMENT);
    strcpy(job_title,JOB_TITLE);
    cout<<"calling constructor with parameters of TEACHER"<<endl;    //����TEACHER���вι��캯��
}
TEACHER::TEACHER(TEACHER &t):PEOPLE(t)
{
    strcpy(job,t.job);
    strcpy(department,t.department);
    strcpy(job_title,t.job_title);
    cout<<"calling the copy constructor of TEACHER"<<endl;    //����TEACHER�ิ�ƹ��캯��
}
TEACHER::~TEACHER()
{
    cout<<"calling destructor of TEACHER"<<endl;    //����TEACHER����������
}
void TEACHER::Cin()
{
    cout<<"������ý�ʦ��ְ�� ���ڲ��� ְ��:";
    cin>>job;
    cin>>department;
    cin>>job_title;
}
void TEACHER::Cout()
{
    cout<<"ְ��:"<<job<<endl;
    cout<<"���ڲ���:"<<department<<endl;
    cout<<"ְ��:"<<job_title<<endl;
}
