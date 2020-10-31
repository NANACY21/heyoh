#include<iostream>
#include<string.h>
#include"DATE.h"
#include"PEOPLE.h"
using namespace std;
PEOPLE::PEOPLE():birthday()
{
    cout<<"calling constructor without parameters of PEOPLE"<<endl;    //����PEOPLE���޲ι��캯��
}
PEOPLE::PEOPLE(char NUMBER[N],char ID1[N],char SEX[N],int YEAR,int MONTH,int DAY):birthday(YEAR,MONTH,DAY)
{
    strcpy(number,NUMBER);
    strcpy(ID,ID1);
    strcpy(sex,SEX);
    cout<<"calling constructor with parameters of PEOPLE"<<endl;    //����PEOPLE���вι��캯��
}
PEOPLE::PEOPLE(PEOPLE &p)
{
    strcpy(number,p.number);
    strcpy(ID,p.ID);
    strcpy(sex,p.sex);
    birthday=p.birthday;
    cout<<"calling the copy constructor of PEOPLE"<<endl;    //����PEOPLE�ิ�ƹ��캯��
}
PEOPLE::~PEOPLE()
{
    cout<<number<<"����Ա�Ѿ�¼��"<<endl;
    cout<<"calling destructor of PEOPLE"<<endl;    //����PEOPLE����������
}
void PEOPLE::Cin()
{
    cout<<"������(¼��)����: number(���) ID(���֤��) sex(�Ա�) birthday(��������)"<<endl;
    cin>>number;
    cin>>ID;
    cin>>sex;
    birthday.Cin();
}
void PEOPLE::Cout()
{
    cout<<"���:"<<number<<endl;
    cout<<"���֤��:"<<ID<<endl;
    cout<<"�Ա�:"<<sex<<endl;
    cout<<"����:";
    birthday.Cout();
    cout<<endl;
}
