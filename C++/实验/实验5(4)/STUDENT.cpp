#include<iostream>
#include<string.h>
#include"PEOPLE.h"
#include"DATE.h"
#include"STUDENT.h"
using namespace std;
STUDENT::STUDENT()
{
    cout<<"calling constructor without parameters of STUDENT"<<endl;    //调用STUDENT类无参构造函数
}
STUDENT::STUDENT(char NUMBER[N],char ID1[N],char SEX[N],int YEAR,int MONTH,int DAY,char SCHOOL[N],char COLLEGE[N],char MAJOR[N],int _CLASS,int SCORE):PEOPLE(NUMBER,ID1,SEX,YEAR,MONTH,DAY)
{
    strcpy(school,SCHOOL);
    strcpy(college,COLLEGE);
    strcpy(major,MAJOR);
    _class=_CLASS;
    score=SCORE;
    cout<<"calling constructor with parameters of STUDENT"<<endl;    //调用STUDENT类有参构造函数
}
STUDENT::STUDENT(STUDENT &s):PEOPLE(s)
{
    strcpy(school,s.school);
    strcpy(college,s.college);
    strcpy(major,s.major);
    _class=s._class;
    score=s.score;
    cout<<"calling the copy constructor of STUDENT"<<endl;    //调用STUDENT类复制构造函数
}
STUDENT::~STUDENT()
{
    cout<<"calling destructor of STUDENT"<<endl;    //调用STUDENT类析构函数
}
void STUDENT::Cin()
{
    cout<<"请输入该学生所在学校 学院 专业 所在班级 入学成绩:";
    cin>>school;
    cin>>college;
    cin>>major;
    cin>>_class;
    cin>>score;
}
void STUDENT::Cout()
{
    cout<<"学校:"<<school<<endl;
    cout<<"学院:"<<college<<endl;
    cout<<"专业:"<<major<<endl;
    cout<<"所在班级:"<<_class<<"班"<<endl;
    cout<<"入学成绩:"<<score<<"分"<<endl;
}
