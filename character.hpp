#ifndef CHARCTER_H
#define CHARCTER_H

#include "header.hpp"


#define MOVESPEED			15.0f

#define CAMERA_ANGLE_SPEED		3.0f

// カメラの注視点の高さ
#define CAMERA_LOOK_AT_HEIGHT		400.0f

// カメラと注視点の距離
#define CAMERA_LOOK_AT_DISTANCE		2150.0f

extern std::string str[3];

class Character
{
private:
protected:
    static HANDLE th;
    int ModelHandle;
    std::string Name;

    int RunFlag;
    int Angle;
    VECTOR MoveVector ;
    int MoveFlag;
public:
    VECTOR Position ;
    /* data */
public:
    Character();
    ~Character();
    void CharactorSet(short id);
    void DrawModel();
    void setMove(netDate tmp);
};



class MyCharacter :public Character
{
private:
    
	float  CameraHAngle ;
	float  CameraVAngle ;
	float  SinParam ;
	float  CosParam ;
public:
    char num;
    MyCharacter(/* args */);
    ~MyCharacter();

    void GetMoveKey();
    void MoveCamera();
    void CameraMove();
    netDate GetSetUp();
    netDate GetDate();
};


#endif



