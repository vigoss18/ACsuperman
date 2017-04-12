#include "htmlManage.h"

extern string codeHtml;

vector<string> urlSelect(string &allhtml)
{
	vector<string> ret;
	string patten = "http://blog.csdn.net[^\\\"]+";
	regex link_regex(patten);
	for (sregex_iterator it(allhtml.begin(), allhtml.end(), link_regex), end; it != end; it++)
	{
		ret .push_back(it->str());
	}
	return ret;
}

bool getCode(string &allHtml)
{
	string patten1 = "class=\"cpp\"";;
	string patten2 = "#include";
	int pos = allHtml.find(patten1);
	if (pos != -1)
	{
		int pos1 = allHtml.find(patten2,pos);
		if (pos1 != -1)
		{
			int pos2 = allHtml.find("</pre>", pos1);
			int pos3 = allHtml.find("</textarea>", pos1);
			if (pos2 > 0 || pos3 > 0)
			{
				if (pos2 > 0 && pos3 > 0)
				{
					if (pos2 < pos3)
					{
						codeHtml = allHtml.substr(pos1 + 1, pos2 - pos1);
					}
					else
					{
						codeHtml = allHtml.substr(pos1 + 1, pos3 - pos1);
					}
				}
				else if (pos2 > 0)
				{
					codeHtml = allHtml.substr(pos1 + 1, pos2 - pos1);
				}
				else if (pos3 > 0)
				{
					codeHtml = allHtml.substr(pos1 + 1, pos3 - pos1);
				}
				return true;
			}	
		}
	}
	return false;
}

void checkCode()
{
	int pos = codeHtml.find("&lt;");
	while (pos > 0)
	{
		codeHtml = codeHtml.replace(pos, 4, "<");
		pos = codeHtml.find("&lt;");
	}
	pos = codeHtml.find("&gt;");
	while (pos > 0)
	{
		codeHtml = codeHtml.replace(pos, 4, ">");
		pos = codeHtml.find("&gt;");
	}
	pos = codeHtml.find("/n");
	while (pos > 0)
	{
		codeHtml = codeHtml.replace(pos, 2, "\\n");
		pos = codeHtml.find("/n");
	}
	pos = codeHtml.find("&amp;");
	while (pos > 0)
	{
		codeHtml = codeHtml.replace(pos, 5, "&");
		pos = codeHtml.find("&amp;");
	}
	pos = codeHtml.find("&quot");
	while (pos > 0)
	{
		codeHtml = codeHtml.replace(pos, 5, "\"");
		pos = codeHtml.find("&quot");
	}
	pos = codeHtml.find("&nbsp");
	while (pos > 0)
	{
		codeHtml = codeHtml.replace(pos, 5, " ");
		pos = codeHtml.find("&nbsp");
	}
	pos = codeHtml.find("&#43;");
	while (pos > 0)
	{
		codeHtml = codeHtml.replace(pos, 5, "+");
		pos = codeHtml.find("&#43;");
	}
	pos = codeHtml.find("&#39;");
	while (pos > 0)
	{
		codeHtml = codeHtml.replace(pos, 5, "\'");
		pos = codeHtml.find("&#39;");
	}
}