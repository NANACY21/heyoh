#include<stdio.h>
struct student
{
    long studentID;
    char studentName[10];
    char studentSex[5];
    int yearofBirth;
    int score[4];
}stu1;
typedef struct student STUDENT;
main()
{
    STUDENT stu1={20166109,"李篪","男",1998,{78,79,80,81}};
    STUDENT *pt;
    pt=&stu1;
    pt->studentID=20166110;
    printf("%d %s %s %d",stu1.studentID,stu1.studentName,stu1.studentSex,stu1.score[2]);
}
