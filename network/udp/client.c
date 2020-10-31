

#include <winsock2.h>
#pragma   comment(lib,"wsock32")

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


void main()
{
	WSADATA wsaData;
	unsigned short port;
	int namelen;
	char ip_address[100];
	SOCKET client_socket;//服务器方用于通信的socket
	SOCKADDR_IN server_addr;
    printf("我是客户端，我要与服务器进行通信。\n");
	printf("请输入服务器端的IP地址:");
	scanf("%s",&ip_address);
    printf("请输入服务器端的端口号:");
	scanf("%u",&port);
	char recv_buf[100];
	char snd_buf[100];
	int Ret = WSAStartup(MAKEWORD(1,1),&wsaData);//windows socket API版本号选为1.1
    if (Ret != 0)
   {
      printf("ERROR: WSAStartup failed with error %d\n", Ret);
      return;
   }
	//建立套接字，指定地址族AF_INET，套接字类型SOCK_DGRAM和使用的协议类型IPPROTO_UDP
	client_socket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.S_un.S_addr =inet_addr(ip_address);
    /*printf("注意:网络编程中,要将主机字节序转成网络字节序。\n");
    printf("我们输入的IP地址是:%s,必须使用inet_addr函数转成网络字节序\n",ip_address);
	printf("因为点分十进制只是为了方便我们记忆。\n转成网络字节序后,\
%s在计算机里存储形式为:%u\n",ip_address,server_addr.sin_addr.S_un.S_addr);


	printf("我们输入的端口号是:%u,必须使用htons函数转成网络字节序",port);   */ 
	server_addr.sin_port=htons(port);
	
//	printf("将%u端口转成网络字节序后变成了%u。\n大家看差别多大。\n",port,htons(port));
	
    namelen = sizeof(server_addr);
    
	printf("现在我们与服务器进行3次通信\n");
	for(int i=0;i<=2;i++)
	{
		printf("请输入要发给服务器的数据:");
	    scanf("%s",&snd_buf);
        //把数据发给服务器端
	    sendto(client_socket,snd_buf,strlen(snd_buf)+1,0,(sockaddr*)&server_addr,sizeof(SOCKADDR));
        //从服务器端收服务器发来的数据
        recvfrom(client_socket,recv_buf,100,0,(SOCKADDR*)&server_addr,&namelen);	
        printf("收到服务器发来的数据:%s\n",recv_buf);	

	}
      closesocket(client_socket);
	  WSACleanup();
}