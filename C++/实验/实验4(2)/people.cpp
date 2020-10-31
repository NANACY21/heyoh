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
    cout<<number<<"号人员已经录入"<<endl;
}
void PEOPLE::Cin()
{
    cout<<"请输入(录入)数据: number(编号) ID(身份证号) sex(性别) birthday(出生日期)"<<endl;
    cin>>number;
    cin>>ID;
    cin>>sex;
    birthday.Cin();
}
void PEOPLE::Cout()
{
    cout<<"编号:"<<number<<endl;
    cout<<"身份证号:"<<ID<<endl;
    cout<<"性别:"<<sex<<endl;
    cout<<"生日:";
    birthday.Cout();
    cout<<endl;
}
