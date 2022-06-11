#include "client.hpp"

Client::Client(IPDATA ipDate_) : ipDate(ipDate_)
{

}


void Client::IPcommu()
{
    netHandle[0] = -2;
    
    ipSysCondition |= (1 << 0);

    while (ipSysCondition & (1 << 0))
    {
        int tmpNetHandle;
        tmpNetHandle = ConnectNetWork( ipDate, netPort);
        if (tmpNetHandle != -1)
        {
            netHandle[0] = tmpNetHandle;
            return;
        }
        
    }

    while (ipSysCondition & (1 << 0))
    {
        if (GetNetWorkDataLength( netHandle[0]) >= 0)
        {
            NetWorkRecv(netHandle[0], &headerBuffer, sizeof(netBufferDate));
            
            NetWorkRecv(netHandle[0], &netBuffer[0], sizeof(netBufferDate)*
                headerBuffer.date.header.volume);
            break;
        }
    }
    
    ipSysCondition |= (1 << 1);

    while (ipSysCondition & (1 << 1))
    {
        ProcessMessage();
    }
    
    int time = GetNowCount();

    while (ipSysCondition & (1 << 0))
    {

        
        if (GetNetWorkDataLength( netHandle[0] ) >= 0)
        {
            
            NetWorkRecv(netHandle[0], &headerBuffer, sizeof(netBufferDate));
            
            if (headerBuffer.date.header.dateType == 2)
            {  
                for(int i = 0; i < headerBuffer.date.header.volume; i++)
                {
                    if (headerBuffer.date.header.id != i)NetWorkRecv(netHandle[0], &netBuffer[0], sizeof(netBufferDate));
                }
            }
            else
            {
                
            }
        }
        
        //データの送信
        if (time >= GetNowCount() + 20)
        {
            NetWorkSend(netHandle[0], &netBuffer[0], sizeof(netBufferDate));
        }
        

    }
    


}

void Client::setBuffer(netBufferDate date)
{
    setBufferX( date, myId);
}

void Client::worldSetUpF()
{
    ipSysCondition &= ~(1 << 1);
}

