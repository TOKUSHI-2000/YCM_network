#ifndef NET_WORK_BUFFER_H
#define NET_WORK_BUFFER_H

#include <DxLib.h>

typedef struct tagNetBufferDate
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
            float z;                    //Z座標
            float angle;                //回転方向

        }body;


        
        
    }date;
    
}NetBufferDate;

#endif