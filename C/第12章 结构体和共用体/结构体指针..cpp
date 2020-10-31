#include<stdio.h>
#define N 10
typedef struct date
{
    int year;
    int month;
    int day;
}DATE;
typedef struct student
{
    long studentID;
    char studentName[10];
    char studentSex[5];
    DATE birthday;
    int score[4];
}STUDENT;
main()
{
    STUDENT stu[30]={{20166101,"小明","男",{1998,02,24},{88,79,80,81}},
                     {20166102,"小丽","女",{1998,03,12},{68,99,80,71}},
                     {20166103,"小华","男",{1998,05,21},{78,59,70,71}},
                     {20166104,"小强","女",{1998,07,20},{48,39,60,91}},
                    };
    STUDENT *pt;
    pt=stu;
    pt->score[0]=80;
    (pt+2)->birthday.year=1991;
    printf("%d",stu[2].birthday.year);
}
