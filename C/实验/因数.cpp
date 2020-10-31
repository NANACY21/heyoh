#include<stdio.h>
void Yinshu(long n)
{
    int i,a,j;
    for(i=2;i<=n;i++)
    {
        a=n%i;
        if(a==0)
        {
            j=n/i;
            if(j==1)
            {
                printf("%d",i);
            }
            else
            {
                printf("%d*",i);
                return Yinshu(j);
            }
        }
        else
        {
            continue;
        }
    }
}
main()
{
    long n;
    printf("请输入1个数:\n");
    scanf("%d",&n);
    Yinshu(n);
}
