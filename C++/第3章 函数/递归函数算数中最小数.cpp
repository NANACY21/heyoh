#include<stdio.h>
#define N 10
int MIN(int n,int a[],int Min)
{
    if(n==0)
    {
        return Min<a[n]?Min:a[n];
    }
    else
    {
        return Min<a[n]?MIN(n-1,a,Min):MIN(n-1,a,a[n]);
    }
}
main()
{
    int a[N],i,Min;
    printf("请输入10个整数:\n");
    for(i=0;i<N;i++)
    {
        scanf("%d",&a[i]);
    }
    Min=MIN(N-1,a,a[N-1]);
    printf("这10个整数中最小的数是%d\n",Min);
}

