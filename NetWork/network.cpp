#include "communication.hpp"


communication::communication()
{
    ipSysCondition = 0;
}


communication::~communication()
{

}


void communication::setBufferX(netBufferDate date, int id)
{
    
    netBuffer[id] = date;
    
}


netBufferDate communication::getBuffer(int i)
{
    return netBuffer[i];
}


