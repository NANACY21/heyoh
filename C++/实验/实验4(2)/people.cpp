#include<iostream>
#include<string.h>
#include"PEOPLE.h"
#include"DATE.h"
using namespace std;
PEOPLE::PEOPLE():birthday()
{

}
PEOPLE::PEOPLE(char NUMBER[N],char ID1[N],char SEX[N],int YEAR,int MONTH,int DAY):birthday(YEAR,MONTH,DAY)
{
    strcpy(number,NUMBER);
    strcpy(ID,ID1);
    strcpy(sex,SEX);
}
PEOPLE::PEOPLE(PEOPLE &p)
{
    strcpy(number,p.number);
    strcpy(ID,p.ID);
    strcpy(sex,p.sex);
    birthday=p.birthday;
}
PEOPLE::~PEOPLE()
{
    cout<<number<<"����Ա�Ѿ�¼��"<<endl;
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
