#include "Socket.h"
#include "htmlManage.h"

char host[256];
char path[256];
SOCKET sock;
#define sp system("pause")

void baidu(string titleId, vector<string> &baiduUrl)
{
	strcpy(host, "www.baidu.com");
	strcpy(path, "/s?wd=");
	strcat(path, titleId.c_str());

	sendGet(host, path);
	
	char bufRecv[2333] = { 0 };
	string allHtml = "";
	int n = recv(sock, bufRecv, sizeof(bufRecv) - 1, 0);
	while (n > 0)
	{
		bufRecv[n] = '\0';
		allHtml += bufRecv;
		n = recv(sock, bufRecv, sizeof(bufRecv) - 1, 0);
	}
	closesocket(sock);
	baiduUrl = urlSelect(allHtml);
	for (int i = 0; i < baiduUrl.size(); i++)
	{
		cout << baiduUrl[i] << endl;
	}
}

int main()
{
	vector<string>baiduUrl;
	for (int i = 1000; i < 1001; i++)
	{
		string titleId = "hdu" + to_string(i);
		baiduUrl.clear();
		//cout << titleId << endl;
		baidu(titleId,baiduUrl);
	}
	
	system("pause");
	return 0;
}