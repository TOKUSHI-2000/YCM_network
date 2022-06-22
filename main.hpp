#ifndef MAIN_HPP
#define MAIN_HPP

#include "string"
#include <DxLib.h>

#include "network/host.hpp"
#include "network/client.hpp"

int stringToInt(std::string str);
extern void readFile(IPDATA& ip, std::string& name, int& ModelId);

#endif