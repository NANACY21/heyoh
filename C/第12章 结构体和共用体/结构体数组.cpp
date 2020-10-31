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
    char studentName[N];
    char studentSex[N];
    DATE birthday;
    int score[4];
}STUDENT;
main()
{
    int i,j,a[30];
    STUDENT b[4]={
                   {20166101,"小明","男",{1998,02,26},{78,79,80,81}},
                   {20166102,"小刚","女",{1999,03,12},{68,69,70,71}},
                   {20166103,"小华","男",{1999,05,21},{58,59,60,61}},
                   {20166104,"小强","女",{1997,05,20},{48,49,50,51}},
                  };
    for(i=0;i<4;i++)
    {
        a[i]=0;
        for(j=0;j<4;j++)
        {
            a[i]=a[i]+b[i].score[j];
        }
        printf("%d %s %s 生日:%d年%d月%d日 4科平均分:%.2f\n",b[i].studentID,b[i].studentName,b[i].studentSex,b[i].birthday.year,b[i].birthday.month,b[i].birthday.day,a[i]/4.0);
    }
}



