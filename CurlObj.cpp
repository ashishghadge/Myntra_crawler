#include "CurlObj.hpp"

CurlObj::CurlObj(std::string url) 
{
	curl = curl_easy_init();
	if (!curl) 
		throw std::string ("Curl did not initialize.");

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CurlObj::WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	replaceString(curlBuffer, "\\u002F", "/");	
}

//This callback function will be called when receive the http response from the server.
size_t CurlObj::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

void CurlObj::replaceString(std::string& subject, const std::string& search,
					const std::string& replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos)
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}
