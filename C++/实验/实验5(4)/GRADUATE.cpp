#include<iostream>
#include<string.h>
#include"DATE.h"
#include"PEOPLE.h"
#include"STUDENT.h"
#include"GRADUATE.h"
using namespace std;
GRADUATE::GRADUATE()
{
    cout<<"calling constructor without parameters of GRADUATE"<<endl;    //����GRADUATE���޲ι��캯��
}
GRADUATE::GRADUATE(char NUMBER[N],char ID1[N],char SEX[N],int YEAR,int MONTH,int DAY,char SCHOOL[N],char COLLEGE[N],char MAJOR[N],int _CLASS,int SCORE,char HIEROPHANT[N],char RESEARCH_AREA[N])
:STUDENT(NUMBER,ID1,SEX,YEAR,MONTH,DAY,SCHOOL,COLLEGE,MAJOR,_CLASS,SCORE)
{
    strcpy(hierophant,HIEROPHANT);
    strcpy(research_area,RESEARCH_AREA);
    cout<<"calling constructor with parameters of STUDENT"<<endl;    //����STUDENT���вι��캯��
}
GRADUATE::GRADUATE(GRADUATE &g):STUDENT(g) //��ֵ���ݹ���
{
    strcpy(hierophant,g.hierophant);
    strcpy(research_area,g.research_area);
    cout<<"calling the copy constructor of GRADUATE"<<endl;    //����GRADUATE�ิ�ƹ��캯��
}
GRADUATE::~GRADUATE()
{
    cout<<"calling destructor of GRADUATE"<<endl;    //����GRADUATE����������
}
void GRADUATE::Cin()
{
    cout<<"��������о����ĵ�ʦ �о�����:";
    cin>>hierophant;
    cin>>research_area;
}
void GRADUATE::Cout()
{
    cout<<"��ʦ:"<<hierophant<<endl;
    cout<<"�о�����:"<<research_area<<endl;
}
