#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#include <DxLib.h>

using std::string;
using std::ifstream;


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
    string a[10];
    ifstream fp( "./settings.txt");   

    if (!fp) {
        std::cout << "ファイルを開けませんでした。\n" << std::endl;
        return 1;
    }


    for (int i = 0; i <10; i++)
    {
        std::getline(fp, a[0]);
    }
    



}



