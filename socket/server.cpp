#include <iostream>
#include <string>
#include <WinSock.h>


int main(int argc, char ** argv)
{
	//初始化 DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	//创建套接字
	SOCKET serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 绑定套接字
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;  //使用IPv4地址
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
	sockAddr.sin_port = htons(1234);  //端口
	//将套接字和IP、端口绑定
	bind(serversock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//进入监听状态
	listen(serversock, 20);
	//接收客户端请求
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(serversock, (SOCKADDR*)&clntAddr, &nSize);
	//等待客户端数据
	std::string str = "已收到\n";
	while(1)
	{
		char szBuffer[MAXBYTE] = { 0 };
		int res = recv(clntSock, szBuffer, MAXBYTE, NULL);
		//输出接收到的数据
		if (res > 0)
		{
			printf("你有新的消息， 请注意查收 %s \n", szBuffer);
			send(clntSock, str.c_str(), str.length(), NULL);
		}
		else if (res == 0)
		{
			printf("客户端已断开\n");
			break;
		}
	}

	//关闭套接字
	closesocket(clntSock);
	closesocket(serversock);
	//终止 DLL 的使用
	WSACleanup();
	return 0;

}