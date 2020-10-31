#include <iostream>
using namespace std;
#include<queue>//队列
int main()
{
    char target[9];//被遮挡的车牌
    int n;//牌照数量
    int i=0,j=0;//下标
    for(i=0;i<9;i++)
    {
        cin>>target[i];
    }
    cin>>n;
    char all_target[n][9];//所有车牌号
    for(i=0;i<n;i++)
    {
        for(j=0;j<9;j++)
        {
            cin>>all_target[i][j];
        }
    }
    queue<int> q;//存储i可能的值
    int flag=0;
    for(i=0;i<n;i++)//开始从数据库中查找车牌号，
    {
        flag=0;
        for(j=0;j<9;j++)
        {
            if(all_target[i][j]==target[j])
            {
                flag=1;
                continue;
            }
            else
            {
                if(target[j]=='*')
                {
                    continue;
                }
                else
                {
                    flag=0;
                    break;
                }
            }
        }
        if(flag==1)
        {
            q.push(i);
        }
    }

    cout<<q.size()<<endl;
    int x=0;
    while(!q.empty())
    {
        x=q.front();
        for(j=0;j<9;j++)
        {
            cout<<all_target[x][j];
        }
        cout<<endl;
        q.pop();
    }
    return 0;
}
