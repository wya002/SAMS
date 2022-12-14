#pragma once
#include "TCC.h"
#include "AirThreat.h"
#include <winsock2.h> // 윈속2 메인 헤더
#pragma comment(lib, "ws2_32") // ws2_32.lib 링크
#include <thread>
#include <chrono>
#include <ws2tcpip.h> // 윈속2 확장 헤더
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>

class UDPSocket
{
public:
	UDPSocket() {};
	UDPSocket(TCC& tcc);
	~UDPSocket();
	void createSocket(TCC& tcc);
	void sendData(Position udpCurPos);
	void receiveData();
	void err_quit(const char* msg);
	void err_display(const char* msg);
	void setATSCurPos(Position atsCurPos);
	void getATSState(string atsStatus);
private:
	SOCKET udpSocket;
	struct sockaddr_in serveraddr;
	Position udpCurPos;
	ATSPosition atsInitPos;
	ATSPosition atsTargetPos;
	State atsState;
};

struct ATSPosition
{
	double x, y;
};
