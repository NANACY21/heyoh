#include <winsock2.h>
#pragma   comment(lib,"wsock32")

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
main()
{ 
    WSADATA wsa;
    if(WSAStartup(MAKEWORD(2,2),&wsa)!=0)
   {
     printf("套接字库初始化失败");
     exit(0);
   }
   /*建立服务器套接字*/
   SOCKET serversock;
   if((serversock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))==INVALID_SOCKET)
   {
     printf("创建套接字失败");
     exit(0);
   }
   struct sockaddr_in serverAddress;
   memset(&serverAddress,0,sizeof(serverAddress));
   serverAddress.sin_family=AF_INET;
   serverAddress.sin_port=htons(6000);
   serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
   if(bind(serversock,(struct sockaddr *)&serverAddress,sizeof(serverAddress))==SOCKET_ERROR)
  {
     printf("套接字绑定端口失败！\n");
     exit(0);
  }
  if(listen(serversock,5)!=0)
  {
    printf("监听失败！\n");
    exit(0);
  }
  //获取本主机名，通过主机名获取本主机IP地址
  /*char name[256],str[32],**pptr; 
  struct in_addr in;
  struct hostent *phost;  
  struct sockaddr addr;  
  struct sockaddr_in  *sptr;  /*指向包含本主机信息的结构的指针
  sptr=(struct sockaddr_in *)&addr;
  gethostname(name,256);						       
  phost=gethostbyname(name);
  pptr=phost->h_addr_list;
  memcpy(&in.S_un.S_addr, *pptr, sizeof(in.S_un.S_addr));
  printf("network serverIP:%s\n",inet_ntoa(in));
  printf("network server:server has port number:%d\n",ntohs(sptr->sin_port));*/
  //接受连接

  SOCKET clientsocket;
  struct sockaddr_in clientaddress;
   memset(&clientaddress,0,sizeof(clientaddress));
   int addrlen=sizeof(clientaddress);
  if((clientsocket=accept(serversock,(struct sockaddr *)&clientaddress,&addrlen))<0)
  {
      printf("accept error\n");
     exit(0);
  }
  printf("接受来自%s的连接\n",inet_ntoa(clientaddress.sin_addr));
  
  int bytes;
  while(1)
  {
	  char buf[256];
      if(recv(clientsocket,buf,sizeof(buf),0)<0)
	  {
         printf("recv error\n");
         exit(0);
	  }
     // buf[bytes]='\0';
      printf("消息来自%s:%s\n",inet_ntoa(clientaddress.sin_addr),buf);

      printf("send to client >");
      gets(buf);
      if(send(clientsocket,buf,strlen(buf)+1,0)<0)
	  {
         printf("send error\n");
         exit(0);
	  }
  }
     closesocket(clientsocket);                            /*关闭套接字*/
	 if(WSACleanup() == SOCKET_ERROR) 
	 {
		printf("WSACleanup failed with error %d\n", WSAGetLastError());
		exit(0);
	}
	
  
}