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
    STUDENT a("20166109","230107199802221213","男",1998,02,22,"黑龙江大学","软件学院","软件工程",8,100),b(a);
    TEACHER c("20166109","230107199802221213","男",1998,02,22,"数学老师","数学学院","副教授");
    GRADUATE d("20166109","230107199802221213","男",1998,02,22,"黑龙江大学","软件学院","软件工程",8,100,"赵鹏","基于GPU的高性能计算");
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
