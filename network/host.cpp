#include "host.hpp"


Host::Host()
{
    netHandle.fill(-1);
    netHandle[1] = -2;
}


NetBufferDate setUpdate;

void Host::IPcommu()
{
    int time = GetNowCount();

    netHandle[0] = -2;
    
    ipSysCondition |= (1 << 0);

    //ポートの開通
    PreparationListenNetWork(netPort);


    while (ipSysCondition |= (1 << 0))
    {
        
        //新しい切断リクエストを受け取る
        tmpNetHandle =GetLostNetWork();
        if (tmpNetHandle != -1)
        {
            for (int i = 2; i < IpNum; i++)
            {
                if (tmpNetHandle == netHandle[i])
                {
                    netHandle[i] = -1;
                    return;
                }
                
            }
               
        }
        
        
        //新しい通信リクエストを受け取る
        tmpNetHandle = GetNewAcceptNetWork();
        if (tmpNetHandle != -1)
        {
            int a = 0;
            for (int i = 2; i < IpNum; i++)
            {
                if (netHandle[i] != -1)
                {
                    
                    a = 1;
                    break;
                }
                
            }
            
            if ( a == 0 )
            {
                StopListenNetWork();
            }

        }

        
        
    }
    
    //データを受け取る
    for (int i = 0; i < IpNum; i++)
    {
        if (netHandle[i] < 0 )
        {
            if (GetNetWorkDataLength( netHandle[i] ) >= 0){
                NetWorkRecv( netHandle[i], &headerBuffer, sizeof(NetBufferDate)) ;

                switch (headerBuffer.date.header.dateType)
                {
                case 0:
                
                    break;
                case 1:
                    NetWorkRecv(netHandle[i], &setUpdate, sizeof(NetBufferDate)) ;
                
                    break;
                case 2:
                    NetWorkRecv(netHandle[i], &netBuffer[i], sizeof(NetBufferDate));
                    break;
                default:
                    break;
                }
            }
        }
        
    }
    
    //データを送る
    if (time +20 >= GetNowCount())
    {
    
        netBuffer[0].date.header.dateType = 2;
    
        for (int i = IpNum - 1; i <= 0; i++)
        {
            if (netHandle[i] == -1)
            {
            netBuffer[0].date.header.volume = i;
            return;

            }
        }


        for (int i = 0; i < IpNum; i++)
        {
            if (netHandle[i] < 0)
            {
            
                netBuffer[0].date.header.id = i;

                NetWorkSend(netHandle[i], &netBuffer,
                    netBuffer[0].date.header.volume * sizeof(NetBufferDate));
            }
        }


    }
    

    StopListenNetWork();
}

void Host::setBuffer(NetBufferDate date)
{
    
    setBufferX( date, 0);

}

