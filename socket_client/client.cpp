#include <Cstdio>
#include <Cstdlib>
#include <iostream>
#include <string>
#include <WinSock.h>


int main() 
{
	//��ʼ��DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//�����׽���
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//sockaddr
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);

	// ���������������
	int ret = connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	if (ret == SOCKET_ERROR)
	{
		std::cout << "���ӷ�����ʧ�ܣ�" << std::endl;
		return -1;
	}

	//���������������
	std::string str;
	char judge = 'y';
	while (1)
	{
		if (judge == 'y' || judge == 'Y')
		{
			std::cout << "�����뷢����Ϣ����\n";
			std::getline(std::cin, str);
			send(sock, str.c_str(), str.length(), NULL);

			// ����Ӧ��
			char szBuffer[MAXBYTE] = { 0 };
			int res = recv(sock, szBuffer, MAXBYTE, NULL);
			//������յ�������
			if (res > 0)
			{
				printf("%s \n", szBuffer);
			}
			else if (res == 0)
				break;
		}

		std::cout << "�Ƿ�������ͣ�\n y or n \n";
		std::cin >> judge;
		std::cin.ignore(1);

		if (judge == 'n' || judge == 'N')
		{
			break;
		}

	}

	//�ر��׽���
	closesocket(sock);
	//��ֹʹ�� DLL
	WSACleanup();
	return 0;
}