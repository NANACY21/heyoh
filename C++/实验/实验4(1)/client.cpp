#include"Client.h"
#include <iostream>
using namespace std;
int Client::ClientNum=0;
char Client::ServerName[10]="0";
Client::Client()
{
    ClientNum++;
}
void Client::ChangeServerName(char NewServerName[10])
{
    int i;
    for(i=0;i<10;i++)
    {
        ServerName[i]=NewServerName[i];
    }
}
void Client::SHOWServerName()
{
        cout<<ServerName<<endl;
}
void Client::SHOWClientNum()
{
    cout<<ClientNum<<endl;
}
