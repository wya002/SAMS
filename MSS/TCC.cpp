#include "TCC.h"

TCC::TCC(const char* addr, int portNumber)
{
	ip = addr;
	port = portNumber;
}

const char* TCC::getIp()
{
	return ip;
}


int TCC::getPort()
{
	return port;
}
