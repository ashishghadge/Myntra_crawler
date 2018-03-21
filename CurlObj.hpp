#include <iostream>
#include <curl/curl.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

using namespace std;


//CurlObj is used to get the html from the given webpage
class CurlObj 
{
	public:
		CurlObj(std::string url);

		static void replaceString(std::string& subject, const std::string& search, const std::string& replace);

    		static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    		std::string getData() 
		{
        		return curlBuffer;
    		}

	private:
    		CURL * curl;
    		std::string curlBuffer;
};

