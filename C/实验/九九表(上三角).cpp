#include<stdio.h>
main()
{
    int a,b,c;
    char ch='-',space=' ';
    for(a=1;a<=9;a++)
    {
        printf("%-4d",a);
    }
    printf("\n");
    for(a=1;a<=9;a++)
    {
        printf("%-4c",ch);
    }
    printf("\n");
    for(a=1;a<=9;a++)
    {
        for(b=1;b<a;b++)
        {
            printf("%-4c",space);
        }
        for(c=a*a;c<=9*a;c+=a)
        {
            printf("%-4d",c);
        }
        printf("\n");
    }
}
