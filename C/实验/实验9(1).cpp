#include<stdio.h>
#define M 5
#define N 3
typedef struct date
{
    int year;
    int month;
    int day;
}DATE;
typedef struct student
{
    long studentID;
    char studentName[M];
    char studentSex[M];
    DATE birthday;
    int score[N];
    float averscore;
}STUDENT;
void InputScore(STUDENT a[],int m,int n)
{
    int i,j;
    printf("输入学生信息(姓名 性别 出生年 月 日 第1科高数成绩 第2科线代成绩 第3科C语言成绩)\n");
    for(i=0;i<m;i++)
    {
        printf("%d.(学号2016610%d):\n",i+1,i+1);
        scanf("%s %s %d %d %d",a[i].studentName,a[i].studentSex,&a[i].birthday.year,&a[i].birthday.month,&a[i].birthday.day);
        for(j=0;j<n;j++)
        {
            scanf("%d",&a[i].score[j]);
        }
    }
}
void AverageScore(STUDENT *a,int m,int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        int sum=0;
        for(j=0;j<m;j++)
        {
            sum=sum+((a+j)->score[i]);
        }
        printf("第%d科课平均分:%.2f\n",i+1,sum/5.0);
    }
}
void MaxScore(STUDENT *a,int m,int n)
{
    int i,j,k=0,l;
    for(i=0;i<n;i++)
    {
        int max=((a+0)->score[i]);
        for(j=0;j<m;j++)
        {
            if(max<((a+j)->score[i]))
            {
                max=((a+j)->score[i]);
                l=j+1;
                k++;
            }
        }
        if(k!=0)
        {
            printf("第%d科课成绩最高的学生学号:2016610%d\n",i+1,l);
        }
        else
        {
            printf("第%d科课成绩最高的学生学号:20166101\n",i+1);
        }
    }
}
void Paixu(STUDENT stu[],int m,int n)
{
    int i,j;
    STUDENT t;
    for(i=0;i<m;i++)
    {
        stu[i].averscore=0;
        for(j=0;j<n;j++)
        {
            stu[i].averscore=stu[i].averscore+(stu[i].score[j]);
        }
        stu[i].averscore=(stu[i].averscore)/3.0;
        printf("2016610%d的3科平均分:%.2f\n",i+1,stu[i].averscore);
    }
    printf("每个人按平均分从大到小的顺序排序是:\n");
    for(i=0;i<m-1;i++)
    {
        for(j=i+1;j<m;j++)
        {
            if(stu[i].averscore < stu[j].averscore)
            {
                t=stu[i];
                stu[i]=stu[j];
                stu[j]=t;
            }
        }
    }
    for(i=0;i<m;i++)
    {
        printf("%s\n",stu[i].studentName);
    }
}
main()
{
    STUDENT a[M];
    InputScore(a,M,N);
    AverageScore(a,M,N);
    MaxScore(a,M,N);
    Paixu(a,M,N);
}

