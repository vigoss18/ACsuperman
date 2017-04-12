#include "Socket.h"
#include "htmlManage.h"

char host[256];
char path[256];
string codeHtml;
SOCKET sock;
#define sp system("pause")

void baidu(string titleId, vector<string> &baiduUrl)
{
	strcpy(host, "cn.bing.com");
	strcpy(path, "/search?q=");
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
	baiduUrl.erase(unique(baiduUrl.begin(), baiduUrl.end()), baiduUrl.end());
	cout << baiduUrl.size() << endl;
	for (int i = 0; i < baiduUrl.size(); i++)
	{
		cout << baiduUrl[i] << endl;
	}
}

void search(vector<string> &baiduUrl)
{
	for (int i = 0; i < min(baiduUrl.size(),3); i++)
	{
		strcpy(path, baiduUrl[i].substr(13, baiduUrl[i].size() - 13).c_str());
		printf("%s\n", path);
		sendGet(host, path);
		char bufRecv[2333] = { 0 };
		string allHtml = "";
		int n = recv(sock, bufRecv, sizeof(bufRecv)-1, 0);
		while (n > 0)
		{
			bufRecv[n] = '\0';
			allHtml += bufRecv;
			n = recv(sock, bufRecv, sizeof(bufRecv)-1, 0);
		}
		cout << allHtml << endl;
		closesocket(sock);
		if (getCode(allHtml))
		{
			checkCode();
		}
		cout << codeHtml << endl;
	}
}

int main()
{
	vector<string>baiduUrl;
	for (int i = 1000; i < 1001; i++)
	{
		string titleId = "hdu+" + to_string(i) + "+csdn";
		baiduUrl.clear();
		//cout << titleId << endl;
		baidu(titleId,baiduUrl);
		search(baiduUrl);
	}
	
	system("pause");
	return 0;
}