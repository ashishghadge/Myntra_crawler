#include <iostream>
#include <string>
#include <curl/curl.h>
#include  <stdio.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <regex>
#include <queue>
#include <unordered_set>
#include <fstream>
#include "Data.hpp"
#include "CurlObj.hpp"

using namespace std;

std::vector<std::string> getURLS(std::string hrefCheck, std::string buffer)
{
        size_t iterator = 0;
        size_t second_iterator = 0;

        bool is_flag = false;

        std::string returnString = "";
        std::vector<std::string> returnVector;

        for(iterator = 0;iterator < buffer.size();++iterator)
        {
            if(buffer[iterator] == '<')
            {
                is_flag = true;
                for(second_iterator = 0;second_iterator < hrefCheck.size();++second_iterator)
                {
                    if(buffer[iterator + second_iterator] == hrefCheck[second_iterator])
                    {
                        returnString = returnString + buffer[iterator + second_iterator];
                    }
                    else
                    {
                        is_flag = false;
                        returnString = "";
                        break;
                    }
                }

                if(is_flag == true)
                {
                    for(second_iterator = iterator + second_iterator;second_iterator < buffer.size();++second_iterator)
                    {
                        returnString = returnString +  buffer[second_iterator];

                        if(buffer[second_iterator - 2] == '/' && buffer[second_iterator - 1] == 'a')
                        {
                            returnVector.push_back(returnString);
                            break;
                        }
                    }
                }
            }
        }

    	return returnVector;
}

void retriveElementValue(const std::string & buffer, std::string &elementValue, 
				const std::string &startSearch, const std::string endSearch = ",")
{
	unsigned long pos = buffer.find(startSearch);
	unsigned long pos1 = buffer.find(endSearch,pos);
	if(startSearch.find("price") == std::string::npos)
		elementValue = buffer.substr(pos+startSearch.size()+1,pos1-pos-startSearch.size()-2);
	else
		elementValue = buffer.substr(pos+startSearch.size(),pos1-pos-startSearch.size());
}

int main( int argc, char** argv )
{
  	if(argc!=2)
	{
		std::cout << "Usage: <./Myntra> <URL>" << endl;
		return 0;
	}

  	std::string urlname = argv[1]; 
	char domainname[1024];
	//Retrieve domain name
	sscanf(urlname.c_str(), "https://%[^/]", domainname);
 
  	queue<std::string> urls;
  	urls.push(urlname);

	//Unsorted sets to make sure get the html data from all unique URLS
  	std::unordered_set<std::string> visited_urls;
  	std::unordered_set<std::string> not_visited_urls;
 
  	std::string readBuffer;

  	std::string hrefCheck = "<a href=\"";
  	std::vector<std::string> urlmap;

  	std::string url;
  	int counter = 0; 

        ofstream csvfile;
	csvfile.open ("output.csv");
	csvfile << "Product Name, URL, Price" << endl;

  	while(!urls.empty())
  	{
		readBuffer.clear();

 		url = urls.front();
     		urls.pop();

        	not_visited_urls.erase(url);
        	visited_urls.insert(url);

		try
		{
			//CurlObj is used to get the html from the given webpage	
			CurlObj temp(url);
        		readBuffer = temp.getData();
		}
		catch (const std::exception &ex)
                {
                       std::cerr << "Exception occured while curl initilization - " << ex.what() << endl;
                       continue;
                }

		unsigned long first = 0, end = 0, next = 0;  

		while(1)
		{
			try
			{
				if ((first = readBuffer.find("\"brands_filter_facet\":", next+1)) != std::string::npos) 
					next = first;
				else
					break;


				if ((end = readBuffer.find("\"discount_label\":", first+1)) != std::string::npos) 
					next = end;
				else
					break;

				Data data(readBuffer.substr(first,end-first),domainname);

				++counter;

				//Dump information into CSV file
				csvfile << "\"" << data.getProductName() << "\"," << data.geturl() << "," << data.getprice() << endl; 
			}
			catch (const std::exception &ex)
			{
				std::cerr << "Exception occured while fetching the information - " << ex.what() << endl;
				break;
			}

		}		

       		std::cout<< "Total ( " << counter << " ) records dumped into output.csv file" << endl;

    		urlmap = getURLS(hrefCheck, readBuffer );
    
	    	for(size_t iterator = 0;iterator < urlmap.size();++iterator)
    		{
			std::string url1;
			retriveElementValue(urlmap[iterator],url1,std::string("href="),std::string(" "));
			if(url1.find("https://") == std::string::npos && url1.find("www") == std::string::npos && url1.find("http://") == std::string::npos)
				url1 = std::string("https://") + domainname + url1;

			
	               	if (visited_urls.find(url1) == visited_urls.end() && not_visited_urls.find(url1) == not_visited_urls.end())
			{
				urls.push(url1);
	        		not_visited_urls.insert(url1);
			}
    		}
  	}
  	return 0;
}

