#include<stdio.h>
int square(int i)
{
    return i*i;
}
main()
{
    int i=0;
    i=square(i);
    for(i=0;i<3;i++)
    {
        static int i=1;//这叫初始化,有static则仅被初始化1次
        i=i+square(i);
        printf("%d ",i);
    }
    printf("%d",i);
}
