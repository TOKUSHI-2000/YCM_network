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

extern IPDATA ip;

#endif
