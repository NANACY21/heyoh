#include<stdio.h>
main()
{
    int a[5]={1,2,3,4,5};
    int *p;
    p=a;    //给定义的指针初始化(整型数组首地址值)
    printf("%d ",*p);
    printf("%d ",*(++p));
    printf("%d ",(*p)++);
    printf("%d ",*p);
    printf("%d ",*(p--));
    printf("%d ",--(*p));
    printf("%d ",*p);
}
