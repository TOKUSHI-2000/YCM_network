#include "network.hpp"


network::network()
{
    ipSysCondition = 0;
}


network::~network()
{

}


void network::setBufferX(netBufferDate date, int id)
{
    
    netBuffer[id] = date;
    
}


netBufferDate network::getBuffer(int i)
{
    return netBuffer[i];
}


