// キャラクターに付いていくカメラ
//
// ＜操作＞
// 方向キー：キャラクターモデル移動
// Z,Cキー：カメラの水平角度を変更
// S,Xキー：カメラの垂直角度を変更
#include "avatar.hpp"
#include "main.hpp"


// ラインを描く範囲
constexpr float LINE_AREA_SIZE = 10000.0f;

// ラインの数
constexpr int LINE_NUM = 50;


IPDATA ip;
NETDATA netData[numOfAvts];

int SystemBits = 0;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	float  cameraHAngle ;
	float  cameraVAngle ;
	
	int fileHandle;

	int time;//時間調整

	std::string name;
	int serverBits = 0;

	short charaId =0;
	char hostId = false;
	static HANDLE th;

	AVATAR* Avatar[numOfAvts];
	MYAVATER* AvatarMe;

	signed char myAvaterId = -1;

	ip.d1=1;
	ip.d2=1;
	ip.d3=1;
	ip.d4=1;

	readIniFile( name, ip, serverBits);
	std::cout << name << "\n";

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

	AvatarMe = new MYAVATER();
	//netSituation &= (1 << 0);
	//netSituation &= (1 << 1);
	if (1/*hostId == 1*/)
	{
		
		AvatarMe->num = 0;
		Avatar[0] = AvatarMe;//ホストはアバターID0を登録
		std::cout << "ホスト\n";

		//第二のアバターを創る処理
		Avatar[1] = new AVATAR();
		Avatar[1]->setModel(1);
		netData->body.position.vetctor = VGet(0.0, 0.0, 0.0);
		netData->body.position.angle = 0.0;
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
    charaId = 0;
	AvatarMe->setModel(charaId);
	//Host a;
	//Communication = &a;
	std::cout << "CharactorSetOK\n";
	//Communication->setBuffer(AvatarMe->GetSetUp());
	std::cout << "BufferセットアップOK";

	// カメラの向きを初期化
	cameraHAngle = 0.0f ;
	cameraVAngle = 40.0f ;

	
	
	// カメラのクリッピング距離を設定
	SetCameraNearFar( 100.0f, 50000.0f );

	// 背景の色を設定する
	SetBackgroundColor( 128, 200, 100 ) ;

	time = GetNowCount();

	SystemBits |= BITS_FINISH_MAIN_THREAD;
	// メインループ
	while(SystemBits & BITS_FINISH_MAIN_THREAD)
	{
		
		// 画面のクリア
		ClearDrawScreen() ;
		
		//移動
		for (char i = 0; i <32; i++)
		{
			if(Avatar[i] != nullptr){
				AvatarMe->moveModel(netData[i]);
			}
		}

		AvatarMe->MoveCamera();
		

		for (char i = 0; i <32; i++)
		{
			if(Avatar[i] != nullptr){
				Avatar[i]->drawModel();
			}
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
		if (GetNowCount() > time + 20)
		{
			if (ProcessMessage()!=0)
			{
				SystemBits &= ~BITS_FINISH_MAIN_THREAD;
			}

		}
		time = GetNowCount();
		
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