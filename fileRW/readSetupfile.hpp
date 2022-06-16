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

int readFile()
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
			cdata[a].type = tmpStr[a].substr(0,a-1);
			cdata[a].data = tmpStr[a].substr( a, tmpStr->length());
		}
		
	}
	

	
    



}



