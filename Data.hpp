#include <iostream>
#include <curl/curl.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

class Data {
	private:
    		std::string HTMLContent;
    		std::string product;
		std::string price;
    		std::string url;
    		std::string domainname;

	public:
    		Data(std::string HTMLContent, std::string domainname);

    		void fillData();
    		void printData();
		void retriveElementValue(const std::string & buffer, std::string &elementValue,const std::string &startSearch);

		std::string getProductName()
		{
			return product;
		}

		std::string geturl()
		{	
			return url;
		}
		
		std::string getprice()
		{
			return price;
		}
};

