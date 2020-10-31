#include<stdio.h>
#define N 10
void PaiXu(int a[],int n)
{
    int i,j,k,t;
    for(i=0;i<n-1;i++)
    {
        k=i;
        for(j=i+1;j<n;j++)
        {
            if(a[j]>a[k])
            {
                k=j;
            }
        }
        if(k != i)
        {
            t=a[k];
            a[k]=a[i];
            a[i]=t;
        }
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
    printf("请输入10个整数:");
    Input(a,N);
    PaiXu (a,N);
    Output(a,N);
}
