#include<stdio.h>
main()
{
    int a[]={2,4,6,8,10},i;
    int *b;
    b=a;
    *(b+1)=20;
    for(i=0;i<5;i++)
    {
        printf("%d ",a[i]);
    }
}


