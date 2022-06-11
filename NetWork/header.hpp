#ifndef HEARDER_HPP
#define HEARDER_HPP

//#include <vector>
#include <array>
#include <iostream>

#include <DxLib.h>

constexpr int netPort = 9875;

constexpr int IpNum = 32;

struct netBufferDate
{

    union date
    {
        struct header                   //ヘッダー
        {
            char volume;                //バッファの数

            int dateType;               //主データのタイプ
            
            char id;                    //自分のID

            char newAva;                //新規に参加したアバター

        }header;

        struct setUpdate                //初期化用のデータ
        {
            char modelId;               //モデルのID
            char name[4];              //名前(仮)
        }setUpdate;
        
        struct body                     //本体データ
        {
            char id;                    //アバターのID
            float x;                    //X座標
            float y;                    //Y座標
            float angle;                //回転方向

        }body;


        
        
    }date;
    
};


#endif