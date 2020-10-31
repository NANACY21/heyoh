#include<stdio.h>
main()
{
    int a=0,*b;
    b=&a;
    printf("%d %p %p %p %d",a,&a,b,&b,*b);
}
