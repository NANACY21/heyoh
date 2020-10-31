#include <winsock2.h>
#pragma   comment(lib,"wsock32")

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void main()
{
	WSADATA wsaData;


	SOCKET server_socket;//服务器方用于通信的socket
	SOCKADDR_IN server_addr;
	SOCKADDR_IN client_addr;
	char recv_buf[100];//用于接收客服端发过来的数据
	char snd_buf[100];//用于向客户端发送数据
	int len;
    char hostname[100];
	
	int Ret = WSAStartup(MAKEWORD(1,1),&wsaData);//windows socket API版本号选为1.1
    if (Ret != 0)
   {
      printf("ERROR: WSAStartup failed with error %d\n", Ret);
      return;
   }

	//建立套接字，指定地址族AF_INET，套接字类型SOCK_DGRAM和使用的协议类型IPPROTO_UDP
	server_socket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(520);//指定通信端口为520
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //本机任意IP地址

	gethostname(hostname,100);
    printf("我是服务器,我的通信端口为:%u\n",ntohs(server_addr.sin_port));
    bind(server_socket,(SOCKADDR*)&server_addr,sizeof(SOCKADDR));//绑定
	
	len = sizeof(SOCKADDR);
	while(1)
	{
	printf("等待接收客户端发送的数据... ...\n");	
	recvfrom(server_socket,recv_buf,100,0,(SOCKADDR*)&client_addr,&len);	
    printf("收到:%s\n",recv_buf);
    printf("给客户端回送数据:");
	scanf("%s",&snd_buf);
	sendto(server_socket,snd_buf,strlen(snd_buf)+1,0,(sockaddr*)&client_addr,sizeof(SOCKADDR));
	}
	closesocket(server_socket);
    WSACleanup();
   
	

}