#include<iostream>
#include<string.h>
#include"PEOPLE.h"
#include"DATE.h"
#include"STUDENT.h"
using namespace std;
STUDENT::STUDENT()
{
    cout<<"calling constructor without parameters of STUDENT"<<endl;    //����STUDENT���޲ι��캯��
}
STUDENT::STUDENT(char NUMBER[N],char ID1[N],char SEX[N],int YEAR,int MONTH,int DAY,char SCHOOL[N],char COLLEGE[N],char MAJOR[N],int _CLASS,int SCORE):PEOPLE(NUMBER,ID1,SEX,YEAR,MONTH,DAY)
{
    strcpy(school,SCHOOL);
    strcpy(college,COLLEGE);
    strcpy(major,MAJOR);
    _class=_CLASS;
    score=SCORE;
    cout<<"calling constructor with parameters of STUDENT"<<endl;    //����STUDENT���вι��캯��
}
STUDENT::STUDENT(STUDENT &s):PEOPLE(s)
{
    strcpy(school,s.school);
    strcpy(college,s.college);
    strcpy(major,s.major);
    _class=s._class;
    score=s.score;
    cout<<"calling the copy constructor of STUDENT"<<endl;    //����STUDENT�ิ�ƹ��캯��
}
STUDENT::~STUDENT()
{
    cout<<"calling destructor of STUDENT"<<endl;    //����STUDENT����������
}
void STUDENT::Cin()
{
    cout<<"�������ѧ������ѧУ ѧԺ רҵ ���ڰ༶ ��ѧ�ɼ�:";
    cin>>school;
    cin>>college;
    cin>>major;
    cin>>_class;
    cin>>score;
}
void STUDENT::Cout()
{
    cout<<"ѧУ:"<<school<<endl;
    cout<<"ѧԺ:"<<college<<endl;
    cout<<"רҵ:"<<major<<endl;
    cout<<"���ڰ༶:"<<_class<<"��"<<endl;
    cout<<"��ѧ�ɼ�:"<<score<<"��"<<endl;
}
