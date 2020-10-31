/*
++a a先+1，再运用a
a++ a先运用，再+1
*/
#include<stdio.h>
main()
{
    int a=10,b[8],i=0,j;
    do
    {b[i]=a%2;
       i++;
       a=a/2;
    }while(a>=1);
    for(j=i-1;j>=0;j--)
    {
        printf("%d ",b[j]);
    }
}

