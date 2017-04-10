#include "htmlManage.h"

extern SOCKET sock;
extern char host[256];
extern char path[256];

void sendGet(char *host, char *path)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "½¨Á¢socketÊ§°Ü.\n";
		return;
	}
	sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrc;
	HOSTENT *pHost = gethostbyname(host);
	if (pHost == NULL)
	{
		cout << "Ö÷»ú½âÎö´íÎó.\n";
		return;
	}
	memcpy(&addrc.sin_addr.s_addr, pHost->h_addr, 4);
	addrc.sin_port = htons(80);
	addrc.sin_family = AF_INET;
	bind(sock, (SOCKADDR*)&addrc, sizeof(addrc));
	int n = connect(sock, (SOCKADDR*)&addrc, sizeof(addrc));
	if (n == SOCKET_ERROR)
	{
		cout << "connect´íÎó.\n";
		return;
	}
	string reqInfo = "GET " + (string)path + " HTTP/1.1\r\nHost: " + (string)host + "\r\nConnection:Close\r\n\r\n";
	cout << reqInfo << endl;
	if (send(sock, reqInfo.c_str(), reqInfo.size(), 0) == SOCKET_ERROR)
	{
		cout << "send´íÎó.\n";
		closesocket(sock);
	}
}