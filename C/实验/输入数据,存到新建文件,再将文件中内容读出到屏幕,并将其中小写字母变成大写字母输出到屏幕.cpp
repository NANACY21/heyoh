//函数fopen()用来打开文件,返回值是一个地址
//函数fclose()用来关闭文件,文件关闭成功返回0值,否则返回非0值
//函数fgetc()用于从一个以只读或读写方式打开的文件上读字符
//函数fputc()用于将一个字符写到一个文件上
//同时打开的文件数目是有限制的
#include<stdio.h>
#include<stdlib.h>
main()
{
    FILE *a;    //fp=文件的地址值
    char b;
    if((a=fopen("D:\\新建文件.txt","w"))==NULL)    //判断文件是否成功打开(文件名：新建文件)
    {
        printf("打开.txt格式的演示失败!\n");
        exit(0);
    }
    printf("请随意输入一些字符:\n");
    b=getchar();
    while(b!='\n')    //while(b!='$')：若键入'$'则结束键盘输入和文件写入
    {
        fputc(b,a);
        b=getchar();
    }
    fclose(a);    //关闭由函数fopen()打开的fp指向的文件
    printf("(已将输入的这些字符存入新建文件)\n");
    if((a=fopen("D:\\新建文件.txt","r"))==NULL)
    {
        printf("打开.txt格式的演示失败!\n");
        exit(0);
    }
    while((b=fgetc(a))!=EOF)    //从文件中读取字符直到文件末尾
    {
        putchar(b);
    }
    fclose(a);
    printf("\n(读出新建文件中的内容)\n");
    if((a=fopen("D:\\新建文件.txt","r"))==NULL)    //判断文件是否成功打开
    {
        printf("打开.txt格式的演示失败!\n");
        exit(0);
    }
    while((b=fgetc(a))!=EOF)    //从文件中读取字符直到文件末尾
    {
        if(b>=97)
        {
            b=b-32;
        }
        putchar(b);
    }
    fclose(a);
    printf("\n(将新建文件中的内容中的小写字母都转换成大写字母)\n");
}
