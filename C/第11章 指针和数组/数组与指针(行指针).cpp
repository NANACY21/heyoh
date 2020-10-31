#include<stdio.h>
#define M 3
#define N 4
void Input(int a[M][N])
{
    int i,j;
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
}
void Output(int a[M][N])
{
    int i,j;
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            printf("%d  ",a[i][j]);
        }
        printf("\n");
    }
}
main()
{
    int a[M][N];
    int (*b)[N];
    b=a;
    printf("请输入1个3*4矩阵:\n");
    Input(a);
    *(b[1]+1)=10;
    *(*(b+1)+1)=100;
    Output(a);
}
