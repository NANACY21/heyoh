#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
#include<stack>
#include<queue>
#define MAXLEN 100//串最大长度
using namespace std;
typedef struct//串定长顺序存储结构
{
    char a[MAXLEN+1];//存储串的一维数组
    int length;//串当前长度
}String;
void BDS_create(String &BDS);
void BDS_display(String &BDS);
int ysfyxjbj(char *a);
void zhuanhuan(String &BDS);//中缀->后缀//涉及文件操作
void zzBDSjisuan(String &BDS);//2(*)7#是错误的中缀表达式格式
void hzBDSjisuan(String &BDS);//涉及文件操作
void HZBDSjisuan(String &BDS);
void menu1();
void menu2(String &BDS);
void menu3(String &BDS);
void BDS_create(String &BDS)
{
    char b='N';
    int i=0;
    BDS.length=0;
    cout<<"输入表达式:";
    while(b!='#')
    {
        cin>>b;
        BDS.a[i]=b;
        i++;
        BDS.length++;
    }
}
void BDS_display(String &BDS)
{
    if(BDS.length==0)
    {
         cout<<"无表达式"<<endl;
    }
    else
    {
        int i=0;
        while(BDS.a[i]!='#')
        {
            cout<<BDS.a[i];
            i++;
        }
    }
    cout<<endl;
}
int ysfyxjbj(char *a)
{
    int b;
    switch(*a)
    {
        case '*':b=2;break;
        case '/':b=2;break;
        case '+':b=1;break;
        case '-':b=1;break;
        case '(':b=0;break;
        case ')':b=0;break;
    }
    return b;
}
void zhuanhuan(String &BDS)//中缀->后缀//涉及文件操作
{
    stack <char>linshi1;//运算符栈
    queue <char>linshi2;//用于存转换后的后缀表达式
    queue <char>linshi3;
    stack <int>linshi4;
    FILE *fp=NULL;//fp=文件的地址值
    int b,c,d;char e,f;
    if(BDS.length==0)//若没有表达式
    {
        cout<<"请先输入1个中缀表达式"<<endl;
    }
    else
    {
        for(int i=0;i<BDS.length-1;i++)//从头->尾扫描中缀表达式
        {
            if(BDS.a[i]==32)
            {

            }
            if(BDS.a[i]<=57&&BDS.a[i]>=48)//如果是操作数
            {
                linshi2.push(BDS.a[i]);
            }
            else
            {
                if(linshi1.empty())
                {
                    linshi1.push(BDS.a[i]);
                }
                else
                {
                    if(BDS.a[i]=='(')
                    {
                        linshi1.push(BDS.a[i]);
                    }
                    else if(BDS.a[i]==')')
                    {
                        B:e=linshi1.top();
                        linshi1.pop();
                        if(e=='(')
                        {

                        }
                        else
                        {
                            linshi2.push(e);
                            goto B;
                        }
                    }
                    else
                    {
                        A:e=linshi1.top();
                        linshi1.pop();
                        b=ysfyxjbj(&e);
                        c=ysfyxjbj(&BDS.a[i]);
                        if(c>b)
                        {
                            linshi1.push(e);
                            linshi1.push(BDS.a[i]);
                        }
                        else
                        {
                            linshi2.push(e);
                            if(!linshi1.empty())
                            {
                                goto A;
                            }
                            linshi1.push(BDS.a[i]);
                        }
                    }
                }
            }
        }
        while(!linshi1.empty())
        {
            e=linshi1.top();
            linshi1.pop();
            linshi2.push(e);
        }
        if((fp=fopen("D:\\后缀表达式.txt","w"))==NULL)//判断文件是否成功打开(文件名:后缀表达式)
        {
            cout<<"没有文件"<<endl;
            exit(0);
            //cout<<"打开.txt格式的演示失败!"<<endl
        }//--------------------------------------------------
        while(!linshi2.empty())
        {
            cout<<linshi2.front();
            fputc(linshi2.front(),fp);
            linshi3.push(linshi2.front());
            linshi2.pop();
        }
        fclose(fp);//关闭由函数fopen()打开的fp指向的文件
        cout<<endl<<"已将生成的后缀表达式存入文件"<<endl;
        cout<<"求该后缀表达式值?(y or n)";
        do
        {
            cin>>f;
            if(f!='y'&&f!='n')
            {
                cout<<"(输入有误)(y or n)";
                e='y';
                getchar();
            }
            else
            {
                e=0;
            }
        }while(e=='y');
        switch(f)
        {
            case 'y':
                while(!linshi3.empty())
                {
                    if(linshi3.front()<=57&&linshi3.front()>=48)
                    {
                        b=linshi3.front()-48;
                        linshi4.push(b);
                        linshi3.pop();
                    }
                    else
                    {
                        b=linshi4.top();
                        linshi4.pop();
                        c=linshi4.top();
                        linshi4.pop();
                        if(linshi3.front()=='-')
                        {
                            d=c-b;
                        }
                        else if(linshi3.front()=='+')
                        {
                            d=c+b;
                        }
                        else if(linshi3.front()=='*')
                        {
                            d=c*b;
                        }
                        else
                        {
                            d=c/b;
                        }
                        linshi4.push(d);
                        linshi3.pop();
                    }
                }
                d=linshi4.top();
                linshi4.pop();
                cout<<d<<endl;
                break;
            case 'n':
                menu3(BDS);
                break;
        }
    }
}
void zzBDSjisuan(String &BDS)//2(*)7#是错误的中缀表达式输入
{
    stack <int>linshi1;//操作数栈
    stack <char>linshi2;//运算符栈
    int b,c,d;char e;
    if(BDS.length==0)
    {
        cout<<"请先输入1个中缀表达式"<<endl;
    }
    else
    {
        for(int i=0;i<BDS.length-1;i++)//从头到尾扫描中缀表达式
        {
            if(BDS.a[i]==32)
            {

            }
            if(BDS.a[i]<=57&&BDS.a[i]>=48)//如果是操作数
            {
                b=BDS.a[i]-48;
                linshi1.push(b);
            }
            else
            {
                if(linshi2.empty())
                {
                    linshi2.push(BDS.a[i]);
                }
                else
                {
                    if(BDS.a[i]=='(')
                    {
                        linshi2.push(BDS.a[i]);
                    }
                    else if(BDS.a[i]==')')
                    {
                        B:e=linshi2.top();
                        linshi2.pop();
                        if(e=='(')
                        {

                        }
                        else
                        {
                            b=linshi1.top();
                            linshi1.pop();
                            c=linshi1.top();
                            linshi1.pop();
                            if(e=='-')
                            {
                                d=c-b;
                            }
                            else if(e=='+')
                            {
                                d=c+b;
                            }
                            else if(e=='*')
                            {
                                d=c*b;
                            }
                            else
                            {
                                d=c/b;
                            }
                            linshi1.push(d);
                            goto B;
                        }
                    }
                    else
                    {
                        A:e=linshi2.top();
                        linshi2.pop();
                        b=ysfyxjbj(&e);
                        c=ysfyxjbj(&BDS.a[i]);
                        if(c>b)
                        {
                            linshi2.push(e);
                            linshi2.push(BDS.a[i]);
                        }
                        else
                        {
                            b=linshi1.top();
                            linshi1.pop();
                            c=linshi1.top();
                            linshi1.pop();
                            if(e=='-')
                            {
                                d=c-b;
                            }
                            else if(e=='+')
                            {
                                d=c+b;
                            }
                            else if(e=='*')
                            {
                                d=c*b;
                            }
                            else
                            {
                                d=c/b;
                            }
                            linshi1.push(d);
                            if(!linshi2.empty())
                            {
                                goto A;
                            }
                            linshi2.push(BDS.a[i]);
                        }
                    }
                }
            }
        }
        while(!linshi2.empty())
        {
            e=linshi2.top();
            linshi2.pop();
            b=linshi1.top();
            linshi1.pop();
            c=linshi1.top();
            linshi1.pop();
            if(e=='-')
            {
                d=c-b;
            }
            else if(e=='+')
            {
                d=c+b;
            }
            else if(e=='*')
            {
                d=c*b;
            }
            else
            {
                d=c/b;
            }
            linshi1.push(d);
        }
        d=linshi1.top();
        linshi1.pop();
        cout<<d<<endl;
    }
}
void hzBDSjisuan(String &BDS)
{
    stack <int>linshi;//操作数栈
    int b,c,d;
    if(BDS.length==0)
    {
        cout<<"请先输入1个后缀表达式"<<endl;
    }
    else
    {
        for(int i=0;i<BDS.length-1;i++)//从头到尾扫描后缀表达式
        {
            if(BDS.a[i]==32)
            {

            }
            if(BDS.a[i]<=57&&BDS.a[i]>=48)
            {
                b=BDS.a[i]-48;
                linshi.push(b);
            }
            else
            {
                b=linshi.top();
                linshi.pop();
                c=linshi.top();
                linshi.pop();
                if(BDS.a[i]=='-')
                {
                    d=c-b;
                }
                else if(BDS.a[i]=='+')
                {
                    d=c+b;
                }
                else if(BDS.a[i]=='*')
                {
                    d=c*b;
                }
                else
                {
                    d=c/b;
                }
                linshi.push(d);
            }
        }
        d=linshi.top();
        linshi.pop();
        cout<<d<<endl;
        cout<<endl;
    }
}
void HZBDSjisuan(String &BDS)
{
    int a,b,c,i=0,j=0;
    char d,e;
    stack <int>linshi;//操作数栈
    char linshi1[MAXLEN];//将文件中数据提取至临时数组
    FILE *fp=NULL;
    cout<<"选取文件中的后缀表达式?(y or n)";
    do
    {
        cin>>e;
        if(e!='y'&&e!='n')
        {
            cout<<"(输入有误)(y or n)";
            d='y';
            getchar();
        }
        else
        {
            d=0;
        }
    }while(d=='y');
    switch(e)
    {
        case 'y':
            fp=fopen("D:\\后缀表达式.txt","r");
            if(fp==NULL)    //判断文件是否成功打开(文件名:后缀表达式)
            {
                cout<<"没有文件"<<endl;
                //cout<<"打开.txt格式的演示失败!"<<endl;
                //exit(0);
            }
            else
            {
                while(fscanf(fp,"%c",&linshi1[i])!=EOF)
                {
                    i++;
                }
                fclose(fp);
                for(j=0;j<i;j++)//从头到尾扫描后缀表达式
                {
                    if(linshi1[j]==32)
                    {

                    }
                    if(linshi1[j]<=57&&linshi1[j]>=48)
                    {
                        a=linshi1[j]-48;
                        linshi.push(a);
                    }
                    else
                    {
                        a=linshi.top();
                        linshi.pop();
                        b=linshi.top();
                        linshi.pop();
                        if(linshi1[j]=='-')
                        {
                            c=b-a;
                        }
                        else if(linshi1[j]=='+')
                        {
                            c=b+a;
                        }
                        else if(linshi1[j]=='*')
                        {
                            c=b*a;
                        }
                        else
                        {
                            c=b/a;
                        }
                        linshi.push(c);
                    }
                }
                c=linshi.top();
                linshi.pop();
                cout<<c<<endl;
            }
            break;
        case 'n':
            BDS_create(BDS);
            hzBDSjisuan(BDS);
            break;
    }
}
void menu1()
{
    cout<<"|-----------------------------------------|"<<endl;
    cout<<"|               表达式求值                |"<<endl;
    cout<<"|-----------------------------------------|"<<endl;
    cout<<"|        (1)中缀表达式->后缀表达式        |"<<endl;
    cout<<"|-----------------------------------------|"<<endl;
    cout<<"|        (2)中缀表达式计算                |"<<endl;
    cout<<"|-----------------------------------------|"<<endl;
    cout<<"|        (3)后缀表达式计算                |"<<endl;
    cout<<"|-----------------------------------------|"<<endl;
    cout<<"|        (4)退出                          |"<<endl;
    cout<<"|-----------------------------------------|"<<endl;
}
void menu2(String &BDS)
{
    int a,b;
    do{
        cin>>a;
        if(a<1||a>4)
        {
            cout<<"(输入有误)(1-4)";
            b=1;
            getchar();
        }
        else
        {
            b=0;
        }
    }while(b==1);
    switch(a)
    {
        case 1:
            BDS_create(BDS);
            zhuanhuan(BDS);
            break;
        case 2:
            BDS_create(BDS);
            zzBDSjisuan(BDS);
            break;
        case 3:
            HZBDSjisuan(BDS);
            break;
        case 4:
            exit(0);
    }
    menu3(BDS);
}
void menu3(String &BDS)
{
    char a,b;
    cout<<"继续?(y or n)";
    do
    {
        cin>>b;
        if(b!='y'&&b!='n')
        {
            cout<<"(输入有误)(y or n)";
            a='y';
            getchar();
        }
        else
        {
            a=0;
        }
    }while(a=='y');
    switch(b)
    {
        case 'y':
            menu2(BDS);
            break;
        case 'n':
            exit(0);
    }
}
main()
{
    String BDS;
    menu1();
    menu2(BDS);
}
