#include<stdio.h>
#define N 3
void Input(int juzhen[N][N])
{
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            scanf("%d",&juzhen[i][j]);
        }
    }
}
void Output(int juzhen[N][N])
{
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            printf("%d ",juzhen[i][j]);
        }
        printf("\n");
    }
}
void ZHZH(int (*a)[N])
{
    int i,j,t;
    for(i=0;i<N;i++)
    {
        for(j=i+1;j<N;j++)
        {
            t=*(*(a+i)+j);
            *(*(a+i)+j)=*(*(a+j)+i);
            *(*(a+j)+i)=t;
        }
    }
}
main()
{
    int juzhen[N][N];
    printf("输入一个3*3矩阵:\n");
    Input(juzhen);
    printf("转置:\n");
    ZHZH(juzhen);
    Output(juzhen);
}
