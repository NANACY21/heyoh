#include<stdio.h>
#define N 20
main()
{
    /*char a[N];
    printf("输入你的名字:\n");
    scanf("%s",a);
    printf("%s ",a);
    scanf("%s",a);
    printf("%s ",a);*/
    char a,b,c,d;
    scanf("%c%c",&a,&b);
    c=getchar();//getchar()读回车
    d=getchar();
    printf("%c%c%c%c\n",a,b,c,d);
    //输入:12回车34回车
    //a:1 b:2 c:3 d:没有       34回车都让c读了
}
