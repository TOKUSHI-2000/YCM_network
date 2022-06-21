#ifndef FUNCTION_HOST_HPP
#define FUNCTION_HOST_HPP

#include "network.hpp"


class Host : public NetWork
{
private:
    int tmpNetHandle = -1;

protected:


public:
    Host();

    void IPcommu() override;
    void setBuffer(NetBufferDate date) override;
};

#endif