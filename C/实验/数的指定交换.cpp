#include<stdio.h>
#define N 10
void JiaoHuan(int *x,int *y)
{
    int t;
    t=*x;
    *x=*y;
    *y=t;
}
void MinJiaoHuan(int a[],int n)
{
    int i,k,min=a[0];
    for(i=0;i<n;i++)
    {
        if(a[i]<min)
        {
           min=a[i];
           k=i;
        }
    }
    JiaoHuan(&a[k],&a[0]);
}
void MaxJiaoHuan(int a[],int n)
{
    int i,k,max=a[0];
    for(i=0;i<n;i++)
    {
        if(a[i]>max)
        {
           max=a[i];
           k=i;
        }
    }
    JiaoHuan(&a[k],&a[n-1]);
}
void Input(int a[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
}
void Output(int a[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
}
main()
{
    int a[N];
    printf("请输入10个数:\n");
    Input(a,N);
    MinJiaoHuan(a,N);
    MaxJiaoHuan(a,N);
    Output(a,N);
}
