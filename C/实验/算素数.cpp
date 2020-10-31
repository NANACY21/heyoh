#include<stdio.h>
main()
{
    int i,n,t=0;
    printf("1-100之间的素数(质数):\n");
    for(i=1;i<=100;i++)
    {
        for(n=2;n<=i;n++)
        {
            if(i%n==0)
            break;
        }
        if(n==i)
        {
            printf("%d  ",i);
            t++;
        }
        if(t==5)
        {
            t=0;
            printf("\n");
        }
    }
}

