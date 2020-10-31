#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<math.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
#include<stack>//栈
#include<queue>//队列
#include<algorithm>//堆(优先队列)
#include<vector>//向量
#define MaxInt 9999//极大值
#define MVNum 100//最大顶点数
#define bag 40//书包的容量(最大能承受bag斤的重量,无需考虑体积问题)
using namespace std;
//int a[6],sizeof(a)/sizeof(a[0])等于6
//向量与堆的用法
int main()
{
    vector <int>a;
    int i,n,b;
    cout<<"你想输入多少数?";
    cin>>n;
    cout<<"请输入(按空格键以分隔每一个数,输入完请按回车键)"<<endl;
    /*49 38 65 97 76 13 27 49*/
    for(i=0;i<n;i++)
    {
        cin>>b;
        a.push_back(b);//在向量最后添加数据
    }
    /*make_heap功能:把一个数组弄成一个堆,默认大根堆*/
    make_heap(a.begin(),a.end());
    //make_heap(a.begin(),a.end(),greater<int>());//小根堆
    /*push_heap功能:新增1个元素在末尾,之后才可调用push_heap,把一个数组弄成一个堆,默认大根堆,必须已有make_heap()语句*/
    a.push_back(100);
    push_heap(a.begin(),a.end());
    /*pop_heap功能:删除堆顶元素,再把剩余元素弄成一个堆,默认大根堆,必须已有make_heap()语句*/
    pop_heap(a.begin(),a.end());//把堆顶元素与数组末尾元素调换位置
    a.pop_back();//删除向量末尾元素
    /*sort_heap功能:堆排序,默认从小到大,堆排序之后不再是合法堆,必须已有make_heap()语句*/
    sort_heap(a.begin(),a.end());
    while(!a.empty())
    {
        cout<<a.front()<<" ";
        a.erase(a.begin());
    }
    return 0;
}
