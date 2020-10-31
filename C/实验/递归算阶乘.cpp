#include<stdio.h>
long Fact(int n)
{
    int i;
    long result=1;
    for(i=2;i<=n;i++)
    {
        result=result*i;
    }
    if(n<0)
    {
        return -1;
    }
    else if(n==0||n==1)
    {
        return 1;
    }
    else
    {
        return n*Fact(n-1);
    }
}
main()
{
    int n;
    long result;
    printf("输入1个大于零的整数:\n");
    scanf("%d",&n);
    result=Fact(n);
    if(result==-1)
    {
        printf("输入1个大于零的整数!\n");
    }
    else
    {
        printf("%d!=%ld",n,result);
    }
}

