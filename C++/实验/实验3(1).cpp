#include <iostream>
using namespace std;
class DOG
{
public:
    DOG(int AGE,int HEIGHT,int WEIGHT)
    {
        age=AGE;
        height=HEIGHT;
        weight=WEIGHT;
    }
    DOG(DOG &d)
    {
        age=d.age;
        height=d.height;
        weight=d.weight;
    }
    void cinn()
    {
        cout<<"输入狗的年龄、身高、体重 ";
        cin>>age>>height>>weight;
    }
    void coutt()
    {
        cout<<"狗的年龄是"<<age<<"岁,"<<"身高是"<<height<<"厘米,"<<"体重是"<<weight<<"斤."<<endl;
    }
private:
    int age,height,weight;
};
main()
{
    DOG a(2,40,30),b(a);
    a.cinn();
    a.coutt();
    b.coutt();
}
