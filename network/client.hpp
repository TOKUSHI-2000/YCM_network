#ifndef FUNCTION_CLIENT_HPP
#define FUNCTION_CLIENT_HPP

#include "network.hpp"



class Client : public network
{
private:
    const IPDATA ipDate;
    char myId;
protected:

public:
    Client(IPDATA ipDate_);

    void IPcommu() override;
    void setBuffer(netBufferDate date);

    void worldSetUpF();
};


#endif