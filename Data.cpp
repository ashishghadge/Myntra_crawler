#include <iostream>
#include <curl/curl.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include "Data.hpp"
using namespace std;

Data::Data(std::string HTMLContent, std::string domainname)
{
	this->HTMLContent = HTMLContent;
	this->domainname = domainname;
	fillData();
}

void Data::retriveElementValue(const std::string & buffer, std::string &elementValue, 
			const std::string &startSearch)
{
	std::string endSearch = ",";
        unsigned long pos = buffer.find(startSearch);
        unsigned long pos1 = buffer.find(endSearch,pos);
        if(startSearch.find("price") == std::string::npos)
                elementValue = buffer.substr(pos+startSearch.size()+1,pos1-pos-startSearch.size()-2);
        else
                elementValue = buffer.substr(pos+startSearch.size(),pos1-pos-startSearch.size());
}

void Data::fillData() 
{
       	this->retriveElementValue(HTMLContent,product,std::string("\"product\":"));
       	this->retriveElementValue(HTMLContent,price,std::string("\"discounted_price\":"));
       	this->retriveElementValue(HTMLContent,url,std::string("\"dre_landing_page_url\":"));
       	url = std::string("https://") + domainname + "/" + url;

        //printData();
}

void Data::printData() {

       	cout << "Product => " << product << endl;
       	cout << "URL     => " << url << endl;
       	cout << "Price   => " << price << endl;
}
