#include <winsock2.h>
#pragma   comment(lib,"wsock32")

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
main()
{
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
      printf("WSAStartup failed with error \n");
      exit(0);
	}
	SOCKET sock;
	if((sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		printf("network client socket failure \n");
		perror("network client");

	}
	u_short port;
	char buf[256], buffer1[256];

	printf("please enter the server ip:");
	gets(buf);
	
	printf("please enter the service port:");
	scanf("%hd", &port);
	getchar();
	struct sockaddr_in m_addr;
	m_addr.sin_port = htons(port);
	m_addr.sin_family=AF_INET;
	m_addr.sin_addr.S_un.S_addr = inet_addr(buf);
	/*连接*/
	if((connect(sock, (struct sockaddr *)&m_addr, sizeof(m_addr))) == SOCKET_ERROR) 
	{
		printf("network client connect failure \n");
		exit(0);
	}
	printf("connect success!!\n");
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	
	while(1) 
	{
		char recvbuf[256];
	    char sendbuf[256];
		int bytes;
		printf("\nsend to server:");
		gets(sendbuf);
		if(send(sock, sendbuf, strlen(buf)+1, 0)<0)
		{
			printf("send error\n");
			exit(0);
		}
		if(recv(sock,recvbuf,sizeof(recvbuf),0)<0)
		{
			printf("recv error\n");
			exit(0);
		}
		printf("come from server: %s",recvbuf);
	}
	closesocket(sock);
	if(WSACleanup() == SOCKET_ERROR) {
		printf("WSACleanup failed with error %d\n", WSAGetLastError());
	}
	exit(0);
}