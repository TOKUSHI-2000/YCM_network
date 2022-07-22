#define AVATAR_CPP
#include "avatar.hpp"

float getSpeed()
{
	if (CheckHitKey(KEY_INPUT_LSHIFT))
	{
		return MOVEDASHSPEED;
	}
	else
	{
		return MOVESPEED;
	}
	
}


AVATAR::AVATAR()
{
}

void AVATAR::setModel(short id)
{
	if (id == 0)
	{
		ModelHandle = -1;
		ModelHandle = MV1LoadModel((TCHAR*)"./Assets/yukkurireimu.mv1");
		MV1SetScale( ModelHandle, VGet( 150.0f, 150.0f, 150.0f ) );
		
	}
	else if (id == 1)
	{
		ModelHandle = MV1LoadModel((TCHAR*)"./Assets/yukkurimarisa.mv1");
		MV1SetScale( ModelHandle, VGet( 150.0f, 150.0f, 150.0f ) );
		
	}
}

void AVATAR::moveModel(NETDATA data)
{
	Position = data.body.position.vetctor;
	Angle = data.body.position.angle;
}


AVATAR::~AVATAR()
{
	MV1DeleteModel(ModelHandle);	
}



void AVATAR::drawModel()
{
	
	MV1SetRotationXYZ( ModelHandle, VGet( 0.0f, Angle / 180.0f * DX_PI_F, 0.0f ) ) ;
	MV1SetPosition( ModelHandle, Position ) ;
	MV1DrawModel( ModelHandle );
}

MYAVATER::MYAVATER()
{
	
    CameraHAngle = 0.0f ;
	CameraVAngle = 40.0f ;
}

MYAVATER::~MYAVATER()
{
}

//キャラクターの移動キー
void MYAVATER::moveModel(NETDATA data)
{
    // 移動ベクトルを初期化
	MoveVector = VGet( 0.0f, 0.0f, 0.0f ) ;

	// 移動しているかどうかのフラグを倒す
	MoveFlag = FALSE ;

	Angle = 90.0f -CameraVAngle;


	if( CheckHitKey( KEY_INPUT_A ) == 1 )
	{
		MoveFlag     = TRUE ;
		MoveVector.x -= getSpeed() ;
	}

	if( CheckHitKey( KEY_INPUT_D ) == 1 )
	{
		MoveFlag     = TRUE ;
		MoveVector.x += getSpeed() ;
	}

	if( CheckHitKey( KEY_INPUT_S ) == 1 )
	{
		MoveFlag     = TRUE ;
		MoveVector.z -= getSpeed() ;
	}

	if( CheckHitKey( KEY_INPUT_W ) == 1 )
	{
		MoveFlag     = TRUE ;
		MoveVector.z += getSpeed() ;
	}

    //体の角度を設定する
    if (MoveVector.x > 0)	
	{
		if (MoveVector.z > 0)
		{
			Angle = -135 - CameraHAngle;
		}
		else if (MoveVector.z < 0)
		{
			Angle = -45 - CameraHAngle;
		}
		else
		{
			Angle = -90.0f - CameraHAngle ;
		}
	}
	else if (MoveVector.x < 0)
	{
		if (MoveVector.z > 0)
		{
			Angle = 135 - CameraHAngle;
		}
		else if (MoveVector.z < 0)
		{
			Angle = 45 - CameraHAngle;
		}
		else
		{
			Angle = 90.0f - CameraHAngle ;
		}
	}
	else
	{
		if (MoveVector.z > 0)
		{
			Angle = 180.0f - CameraHAngle ;
		}
		else if (MoveVector.z < 0)
		{
			Angle = 0.0f - CameraHAngle ;
		}
		else
		{
			Angle = 180.0f - CameraHAngle ;
		}
	}

    //同時押しの移動アニメーションの無効化
	if (MoveVector.x == 0 && MoveVector.z == 0 )
	{
		MoveFlag = false;
	}
	
    
		
}

