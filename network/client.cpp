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
            NetWorkRecv(netHandle[0], &headerBuffer, sizeof(NetBufferDate));
            
            NetWorkRecv(netHandle[0], &netBuffer[0], sizeof(NetBufferDate)*
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

    //データの受信
    while (ipSysCondition & (1 << 0))
    {

        
        if (GetNetWorkDataLength( netHandle[0] ) >= 0)
        {
            
            NetWorkRecv(netHandle[0], &headerBuffer, sizeof(NetBufferDate));
            
            switch (headerBuffer.date.header.dateType)
            {
            case 0:

                break;
            case 1:

                break;
            case 2:
                for(int i = 0; i < headerBuffer.date.header.volume; i++)
                {
                    if (headerBuffer.date.header.id != i)NetWorkRecv(netHandle[0], &netBuffer[0], sizeof(NetBufferDate));
                }
                break;
            default:
                break;
            }
        }
        
        //データの送信
        if (time >= GetNowCount() + 20)
        {
            NetWorkSend(netHandle[0], &netBuffer[0], sizeof(NetBufferDate));
        }
        

    }
    


}

void Client::setBuffer(NetBufferDate date)
{
    setBufferX( date, myId);
}

void Client::worldSetUpF()
{
    ipSysCondition &= ~(1 << 1);
}

