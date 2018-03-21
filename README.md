# Myntra_crawler

To run this code, you need to have the curl headers installed

#Install header files and library for cURL
sudo aptitude install libcurl4-openssl-dev

#Clone the repository
git clone https://github.com/ashishghadge/Myntra_crawler.git

#Complile it using using make command
make
make clean

#Run the code
Usage: <./Myntra> <URL>

e.g

./Myntra "https://www.myntra.com/"
or
./Myntra "https://www.myntra.com/men-clothing"
etc..

Output:
Output.csv file will be created with the information (Product Name, URL, Price)
