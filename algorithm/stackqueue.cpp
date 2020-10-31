/*有些知识文章解释不如代码直观*/
#include<iostream>//c++的输入输出
#include<stack>//栈
#include<queue>//队列
using namespace std;
int main()
{
    stack<int> s;
    queue<int> q;
    if(s.empty())
    {
        cout<<"栈s当前为空"<<endl;
    }
    if(q.empty())
    {
        cout<<"队列q当前为空"<<endl;
    }
    s.push(1);//入栈
    s.push(2);
    s.push(3);
    s.push(4);
    q.push(1);//入队
    q.push(2);
    q.push(3);
    q.push(4);
    s.pop();//出栈，无返回值
    q.pop();//出队，无返回值
    cout<<"栈顶元素为(不删除该元素)："<<s.top()<<endl;
    cout<<"队首元素为(不删除该元素)："<<q.front()<<endl;
    cout<<"队尾元素为(不删除该元素)："<<q.back()<<endl;
    cout<<"栈s中元素个数："<<s.size()<<endl;
    cout<<"队列q中元素个数："<<q.size()<<endl;
    return 0;
}
