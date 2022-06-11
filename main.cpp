// キャラクターに付いていくカメラ
//
// ＜操作＞
// 方向キー：キャラクターモデル移動
// Z,Cキー：カメラの水平角度を変更
// S,Xキー：カメラの垂直角度を変更

#include "character.hpp"

// 移動速度
//#define MOVESPEED			10.0f

// ラインを描く範囲
constexpr float LINE_AREA_SIZE = 10000.0f;

// ラインの数
constexpr int LINE_NUM = 50;

std::string str[3];
/*
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
*/


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	float  cameraHAngle ;
	float  cameraVAngle ;
	
	int fileHandle;

	short charaId;
	char hostId = false;
	static HANDLE th;

	Character* Avatar[numOfAvts];
	MyCharacter* AvatarMe;

	signed char myAvaterId = -1;

	// ウインドウモードで起動
	ChangeWindowMode( TRUE ) ;
	SetAlwaysRunFlag( TRUE );

	SetMainWindowText((TCHAR*)"ゆっくりしていってね");
	
	// ＤＸライブラリの初期化
	if( DxLib_Init() < 0 ) return -1 ;

	for (char i = 0; i < 32; i++)
	{
		Avatar[i] = nullptr;
	}
	
	// 描画先を裏画面にする
	SetDrawScreen( DX_SCREEN_BACK ) ;


	fileHandle = FileRead_open((TCHAR*)"./settings.txt", FALSE);

	for (int i =0; FileRead_eof( fileHandle ) == 0 && i<2 ; i++)
	{
		TCHAR strc[128]; 
		FileRead_gets( strc, 128, fileHandle);
		str[i] = (char*)strc; 
	}
	FileRead_close(fileHandle);

	{	
	
		int i;
		for (i = 0; i < 3; i++)
		{
			if ( 0 == str[i].find("server:"))break;
			if (i == 3) i= -1;
		
		}
	
		if (i == -1)
		{
			charaId = 1;
		}
		else if (str[i].find("\"h\"") != 5 && str[i].find("\"h\"") != std::string::npos)
		{
    		charaId = 0;
			hostId = 1;
		}
		else
		{
			charaId = 1;
		}
	}

	{
		std::string tmpStr;
		std::string tmpStrNum;
		int num;
		int i;
		for (i = 0; i < 3; i++)
		{
			if( 0 == str[i].find("ip:"))break;
			if (i == 3) i= -1;
		}
		if ( i == 0 || i >3)
		{
			DxLib_End();
			return 0;
		}
		else
		{
			tmpStr = str[i];
		}
		
		printf("%s\n", tmpStr.c_str());
		tmpStr.erase( 0, 4);
		num = tmpStr.find(".");
		tmpStrNum = tmpStr.substr(0,num);
		tmpStr.erase(0, num + 1);
		//ip.d1 = stringToInt(tmpStrNum);

		num = tmpStr.find(".");
		tmpStrNum = tmpStr.substr(0,num);
		tmpStr.erase(0, num + 1);
		//ip.d2 = stringToInt(tmpStrNum);

		num = tmpStr.find(".");
		tmpStrNum = tmpStr.substr(0,num);
		tmpStr.erase(0, num + 1);
		//ip.d3 = stringToInt(tmpStrNum);
		
		num = tmpStr.find(".");
		tmpStrNum = tmpStr.substr(0,num);
		//ip.d4 = stringToInt(tmpStrNum);
		
		
		ip.d1 = 192;
		ip.d2 = 168;
		ip.d3 = 1;
		ip.d4 = 4;
	}

	AvatarMe = new MyCharacter();
	//netSituation &= (1 << 0);
	//netSituation &= (1 << 1);
	if (hostId == 1)
	{
		
		AvatarMe->num = 0;
		Avatar[0] = AvatarMe;//ホストはアバターID0を登録
	}
	else
	{

		//DrawString(0,0,"接続中\n  べーた版\n  ",GetColor(255,255,255), true);
		ProcessMessage();
		int* netHandle = new int;
		//netSituation &= ~(1 << 2);
		DrawFormatString(0,0,GetColor(255,255,255),(TCHAR*)"接続中\n  べーた版\n  IP:%d.%d.%d.%d",ip.d1,ip.d2,ip.d3,ip.d4);
		ScreenFlip();
		while (!(1/*netSituation & (1 << 2)*/))
		{
			if ( ProcessMessage() != 0)
			{
				
				//netSituation &= ~(1 << 0);
				//netSituation &= ~(1 << 1);

				DxLib_End();
				return 0;
			}
			printf("setting now");
		}
		
		std::cout << *netHandle;
		while ( *netHandle < 0)
		{
			if ( ProcessMessage() != 0)
			{
				
				//netSituation &= ~(1 << 0);
				//netSituation &= ~(1 << 1);

				DxLib_End();
				return 0;
			}
			
			printf("%d", *netHandle);
		}
		printf("OK");
		AvatarMe->num = NetWorkRecv( *netHandle, &AvatarMe->num , 1 ) ;
		Avatar[AvatarMe->num] = AvatarMe;
		
		//th=CreateThread(0,0,(LPTHREAD_START_ROUTINE)Client,(LPVOID)1,0,NULL);
		
	}
    
	AvatarMe->CharactorSet(charaId);
	//Host a;
	//Communication = &a;
	std::cout << "CharactorSetOK\n";
	//Communication->setBuffer(AvatarMe->GetSetUp());
	std::cout << "BufferセットアップOK";

	// カメラの向きを初期化
	cameraHAngle = 0.0f ;
	cameraVAngle = 40.0f ;

	
	for (int i = 0; i < 32; i++)
	{
		if (Avatar[i] != nullptr)
		{
		
			if (AvatarMe->num != i)
			{
	//			Avatar[i]->setMove(Communication->getBuffer(i));
			}
		}
	}
	
	// カメラのクリッピング距離を設定
	SetCameraNearFar( 100.0f, 50000.0f );

	// 背景の色を設定する
	SetBackgroundColor( 128, 200, 100 ) ;

	// メインループ
	while( ProcessMessage() == 0 )
	{

		// 画面のクリア
		ClearDrawScreen() ;
		
		AvatarMe->GetMoveKey();

		AvatarMe->MoveCamera();
		
		AvatarMe->CameraMove();

		for (char i = 0; i <32; i++)
		{
			if(Avatar[i] != nullptr)
				Avatar[i]->DrawModel();
		}
		

	//	Communication->setBuffer( AvatarMe->GetDate());

		// 位置関係が分かるように地面にラインを描画する
		{
			int i ;
			VECTOR Pos1 ;
			VECTOR Pos2 ;

			SetUseZBufferFlag( TRUE ) ;

			Pos1 = VGet( -LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f ) ;
			Pos2 = VGet( -LINE_AREA_SIZE / 2.0f, 0.0f,  LINE_AREA_SIZE / 2.0f ) ;
			for( i = 0 ; i <= LINE_NUM ; i ++ )
			{
				DrawLine3D( Pos1, Pos2, GetColor( 255,255,255 ) ) ;
				Pos1.x += LINE_AREA_SIZE / LINE_NUM ;
				Pos2.x += LINE_AREA_SIZE / LINE_NUM ;
			}

			Pos1 = VGet( -LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f ) ;
			Pos2 = VGet(  LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f ) ;
			for( i = 0 ; i < LINE_NUM ; i ++ )
			{
				DrawLine3D( Pos1, Pos2, GetColor( 255,255,255 ) ) ;
				Pos1.z += LINE_AREA_SIZE / LINE_NUM ;
				Pos2.z += LINE_AREA_SIZE / LINE_NUM ;
			}

			SetUseZBufferFlag( FALSE ) ;
		}

		// 裏画面の内容を表画面に反映
		ScreenFlip() ;
	}
	//netSituation &= ~(1 << 0);
	//netSituation &= ~(1 << 1);
	// ＤＸライブラリの後始末
	DxLib_End() ;
	DWORD result;
	do
	{
		GetExitCodeThread( th, &result);
	} while (STILL_ACTIVE==result);
	

	// ソフトの終了
	return 0 ;
}