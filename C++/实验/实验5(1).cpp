//attribute 属性
#include<iostream>
using namespace std;
class TRANSPORT
{
private:
    int weight,year,month,day;
public:
    void cinn()
    {
        cout<<"输入该交通工具的质量 生产日期 ";cin>>weight>>year>>month>>day;
    }
    void coutt()
    {
        cout<<"该交通工具的质量为:"<<weight<<"吨"<<endl;
        cout<<"生产日期为:"<<year<<"年"<<month<<"月"<<day<<"日"<<endl;
    }
};
class CAR:public TRANSPORT
{

};
main()
{
    CAR a;
    a.cinn();
    a.coutt();
}
