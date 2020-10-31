#include<stdio.h>
main()
{
    int a,b;
    for(a=1;a<=9;a++)
    {
        for(b=1;b<=9;b++)
        {
            printf("%d*%d=%-2d  ",a,b,a*b);
        }
    printf("\n");
    }
}

