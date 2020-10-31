#include<iostream>
#include<string.h>
using namespace std;
main()
{
    int *a,*b,i,j,m,n;
    cout<<"输入第一个矩阵的行数和列数:"<<endl;
    cin>>m>>n;
    a=new int[m*n];
    cout<<"输入第一个矩阵:"<<endl;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            cin>>*(a+i*n+j);
        }
    }
    cout<<"输入第二个矩阵的行数和列数:"<<endl;
    cin>>m>>n;
    b=new int[m*n];
    cout<<"输入第二个矩阵:"<<endl;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            cin>>*(b+i*n+j);
        }
    }
    cout<<"将这两个矩阵相加:"<<endl<<"结果:"<<endl;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            cout<<(*(a+i*n+j))+(*(b+i*n+j))<<"  ";
        }
        cout<<endl;
    }
    delete []a;
    delete []b;
}
