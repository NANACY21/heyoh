#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
class Client
{
private:
    static char ServerName[10];    //�������������
    static int ClientNum;    //��¼����Ŀͻ�����
public:
    Client();
    static void ChangeServerName(char NewServerName[10]);
    void SHOWServerName();
    void SHOWClientNum();
};
#endif // CLIENT_H_INCLUDED

