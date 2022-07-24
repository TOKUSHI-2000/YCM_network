#include <stdio.h>
#include <string>
#include <unordered_map>
#include <DxLib.h>

#include <iostream>

constexpr int strNum = 10;
constexpr int strLenght = 32;

constexpr char U81BITE = ~(1<7);
constexpr char U82BITE = (1<<7) | ~(1<<6);
constexpr char U83BITE = (1<<7) | (1<<6) | ~(1<<5);
constexpr char U84BITE = (1<<7) | (1<<6) | (1<<5) | ~(1<<4);
constexpr char U85BITE = (1<<7) | (1<<6) | (1<<5) | (1<<4) | ~(1<<3);
constexpr char U86BITE = (1<<7) | (1<<6) | (1<<5) | (1<<4) | (1<<3) | ~(1<<2);

unsigned char stringToChar(std::string str)
{
    int i = 0;
    try
    {
        i = std::stoi(str);
    }
    catch(const std::invalid_argument& e)
    {
        return 1;
    }

    if (i > 127)return 1;

    return i;
}

bool stringToBool(std::string str, bool Default = true)
{
    if (!(str.find("true") == std::string::npos))
    {
        return true;
    }
    else if (!(str.find("false") == std::string::npos))
    {
        return false;   
    }
    else
    {
        return Default;
    }
    
    
}

class DATAMAP
{
private:
    std::string &name;
    IPDATA &ip;
    int &serverBits;
    std::unordered_map<std::string,std::string> data =
    {
        {u8"Host",u8"true"},
        {u8"Server",u8"true"},
        {u8"ip1",u8"1"},
        {u8"ip2",u8"1"},
        {u8"ip3",u8"1"},
        {u8"ip4",u8"1"},
        {u8"Name",u8"NoName"},
    };

    std::string str[strNum];
public:
    DATAMAP(std::string &name_, IPDATA &ip_,int &serverBits_);
    ~DATAMAP();
    void dataChange(char *str_);

    
    
};

DATAMAP::DATAMAP(std::string &name_, IPDATA &ip_,int &serverBits_) :name(name_), ip(ip_), serverBits(serverBits_)
{
}


DATAMAP::~DATAMAP()
{
    int tmp;
    name = data[u8"Name"];
    ip.d1 = stringToChar(data[u8"ip1"]);

    ip.d2 = stringToChar(data[u8"ip2"]);

    ip.d3 = stringToChar(data[u8"ip3"]);

    ip.d4 = stringToChar(data[u8"ip4"]);

    serverBits = 0;
    if (stringToBool(data["Host"]));
    {
        serverBits |= (1<<1);
    }

    if (stringToBool(data["Server"]))
    {
        serverBits |= (1<<0);
    }
    
    return;
}


void DATAMAP::dataChange(char *str_)
{
    std::string str = str_;
    std::string key;
    std::string body;

    if(str.empty())return;

    int start;
    int finish;

    start = 0;
    finish = str.find_first_of("=");

    key = str.substr(0,finish);

    start = finish + 1;
    if (str.find_first_of(";") ==std::string::npos)
    {
        finish = str.length()-start;
    }
    else
    {
        finish = str.find(";")-start;
    }

    body = str.substr( start, finish);

    std::cout <<key << ":" << body << "\n";

    if (data.find(key) != data.end())
    {
        data.erase(key);
    }
    data.insert({key, body});
    std::cout << data[key] << "\n";
   return; 

}



void readIniFile(std::string &name_, IPDATA &ip_,int &serverBits_)
{
    FILE *fp;
    DATAMAP datamap( name_,ip_, serverBits_);
    

    fp = fopen(u8"./settings.txt","r");
    if (fp == NULL)
    {
        return;
    }
    
    for (int i = 0; i < 10; i++)
    {
        char cstr[strLenght];

        fgets( cstr, strLenght, fp);
        
        datamap.dataChange(cstr);
        
        if (cstr == NULL || feof(fp))
        {
            break;
        }
    }
    
    fclose(fp);
    
    
    

    return;
}
