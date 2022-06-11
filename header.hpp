#ifndef HEADER_H
#define HEADER_H

#include <windows.h>
#include <DxLib.h>
#include <string>
#include <math.h>

#include <iostream>
constexpr char numOfAvts = 32;

struct netDate
{
    char id;
    char kind;
    union body
    {
        struct setUpC
        {
            //char name[32] = "HOGEHOGE";
            unsigned short type;
        }setUpC;

        struct avatarDate
        {
            VECTOR position;
            int angle;
        }avatarDate;
        
        
    }boby;
    


};
#endif
