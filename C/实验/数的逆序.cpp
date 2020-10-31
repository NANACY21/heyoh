#include<stdio.h>
#define N 10
void Jiaohuan(int *x,int *y)
{
    int t;
    t=*x;
    *x=*y;
    *y=t;
}
void PaiXu(int a[],int n)
{
    int i;
    for(i=0;i<n/2;i++)
    {
        Jiaohuan(&a[i],&a[n-i-1]);
    }
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
    PaiXu(a,N);
    Output(a,N);
}
