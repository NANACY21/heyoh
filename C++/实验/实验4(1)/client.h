#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
class Client
{
private:
    static char ServerName[10];    //保存服务器名称
    static int ClientNum;    //记录定义的客户数量
public:
    Client();
    static void ChangeServerName(char NewServerName[10]);
    void SHOWServerName();
    void SHOWClientNum();
};
#endif // CLIENT_H_INCLUDED

