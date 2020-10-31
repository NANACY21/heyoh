//类型兼容规则也称赋值兼容规则,公有继承情况下,基类兼容派生类
//静态联编
#include<iostream>
using namespace std;
class A
{
public:
    void Show()const
    {
        cout<<"A::Show()"<<endl;
    }
};
class B:public A
{
public:
    void Show()const
    {
        cout<<"B::Show()"<<endl;
    }
};
class C:public B
{
public:
    void Show()const
    {
        cout<<"C::Show()"<<endl;
    }
};
void fun(A *a)
{
    a->Show();
}
main()
{
    A b;
    B c;
    C d;
    fun(&b);
    fun(&c);
    fun(&d);
    //c.Show(); //就近原则
}
