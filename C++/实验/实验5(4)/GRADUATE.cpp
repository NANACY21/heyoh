#include<iostream>
#include<string.h>
#include"DATE.h"
#include"PEOPLE.h"
#include"STUDENT.h"
#include"GRADUATE.h"
using namespace std;
GRADUATE::GRADUATE()
{
    cout<<"calling constructor without parameters of GRADUATE"<<endl;    //调用GRADUATE类无参构造函数
}
GRADUATE::GRADUATE(char NUMBER[N],char ID1[N],char SEX[N],int YEAR,int MONTH,int DAY,char SCHOOL[N],char COLLEGE[N],char MAJOR[N],int _CLASS,int SCORE,char HIEROPHANT[N],char RESEARCH_AREA[N])
:STUDENT(NUMBER,ID1,SEX,YEAR,MONTH,DAY,SCHOOL,COLLEGE,MAJOR,_CLASS,SCORE)
{
    strcpy(hierophant,HIEROPHANT);
    strcpy(research_area,RESEARCH_AREA);
    cout<<"calling constructor with parameters of STUDENT"<<endl;    //调用STUDENT类有参构造函数
}
GRADUATE::GRADUATE(GRADUATE &g):STUDENT(g) //赋值兼容规则
{
    strcpy(hierophant,g.hierophant);
    strcpy(research_area,g.research_area);
    cout<<"calling the copy constructor of GRADUATE"<<endl;    //调用GRADUATE类复制构造函数
}
GRADUATE::~GRADUATE()
{
    cout<<"calling destructor of GRADUATE"<<endl;    //调用GRADUATE类析构函数
}
void GRADUATE::Cin()
{
    cout<<"请输入该研究生的导师 研究方向:";
    cin>>hierophant;
    cin>>research_area;
}
void GRADUATE::Cout()
{
    cout<<"导师:"<<hierophant<<endl;
    cout<<"研究方向:"<<research_area<<endl;
}
