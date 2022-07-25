#ifndef HEADER_H
#define HEADER_H

#include <windows.h>
#include <DxLib.h>
#include <string>
#include <math.h>

#include <iostream>

struct NETDATA
{
    union body
    {
        struct header
        {
            char dataType;
        }header;

        struct position
        {
            VECTOR vetctor;
            float angle;//向き
        }position;
        
        
    }body;
    
};


constexpr char numOfAvts = 32;

constexpr int BITS_STOP_MAIN_THREAD = (1<<0);
constexpr int BITS_FINISH_MAIN_THREAD = (1<<1);

extern IPDATA ip;
extern int SystemBits;

#endif
