#pragma once
class TCC
{
public :
	void setIp(const char* addr);
	const char* getIp();
private:
	const char* ip;
};