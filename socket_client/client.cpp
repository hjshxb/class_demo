#include <Cstdio>
#include <Cstdlib>
#include <iostream>
#include <string>
#include <WinSock.h>


int main() 
{
	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//创建套接字
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//sockaddr
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);

	// 与服务器进行连接
	int ret = connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	if (ret == SOCKET_ERROR)
	{
		std::cout << "连接服务器失败！" << std::endl;
		return -1;
	}

	//向服务器发送数据
	std::string str;
	char judge = 'y';
	while (1)
	{
		if (judge == 'y' || judge == 'Y')
		{
			std::cout << "请输入发送消息！！\n";
			std::getline(std::cin, str);
			send(sock, str.c_str(), str.length(), NULL);

			// 接收应答
			char szBuffer[MAXBYTE] = { 0 };
			int res = recv(sock, szBuffer, MAXBYTE, NULL);
			//输出接收到的数据
			if (res > 0)
			{
				printf("%s \n", szBuffer);
			}
			else if (res == 0)
				break;
		}

		std::cout << "是否继续发送！\n y or n \n";
		std::cin >> judge;
		std::cin.ignore(1);

		if (judge == 'n' || judge == 'N')
		{
			break;
		}

	}

	//关闭套接字
	closesocket(sock);
	//终止使用 DLL
	WSACleanup();
	return 0;
}