#include "network.hpp"


NetWork::NetWork()
{
    ipSysCondition = 0;
}


NetWork::~NetWork()
{

}


void NetWork::setBufferX(NetBufferDate date, int id)
{
    
    netBuffer[id] = date;
    
}


NetBufferDate NetWork::getBuffer(int i)
{
    return netBuffer[i];
}


