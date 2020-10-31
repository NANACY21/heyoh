#include<stdio.h>
void Output(int *b)
{
    printf("%d ",*b);
    *b=20;
}
main()
{
    int a=10;
    printf("%d ",a);
    Output(&a);
    printf("%d ",a);
}
