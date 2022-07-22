#ifndef CHARCTER_H
#define CHARCTER_H

#include "header.hpp"
#ifdef AVATAR_CPP

#endif
constexpr float MOVESPEED = 30.0f;
constexpr float MOVEDASHSPEED = 45.0f;

#define CAMERA_ANGLE_SPEED		3.0f

// カメラの注視点の高さ
#define CAMERA_LOOK_AT_HEIGHT		400.0f

// カメラと注視点の距離
#define CAMERA_LOOK_AT_DISTANCE		2150.0f

extern std::string str[3];
class AVATAR
{
private:

protected:
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
    AVATAR();
    ~AVATAR();
    void setModel(short id);
    void drawModel();
    virtual void moveModel(NETDATA data);//int は仮
    
};



class MYAVATER :public AVATAR
{
private:
    
	float  CameraHAngle ;
	float  CameraVAngle ;
	float  SinParam ;
	float  CosParam ;
public:
    char num;
    MYAVATER(/* args */);
    ~MYAVATER();

    void moveModel(NETDATA data) override;
    void MoveCamera();
};


#endif



