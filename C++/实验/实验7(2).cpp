//动态联编
#include<iostream>
using namespace std;
class Vehicle
{
public:
    virtual void run()
    {
        cout<<"Vehicle::run!"<<endl;
    }
    virtual void stop()
    {
        cout<<"Vehicle::stop!"<<endl;
    }
};
class bicycle:public Vehicle
{
public:
    void run()
    {
        cout<<"bicycle::run!"<<endl;
    }
    void stop()
    {
        cout<<"bicycle::stop!"<<endl;
    }
};
class car:public Vehicle
{
    void run()
    {
        cout<<"car::run!"<<endl;
    }
    void stop()
    {
        cout<<"car::stop!"<<endl;
    }
};
class motocar:public bicycle
{
    void run()
    {
        cout<<"motocar::run!"<<endl;
    }
    void stop()
    {
        cout<<"motocar::stop!"<<endl;
    }
};
void func(Vehicle *a)
{
    a->run();
    a->stop();
}
main()
{
    Vehicle a;
    bicycle b;
    car c;
    motocar d;
    func(&a);
    func(&b);
    func(&c);
    func(&d);
}
