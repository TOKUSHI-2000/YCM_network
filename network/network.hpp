#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#include "header.hpp"
#include "netWorkBuffer.h"


class NetWork
{
private:
protected:
    //ネットハンドル-2自分-1は未定義
    char ipSysCondition;
    //バッファヘッダーのデータ
    NetBufferDate headerBuffer;

    std::array<int,IpNum> netHandle = {};
    std::array<NetBufferDate,IpNum> netBuffer = {};

    void setBufferX(NetBufferDate date, int id);
public:
    NetWork();
    ~NetWork();

    virtual void IPcommu() =0;
    NetBufferDate getBuffer(int i);
    virtual void setBuffer(NetBufferDate date) =0;
};


#endif