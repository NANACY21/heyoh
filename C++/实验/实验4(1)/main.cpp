#include <iostream>
#include"Client.h"
using namespace std;
main()
{
    Client a;
    char b[10];
    cout << "���ķ���������:" << endl;
    cin>>b;
    a.ChangeServerName(b);
    a.SHOWServerName();
    a.SHOWClientNum();
    Client a1;
    cout << "���ķ���������:" << endl;
    cin>>b;
    a1.ChangeServerName(b);
    a1.SHOWServerName();
    a1.SHOWClientNum();
}
