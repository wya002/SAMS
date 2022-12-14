#pragma once
#include "Simulator.h"
#include <winsock2.h> // 윈속2 메인 헤더
#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

class UDP
{
public :
	UDP() {};
	UDP(Simulator& simulator);
	~UDP();
	void createSocket(Simulator& simulator);
	void sendData();
	void receiveData();
	void err_quit(const char* msg);
	void err_display(const char* msg);
	void err_display(int errcode);

private :
	SOCKET udpSocket;
	struct sockaddr_in simulatorAddr;
};

