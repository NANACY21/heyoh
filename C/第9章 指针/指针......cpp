#include<stdio.h>
void Exchange(int a,int b)
{
    int t;
    t=a;
    a=b;
    b=t;
}
main()
{
    int i,a[8]={1,2,3,4,5,6,7,8};
    for(i=0;i<8;i++)
    {
        Exchange(a[i],a[i+1]);
    }
    for(i=0;i<8;i++)
    {
        printf("%d ",a[i]);
    }
}
