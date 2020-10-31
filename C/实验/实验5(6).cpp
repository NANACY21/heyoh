#include<stdio.h>
#define N 40
#define M 3
void Readscore(int score[][M],long mun[],int n)
{
    int i,j,k;
    printf("Input student's ID and score as: MT EN PH:\n");
    for (i=0;i<n;i++)
    {
        scanf("%ld",&mun[i]);
        for (j=0;j<M;j++)
        {
            do{
                scanf("%d",&k);
                if(k<0||k>100)
                    printf("Input the score(0-100):");
            }while(k<0||k>100);
            score[i][j]=k;
        }
    }
    return;
}
/*计算学生的总分和平均分*/
void AverforStud(int score[][M],int sum[],float aver[],int n)
{
    int i,j;
    for (i=0;i<n;i++)
    {
        sum[i]=0;
        for(j=0;j<M;j++)
        {
            sum[i]=sum[i]+score[i][j];
        }
        aver[i]=(float)sum[i]/M;
    }
    for (i=0;i<n;i++)
    {
        printf("第%d个学生的总分和总平均分:",i+1);
        printf("%d %.1f\n",sum[i],aver[i]);
    }
}
void MAX (int score[][M],int n,int max[M],long stud[N],long mun[N])
{
    int k,i,m=0;
    for (i=0;i<M;i++)
    {
        for (k=0;k<n;k++)
        {
            if (score[k][i]>score[m][i])
            {
                m=k;
            }
        }
        max[i]=score[m][i];
        stud[i]=mun[m];
    }
    for (i=0;i<M;i++)
    {
        switch (i)
        {
            case 0:
                printf("Max score of student'ID and max MT score:");
                printf("%ld %d\n",stud[i],max[i]);
                break;
            case 1:
                printf("Max score of student'ID and max EN score:");
                printf("%ld %d\n",stud[i],max[i]);
                break;
            case 2:
                printf("Max score of student'ID and max PH score:");
                printf("%ld %d\n",stud[i],max[i]);
                break;
        }
    }

}
void BJG(int score[][M],long mun[N],int n)
{
    int i,k,j;
    for(i=0;i<n;i++)
    {
        for (j=0;j<M;j++)
        {
            if(score[i][j]<60)
            {
                printf("不及格学生的学号和MT EN PH成绩:%ld",mun[i]);
                for (k=0;k<M;k++)
                {
                    printf(" %d",score[i][k]);
                }
                printf("\n");
            }
            break;
        }
    }
}
int main()
{
    int score[N][M],sum[N],n,max[M];
    float aver[N];
    long mun[N],stud[N];
    do{
        printf("Input the total number of the students(n<=40):");
        scanf("%d",&n);
    }while((n<0)||(n>40));
    Readscore(score,mun,n);
    AverforStud(score,sum,aver,n);
    MAX (score,n,max,stud,mun);
    BJG(score,mun,n);
}

