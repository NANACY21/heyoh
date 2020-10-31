#include<stdio.h>
#define N 100
void Match(char a[],char b[])
{
    int i,k;
    for(i=0;a[i]!='\0';i++);
    {
        k=i;
    }
    for(;b[i-k]!='\0';i++)
    {
        a[i]=b[i-k];
    }
    a[i]!='\0';
}
main()
{
    char a[N]={0},b[N]={0};
    printf("请输入2个字符串:\n");
    scanf("%s%s",a,b);
    Match(a,b);
    puts(a);
}
