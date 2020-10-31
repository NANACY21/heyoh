//函数fopen()用来打开文件，返回值是一个地址
//函数fclose()用来关闭文件，文件关闭成功返回0值，否则返回非0值
//函数fgetc()用于从一个以只读或读写方式打开的文件上读字符
//函数fputc()用于将一个字符写到一个文件上
//同时打开的文件数目是有限制的
#include<stdio.h>
#include<stdlib.h>
#define M 5
#define N 3
typedef struct student
{
    long studentID;
    char studentName[M];
    int score[N];
    float averscore;
}STUDENT;
void Inputscore(STUDENT stu[],int m,int n)
{
    int i,j;
    printf("输入学生信息(学号 姓名 第一科高数成绩 第二科线性代数成绩 第三科C语言成绩)\n");
    for(i=0;i<m;i++)
    {
        printf("%d.(学号2016610%d):\n",i+1,i+1);
        scanf("%d %s",&stu[i].studentID,stu[i].studentName);
        for(j=0;j<n;j++)
        {
            scanf("%d",&stu[i].score[j]);
        }
    }
}
void MC(STUDENT stu[],int m,int n)
{
    int i,j;
    for(i=0;i<m;i++)
    {
        stu[i].averscore=0;
        for(j=0;j<n;j++)
        {
            stu[i].averscore=stu[i].averscore+(stu[i].score[j]);
        }
        stu[i].averscore=(stu[i].averscore)/3.0;
    }
}
void WritetoFile(STUDENT stu[],int m,int n)
{
    FILE *a;
    int i,j;
    if((a=fopen("D:\\STUD.txt","w"))==NULL)    //判断文件是否成功打开
    {
        printf("打开.txt格式的演示失败!\n");
        exit(0);
    }
    for(i=0;i<m;i++)
    {
        fprintf(a,"%d %s ",stu[i].studentID,stu[i].studentName);
        for(j=0;j<n;j++)
        {
            fprintf(a,"%d ",stu[i].score[j]);
        }
        fprintf(a,"%.2f",stu[i].averscore);
        fprintf(a,"\n");
    }
    fclose(a);    //关闭由函数fopen()打开的fp指向的文件
}
void ReadfromFile(STUDENT stu[])
{
    int i,j;
    FILE *a;
    if((a=fopen("D:\\STUD.tet","r"))==NULL)
    {
        printf("打开.txt格式的演示失败!\n");
        exit(0);
    }
    for(i=0;i<M;i++)
    {
        fscanf(a,"%d",&stu[i].studentID);
        fscanf(a,"%s",stu[i].studentName);
        for(j=0;j<N;j++)
        {
            fscanf(a,"%d",&stu[i].score[j]);
        }
        fscanf(a,"%f",&stu[i].averscore);
    }
    fclose(a);
}
void PrintfInformation(STUDENT stu[],long a)
{
    int i,j;
    for(i=0;i<M;i++)
    {
        if(stu[i].studentID==a)
        {
            printf("%ld %s ",stu[i].studentID,stu[i].studentName);
            for(j=0;j<N;j++)
            {
                printf("%4d",stu[i].score[j]);
            }
            printf("%6.2f",stu[i].averscore);
            break;
        }
    }
}
main()
{
    STUDENT stu[M],Stu[M];
    long a;
    Inputscore(stu,M,N);
    MC(stu,M,N);
    WritetoFile(stu,M,N);
    printf("请输入一个学生的学号,以在屏幕显示该学号学生信息:");
    scanf("%ld",&a);
    ReadfromFile(Stu);
    PrintfInformation(Stu,a);
}
