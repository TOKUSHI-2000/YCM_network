#include "network.hpp"


NetWork::NetWork()
{
    ipSysCondition = 0;
}


NetWork::~NetWork()
{

}


void NetWork::setBufferX(netBufferDate date, int id)
{
    
    netBuffer[id] = date;
    
}


netBufferDate NetWork::getBuffer(int i)
{
    return netBuffer[i];
}


