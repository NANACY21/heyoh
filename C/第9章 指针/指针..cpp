#include<stdio.h>
#define N 12
main()
{
    char name[N];
    char *a;
    a=name;
    printf("enter your name:\n");
    gets(a);
    puts(a);
}
