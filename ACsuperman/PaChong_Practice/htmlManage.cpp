#include "htmlManage.h"

vector<string> urlSelect(string &allhtml)
{
	vector<string> ret;
	string patten = "www.baidu.com/link\\?url=[^\"]";
	regex link_regex(patten);
	for (sregex_iterator it(allhtml.begin(), allhtml.end(), link_regex), end; it != end; it++)
	{
		ret .push_back(it->str());
	}
	return ret;
}