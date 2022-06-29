#include "readSetupfile.hpp"

struct cfgDate
{
	string type;
	string data;
};



int stringToInt(std::string str)
{
	//std::cout << "\t値:" << str << "\n";
	int tmpnNum = 0;

	try
	{
		tmpnNum = std::stoi(str);
		return tmpnNum;
	}
	catch(std::invalid_argument e)
	{
		//ClearDrawScreen() ;
		std::cout <<"errer:\tIpアドレスが数字として認識できません\n";
		//ScreenFlip() ;
		//WaitKey();
		
		
		exit(1);
	} catch (std::out_of_range e) {
    return tmpnNum;
    }
    return tmpnNum;
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
	std::cout << "ファイルの読み込みに成功しました" << "\n";

    for (int i = 0; i <10; i++)
    {
		if (fp.eof())
		{
			std::cout << "ファイルの読み込み終" << i <<"\n";
			break;
		}
		
        std::getline(fp, tmpStr[i]);
    }


	for (int i = 0; i < 10; i++)
	{
		int a;
		if (!tmpStr[i].empty())
		{
			a = tmpStr[i].find(":");
			if (a == std::string::npos)
			{
				continue;
			}
			
			cdata[i].type = tmpStr[i].substr(0,a);
			cdata[i].data = tmpStr[i].substr( a);
		}

		
		
		
	}
	
	std::cout << "データの分割完了\n";

	for (int i = 0; i < 10; i++)
		{
			std::cout << "読み込みデータ:\n";
			if (!tmpStr[i].empty())
			{
				std::cout << "\tデータあり\n";
				if (cdata[i].type == "Ip")
				{
					string tmpCData;
					string tmpnum;
                    int point;

					tmpCData = cdata[i].data;

					for (int i = 0; i < tmpCData.length(); i++)
					{
						try
						{
							std::stoi(tmpCData.substr(0,1));
						}
						catch(std::invalid_argument e)
						{
							tmpCData.erase(0,1);
							continue;
						}
						catch (std::out_of_range e)
						{
							break;
    					}
						break;
					}


					point = tmpCData.find(".");
					tmpnum = tmpCData.substr( 0, point);
					tmpCData.erase(0,point+1);
					ip.d1 = stringToInt(tmpnum);
					
					//tmpCData = cdata[i].data;
					point = tmpCData.find(".");
					tmpnum = tmpCData.substr( 0, point);
					tmpCData.erase(0,point+1);
					ip.d2 = stringToInt(tmpnum);

					//tmpCData = cdata[i].data;
					point = tmpCData.find(".");
					tmpnum = tmpCData.substr( 0, point);
					tmpCData.erase(0,point+1);
					ip.d3 = stringToInt(tmpnum);

					//tmpCData = cdata[i].data;
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

		}
	
    

	std::cout << "name:" << name << "\tIP:" << (int)ip.d1 << "." << (int)ip.d2 << "." << (int)ip.d3 << "." << (int)ip.d4; 

	return;
}