#pragma once

class TCC
{
public:
	TCC() {};
	TCC(const char* addr, int portNumber);
	const char* getIp();
	int getPort();

private:
	const char* ip;
	int port;
};

