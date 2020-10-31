#include<stdio.h>
#define N 10
int Length(char *a)
{
    int i,n=0;
    for(i=0;*(a+i)!='\0';i++)
    {
        n++;
    }
    return n;
}
main()
{
    char a[N];
    int b;
    printf("请输入一个字符串(不得超过9个字母):\n");
    scanf("%s",a);
    b=Length(a);
    printf("该字符串长度为%d",b);
}
