#include<stdio.h>
int Galaxy(int a[],int n)
{
    int i,sum=0;
    for(i=0;i<n+2;i++)
    {
        sum=sum+a[i];
    }
    return sum;
}
main()
{
    int a,b[]={9,8,7,6,5,4,3,2,1};
    a=Galaxy(b,3);
    printf("%d",a);
}