//カメラの移動
void MYAVATER::MoveCamera()
{
	
	// ZCSXキーでカメラの操作
		if( CheckHitKey( KEY_INPUT_RIGHT ) == 1 )
		{
			CameraHAngle += CAMERA_ANGLE_SPEED ;
			if( CameraHAngle >= 180.0f )
			{
				CameraHAngle -= 360.0f ;
			}
		}

		if( CheckHitKey( KEY_INPUT_LEFT ) == 1 )
		{
			CameraHAngle -= CAMERA_ANGLE_SPEED ;
			if( CameraHAngle <= -180.0f )
			{
				CameraHAngle += 360.0f ;
			}
		}

		if( CheckHitKey( KEY_INPUT_UP ) == 1 )
		{
			CameraVAngle += CAMERA_ANGLE_SPEED ;
			if( CameraVAngle >= 80.0f )
			{
				CameraVAngle = 80.0f ;
			}
		}

		if( CheckHitKey( KEY_INPUT_DOWN ) == 1 )
		{
			CameraVAngle -= CAMERA_ANGLE_SPEED ;
			if( CameraVAngle <= 0.0f )
			{
				CameraVAngle = 0.0f ;
			}
		}
    // 方向入力に従ってキャラクターの移動ベクトルと向きを設定
	/*if( CheckHitKey( KEY_INPUT_A ) == 1 )
	{
		Angle        = 90.0f - CameraHAngle ;
		MoveFlag     = TRUE ;
		MoveVector.x = -MOVESPEED ;
	}

	if( CheckHitKey( KEY_INPUT_D ) == 1 )
	{
		Angle        = -90.0f - CameraHAngle ;
		MoveFlag     = TRUE ;
		MoveVector.x = MOVESPEED ;
	}

	if( CheckHitKey( KEY_INPUT_S ) == 1 )
	{
		Angle        = 0.0f - CameraHAngle ;
		MoveFlag     = TRUE ;
		MoveVector.z = -MOVESPEED ;
	}

	if( CheckHitKey( KEY_INPUT_W ) == 1 )
	{
		Angle        = 180.0f - CameraHAngle ;
		MoveFlag     = TRUE ;
		MoveVector.z = MOVESPEED ;
	}*/

    // 移動した場合は、カメラの水平角度を考慮した方向に座標を移動する
	if( MoveFlag == TRUE )
	{

		VECTOR TempMoveVector ;

		// カメラの角度に合わせて移動ベクトルを回転してから加算
		SinParam = sin( CameraHAngle / 180.0f * DX_PI_F ) ;
		CosParam = cos( CameraHAngle / 180.0f * DX_PI_F ) ;
		TempMoveVector.x = MoveVector.x * CosParam - MoveVector.z * SinParam ;
		TempMoveVector.y = 0.0f ;
		TempMoveVector.z = MoveVector.x * SinParam + MoveVector.z * CosParam ;

        //体を移動する
		Position = VAdd( Position, TempMoveVector ) ;
	}

		// カメラの位置と向きを設定
		{
			VECTOR TempPosition1 ;
			VECTOR TempPosition2 ;
			VECTOR CameraPosition ;
			VECTOR CameraLookAtPosition ;

			// 注視点はキャラクターモデルの座標から CAMERA_LOOK_AT_HEIGHT 分だけ高い位置
			CameraLookAtPosition    = Position ;
			CameraLookAtPosition.y += CAMERA_LOOK_AT_HEIGHT ;

			// カメラの位置はカメラの水平角度と垂直角度から算出

			// 最初に垂直角度を反映した位置を算出
			SinParam = sin( CameraVAngle / 180.0f * DX_PI_F ) ;
			CosParam = cos( CameraVAngle / 180.0f * DX_PI_F ) ;
			TempPosition1.x = 0.0f ;
			TempPosition1.y =  SinParam * CAMERA_LOOK_AT_DISTANCE ;
			TempPosition1.z = -CosParam * CAMERA_LOOK_AT_DISTANCE ;

			// 次に水平角度を反映した位置を算出
			SinParam = sin( CameraHAngle / 180.0f * DX_PI_F ) ;
			CosParam = cos( CameraHAngle / 180.0f * DX_PI_F ) ;
			TempPosition2.x = CosParam * TempPosition1.x - SinParam * TempPosition1.z ;
			TempPosition2.y = TempPosition1.y ;
			TempPosition2.z = SinParam * TempPosition1.x + CosParam * TempPosition1.z ;

			// 算出した座標に注視点の位置を加算したものがカメラの位置
			CameraPosition = VAdd( TempPosition2, CameraLookAtPosition ) ;

			// カメラの設定に反映する
			SetCameraPositionAndTarget_UpVecY( CameraPosition, CameraLookAtPosition );
		}
	

}





