#pragma once
#include "TCC.h"
#include <winsock2.h> // 윈속2 메인 헤더
#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

class UDPSocket
{
public:
	UDPSocket() {};
	UDPSocket(TCC& tcc);
	~UDPSocket();
	void createSocket(TCC& tcc);
	void sendData();
	void receiveData();
	void err_quit(const char* msg);
	void err_display(const char* msg);

private:
	
	SOCKET udpSocket;
	struct sockaddr_in serveraddr;
};