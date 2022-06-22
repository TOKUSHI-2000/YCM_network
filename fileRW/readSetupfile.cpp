#include "readSetupfile.hpp"

struct cfgDate
{
	string type;
	string data;
};



int stringToInt(std::string str)
{
	std::cout << "値:" << str << "\n";
	int tmpnNum = 0;

	try
	{
		tmpnNum = std::stoi(str);
		return tmpnNum;
	}
	catch(std::invalid_argument e)
	{
		ClearDrawScreen() ;
		DrawString( 0, 0, (TCHAR*)"errer:\tIpアドレスが数字として認識できません", GetColor( 255, 255, 255), true);
		ScreenFlip() ;
		WaitKey();
		
		
		exit(1);
	} catch (std::out_of_range e) {
    return tmpnNum;
    }
}

void readFile(IPDATA& ip, string& name, int& ModelId)
{
	ip.d1 = 1;
	ip.d2 = 1;
	ip.d3 = 1;
	ip.d4 = 1;

	name = "Nun";
	ModelId = 2;

	cfgDate cdata[10];
    string tmpStr[10];
    ifstream fp( "./settings.txt", std::ios::in);   

    if (!fp) {
        std::cout << "ファイルを開けませんでした。\n" << std::endl;
        return;
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
		if (!tmpStr[i].empty())
		{
			a = tmpStr[i].find("=");
			cdata[i].type = tmpStr[i].substr(0,a);
			cdata[i].data = tmpStr[i].substr( a, tmpStr->length());
		}

		
		
		
	}
	
	for (int i = 0; i < 10; i++)
		{
			std::cout << "OK";
			if (!tmpStr[i].empty())
			{
				if (cdata[i].type == "Ip")
				{
					string tmpCData;
					string tmpnum;
                    int point;

					tmpCData = cdata[i].type;
					point = tmpCData.find(".");
					tmpnum = tmpCData.substr( 0, point);
					tmpCData.erase(0,point+1);
					ip.d1 = stringToInt(tmpnum);
					
					tmpCData = cdata[i].type;
					point = tmpCData.find(".");
					tmpnum = tmpCData.substr( 0, point);
					tmpCData.erase(0,point+1);
					ip.d2 = stringToInt(tmpnum);

					tmpCData = cdata[i].type;
					point = tmpCData.find(".");
					tmpnum = tmpCData.substr( 0, point);
					tmpCData.erase(0,point+1);
					ip.d3 = stringToInt(tmpnum);

					tmpCData = cdata[i].type;
					point = tmpCData.find(".");
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
			
			std::cout << "\n";

		}
	
    

	std::cout << "name:" << name << "\tIP:" << ip.d1 << "." << ip.d2 << "." << ip.d3 << "." << ip.d4; 

}