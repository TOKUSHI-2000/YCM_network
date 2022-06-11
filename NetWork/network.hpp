#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#include "header.hpp"

netBufferDate setUpdate;

class communication
{
private:
protected:
    //ネットハンドル-2自分-1は未定義
    char ipSysCondition;
    //バッファヘッダーのデータ
    netBufferDate headerBuffer;

    std::array<int,IpNum> netHandle = {};
    std::array<netBufferDate,IpNum> netBuffer = {};

    void setBufferX(netBufferDate date, int id);
public:
    communication();
    ~communication();

    virtual void IPcommu();
    netBufferDate getBuffer(int i);
};


#endif