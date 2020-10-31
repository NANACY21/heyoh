#include<stdio.h>
#include<string.h>
#define M 5
#define N 10
void Paixu(char a[M][N],int n)
{
    int i,j;
    char t[N];
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(strcmp(a[j],a[i])<0)
            {
                strcpy(t,a[i]);
                strcpy(a[i],a[j]);
                strcpy(a[j],t);
            }
        }
    }
}
void Input(char a[][N])
{
    int i;
    for(i=0;i<M;i++)
    {
        printf("请输入第%d个字符串(不得超过9个字母):\n",i+1);
        gets(a[i]);
    }
}
void Output(char a[][N])
{
    int i;
    for(i=0;i<M;i++)
    {
        puts(a[i]);
    }
}
main()
{
    char a[M][N];
    Input(a);
    Paixu(a,M);
    Output(a);
}

