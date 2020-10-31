#include<stdio.h>
#define N 100
void Match(char *a,char *b)
{
    for(;*a!='\0';a++);
    {
        for(;*b!='\0';a++,b++)
        {
            *a=*b;
        }
    }
    *a='\0';
}
main()
{
    char a[N]={0},b[N]={0};
    printf("请输入2个字符串:\n");
    scanf("%s%s",a,b);
    Match(a,b);
    printf("%s",a);
}
