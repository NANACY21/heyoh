#include<stdio.h>
#define M 5
#define N 3
void InputScore(int a[M][N])
{
    int i,j;
    for(i=0;i<M;i++)
    {
        printf("请输入第%d个学生的数语外3科成绩(学号2016610%d)\n",i+1,i+1);
        for(j=0;j<N;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
}
void MathAverageScore(int (*a)[N])
{
    int j,b=0;
    for(j=0;j<M;j++)
    {
        b=b+*(a[j]);
    }
    printf("此班数学平均分是%.2f\n",b/5.0);
}
void Fail(int (*a)[N])
{
    printf("该班的不及格生如下:\n");
    int i,j;
    for(i=0;i<M;i++)
    {
        int k=0,sum=0;
        for(j=0;j<N;j++)
        {
            if(*(a[i]+j)<60)
            {
                k++;
            }
        }
        if(k>=2)
        {
            printf("2016610%d ",i+1);
            printf("3科成绩:");
            for(j=0;j<N;j++)
            {
                printf("%d ",*(a[i]+j));
                sum=sum+*(a[i]+j);
            }
            printf("平均分:");
            printf("%.2f\n",sum/3.0);
        }
    }
}
void NiceScore(int (*a)[N])
{
    printf("3科平均分超过90分或每科都高于85分的学生如下:\n");
    int i,j;
    for(i=0;i<M;i++)
    {
        int k=0,sum=0;
        for(j=0;j<N;j++)
        {
            if(*(a[i]+j)>85)
            {
                k++;
            }
            sum=sum+*(a[i]+j);
        }
        if(((sum/3.0)>90)||(k==3))
        {
            printf("2016610%d\n",i+1);
        }
    }
}
main()
{
    int Score[M][N];
    InputScore(Score);
    printf("程序运行结果:\n");
    MathAverageScore(Score);
    Fail(Score);
    NiceScore(Score);
}

