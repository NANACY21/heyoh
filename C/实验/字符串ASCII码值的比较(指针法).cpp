//A的ASCII码值比a的ASCII码值小32
#include<stdio.h>
#define N 10
int MyStrcmp(char *a,char *b)
{
    int i,c;
    for(i=0;*(b+i)!='\0'||*(a+i)!='\0';i++)
    {
        if(*(a+i)!=*(b+i))
        {
            c=*(a+i)-*(b+i);
            return c;
        }
        else
            continue;
    }
    return 0;
}
main()
{
    char a[N],b[N];
    int c;
    printf("请输入2个字符串(不得超过9个字母):\n");
    scanf("%s%s",a,b);
    c=MyStrcmp(a,b);
    printf("%d",c);
}






