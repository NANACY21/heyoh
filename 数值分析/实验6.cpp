#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
#include<math.h>
#include<queue>//队列,优先队列
#include<vector>//向量
using namespace std;
long double a[4][5]={{-4,1,1,1},{1,-4,1,1},{1,1,-4,1},{1,1,1,-4}};
long double b[4]={1,1,1,1};
long double x[4];
long double y;
int n=4;
main()
{
    long double eps=0.00000001;
    cout<<"高斯-赛德尔迭代法"<<endl;
    int i,j;
    for(i=0;i<n;i++)
    {
        x[i]=0;
    }
    long double e=0;
    for(i=0;i<n;i++)
    {
        y=b[i];
        for(j=0;j<n;j++)
        {
            if(j!=i)
            {
                y = y - a[i][j]*x[j];
            }
        }
        y=y/a[i][i];
        if( fabs(x[i]-y) > e )
        {
            e=fabs(x[i]-y);
        }
        x[i]=y;
    }
    while(e >= eps)
    {
        e=0;
        for(i=0;i<n;i++)
        {
            y=b[i];
            for(j=0;j<n;j++)
            {
                if(j!=i)
                {
                    y = y - a[i][j]*x[j];
                }
            }
            y=y/a[i][i];
            if( fabs(x[i]-y) > e )
            {
                e=fabs(x[i]-y);
            }
            x[i]=y;
        }
    }
    for(i=0;i<n;i++)
    {
        cout<<"x"<<i+1<<"="<<x[i]<<endl;
    }
}
