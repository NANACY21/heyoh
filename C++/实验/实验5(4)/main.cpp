#include<iostream>
#include<string.h>
#include"DATE.h"
#include"PEOPLE.h"
#include"STUDENT.h"
#include"TEACHER.h"
#include"GRADUATE.h"
using namespace std;
main()
{
    STUDENT a("20166109","230107199802221213","��",1998,02,22,"��������ѧ","���ѧԺ","�������",8,100),b(a);
    TEACHER c("20166109","230107199802221213","��",1998,02,22,"��ѧ��ʦ","��ѧѧԺ","������");
    GRADUATE d("20166109","230107199802221213","��",1998,02,22,"��������ѧ","���ѧԺ","�������",8,100,"����","����GPU�ĸ����ܼ���");
    a.PEOPLE::Cout();
    a.Cout();
    cout<<endl;
    b.PEOPLE::Cout();
    b.Cout();
    cout<<endl;
    a.PEOPLE::Cin();
    a.Cin();
    a.PEOPLE::Cout();
    a.Cout();
    cout<<endl;
    d.PEOPLE::Cout();
    d.STUDENT::Cout();
    d.Cout();
}
