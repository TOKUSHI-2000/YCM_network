#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#include <DxLib.h>

using std::string;
using std::ifstream;

struct cfgDate
{
	string type;
	string data;
};

IPDATA ip;

int stringToInt(std::string str)
{
	std::cout << str << "\t";
	int a = 0;
	try
	{
		a = std::stoi(str);
		return a;
	}
	catch(std::invalid_argument e)
	{
		ClearDrawScreen() ;
		DrawString( 0, 0, (TCHAR*)"あああああああああエラー\n\tIpアドレスが数字として認識できません", GetColor( 255, 255, 255), true);
		ScreenFlip() ;
		WaitKey();
		
		
		exit(1);
	} catch (std::out_of_range e) {
    return a;
    }
}

int readFile(IPDATA& ip, string& name, int& ModelId)
{
	cfgDate cdata[10];
    string tmpStr[10];
    ifstream fp( "./settings.txt", std::ios::in);   

    if (!fp) {
        std::cout << "ファイルを開けませんでした。\n" << std::endl;
        return 1;
    }


    for (int i = 0; i <10; i++)
    {
		if (!fp.eof())
		{
			break;
		}
		
        std::getline(fp, tmpStr[0]);
    }



	for (int i = 0; i < 10; i++)
	{
		int a;
		if (!tmpStr[0].empty())
		{
			a = tmpStr[i].find("=");
			cdata[i].type = tmpStr[i].substr(0,a);
			cdata[i].data = tmpStr[i].substr( a, tmpStr->length());
		}

		for (int i = 0; i < 10; i++)
		{
			if (!tmpStr[0].empty())
			{

				if (cdata[i].type == "Ip")
				{
					string tmpCData;
					string tmpnum;

					tmpCData = cdata[i].type;
					int point = tmpCData.find(".");
					tmpnum = tmpCData.substr( 0, point);
					tmpCData.erase(0,point+1);
					ip.d1 = stringToInt(tmpnum);
					
					tmpCData = cdata[i].type;
					int point = tmpCData.find(".");
					tmpnum = tmpCData.substr( 0, point);
					tmpCData.erase(0,point+1);
					ip.d2 = stringToInt(tmpnum);

					tmpCData = cdata[i].type;
					int point = tmpCData.find(".");
					tmpnum = tmpCData.substr( 0, point);
					tmpCData.erase(0,point+1);
					ip.d3 = stringToInt(tmpnum);

					tmpCData = cdata[i].type;
					int point = tmpCData.find(".");
					tmpnum = tmpCData.substr( 0, point);
					tmpCData.erase(0,point+1);
					ip.d4 = stringToInt(tmpnum);


					
				}
				else if (cdata[i].type == "Name")
				{
					name = cdata[i].data;
				}
				else if (cdata[i].type == "Model")
				{
					try
					{
					ModelId = stoi(cdata[i].data);	
					}
					catch(std::invalid_argument e)
					{
						ModelId = 2;
					}
				}
				
				


			}
			
		}
		
		
	}
	

	
    



}



