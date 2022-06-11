#ifndef FUNCTION_HOST_HPP
#define FUNCTION_HOST_HPP

#include "communication.hpp"


class Host : public communication
{
private:
    int tmpNetHandle = -1;

protected:


public:
    Host();

    void IPcommu() override;
    void setBuffer(netBufferDate date);
};

#endif