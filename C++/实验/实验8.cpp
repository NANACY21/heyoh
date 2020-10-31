//ofstream是文件输出流类,用于把内容写进文件
//ofstream类的成员函数有:open函数、close函数、put函数(用于把一个字符写入文件)、write函数(用于把内容写进文件)、seekp函数、tellp函数、错误处理函数
//cout是ofstream类对象
//ifstream是文件输入流类,用于把文件内容读出
//ifstream类的成员函数有:open函数、close函数、get函数、getline函数、read函数(用于把文件内容读出)、seekg函数、tellg函数
//cin是ifstream类对象
//ios::out覆盖写
//ios::app追加写
//ios::in
//cin.get()是保留回车在输入流队列中的.而cin是丢弃回车的
#include<iostream>
#include<fstream>
#define N 20
using namespace std;
int t;
main()
{
    char a[N];char b;
    cout<<"输入文件名 ";cin>>a;
    ofstream file(a,ios::out);
    cout<<"输入一些数据,存到文件 "<<a<<" 中";
    cin>>b;
	while(b!='#')
	{
		file.put(b);
		cin.get(b);
	}
	file.close();
    char cunbtzm[N],temp[N];
	int cunpinlv[N]={0},j=0;
	int have=0,t1=1;
	int flag,flag1=0;
	ifstream file1(a,ios::in);
	while(file1.good())
	{
		file1.get(b);
		if(b!='\n'&&b!=' ')
		{
			if(t==0)
			{
				cunbtzm[t]=b;
				cunpinlv[t]=1;
				t++;
			}
			else
			{
				if(t==1&&flag1==0)
				{
					if(cunbtzm[t-1]==b)
					{
						cunpinlv[t-1]++;
						flag1=1;
						goto E;
					}
					else
					{
						have=1;
					}
				}
				flag=1;
				for(int i=0;i<t;i++)
				{
					if(cunbtzm[i]==b)
					{
						cunpinlv[i]++;
						flag=0;
						break;
					}
				}
				if(flag==1)
				{
					have=1;
				}
			}
			E:if(have)
			{
				cunbtzm[t]=b;
				cunpinlv[t]=1;
				t++;
				have=0;
			}
		}
		temp[j]=b;
		j++;
	}
	cunbtzm[t]='\0';
	temp[j-1]='\0';
	file1.close();
	int i,k;
	for(int k=0;cunbtzm[k]!='\0';k++)
	{
		if(temp[j-2]==cunbtzm[k])
		{
			cunpinlv[k]--;
			break;
		}
	}
	for(i=0;cunbtzm[i]!='\0';i++)
	{
		cout<<"这些数据中字母"<<cunbtzm[i]<<"的个数:"<<cunpinlv[i]<<endl;
	}
	ofstream file3("实验8(副本).txt",ios::out);
	file3<<t1;
	t1++;
	for(i=0;i<j;i++)
	{
		file3.put(temp[i]);
		if(temp[i]=='\n')
		{
			file3<<t1++;
		}
	}
}
