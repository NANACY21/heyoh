#include<stdio.h>
main()
{
    int a,b;
    char ch='-';
    for(a=1;a<=9;a++)
    {
        printf("%4d",a);
    }
    printf("\n");
    for(a=1;a<=9;a++)
    {
        printf("%4c",ch);
    }
    printf("\n");
    for(a=1;a<=9;a++)
    {
        for(b=1*a;b<=9*a;b+=a)
        {
            printf("%4d",b);
        }
        printf("\n");
    }
}
