#include<stdio.h>
#define N 100
void Copy(char *a,char *b)
{
    do
    {
        *a=*b;
        a++;
        b++;
    }while(*a!='\0'||*b!='\0');
}
main()
{
    char a[N],b[N];
    printf("请输入2个字符串:\n");
    scanf("%s%s",a,b);
    Copy(a,b);
    printf("%s %s",a,b);
}
