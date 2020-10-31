#include<stdio.h>
#define N 3
void Input(int a[][N],int m,int n)
{
    int i,j;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
}
void Max(int a[][N],int m,int n)
{
    int i,j,k=0,b,c,max=a[0][0];
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            if(a[i][j]>max)
            {
                max=a[i][j];
                b=i+1;
                c=j+1;
                k++;
            }
        }
    }
    if(k!=0)
    {
        printf("最大值:%d (位置:第%d行第%d列)",max,b,c);
    }
    else
    {
        printf("最大值:%d (位置:第1行第1列)",a[0][0]);
    }
}
main()
{
    int a[N][N];
    printf("请输入一个3*3矩阵:\n");
    Input(a,N,N);
    Max(a,N,N);
}
