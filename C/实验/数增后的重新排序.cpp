#include<stdio.h>
#define N 10
void Paixu(int a[],int n)
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
    int a[N];    //申请4*10个字节的连续的空间
    printf("请输入9个数:\n");    //提示
    Input(a,N-1);
    Paixu(a,N-1);
    Output(a,N-1);
    printf("\n再输入1个数:\n");    //提示
    scanf("%d",&a[N-1]);
    Paixu(a,N);
    Output(a,N);
}
