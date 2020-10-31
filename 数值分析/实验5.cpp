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
long double Gauss[4][5]={{10,-7,0,1,8},{-3,2.099999,6,2,5.900001},{5,-1,5,-1,5},{2,1,0,2,1}};
int n=4;//矩阵阶数(增广矩阵行数)
void zhihuan(int i1,int i2);//单纯换行
void zhihuan(int i1,int i2)//单纯换行
{
	long double temp;
	for(int i=0;i<=n;i++)
	{
		temp=Gauss[i1][i];
		Gauss[i1][i]=Gauss[i2][i];
		Gauss[i2][i]=temp;
	}
}
main()
{
	long double result[4],xshls=1;
	int max,i,j,k;
	for(i=0;i<n;i++)
	{
		max=i;//最大的数的下标
		for(j=i;j<n;j++)
		{
			if(fabs(Gauss[j][i])>fabs(Gauss[max][i]))
			{
				max=j;
			}
		}
		if(max!=i)
		{
			zhihuan(i,max);
			xshls=0-xshls;
		}
		for(j=i+1;j<n;j++)
		{
			Gauss[j][i]=Gauss[j][i]/Gauss[i][i];
			for(k=i+1;k<=n;k++)
			{
				Gauss[j][k]=Gauss[j][k]-Gauss[j][i]*Gauss[i][k];
			}
		}
		xshls=xshls*Gauss[i][i];
	}
	long double sum=0;
	for(i=n-1;i>=0;i--)
	{
		sum=0;
		for(j=i+1;j<n;j++)
		{
			sum+=Gauss[i][j]*result[j];
		}
		result[i]=(Gauss[i][n]-sum)/Gauss[i][i];
	}
	for(i=0;i<n;i++)
	{
		cout<<"x"<<i+1<<"="<<result[i]<<endl;
	}
	cout<<"系数行列式的值:"<<xshls<<endl;
}
