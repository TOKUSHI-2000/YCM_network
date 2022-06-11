#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#include "header.hpp"

class network
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
    network();
    ~network();

    virtual void IPcommu() =0;
    netBufferDate getBuffer(int i);
};


#endif