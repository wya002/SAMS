#pragma once

#include "TypeDef.h"
#include "Missile.h"
#include "TCC.h"
#pragma comment(lib, "ws2_32") // ws2_32.lib 링크
#include <thread>
#include <chrono>
#include <winsock2.h> // 윈속2 메인 헤더
#include <ws2tcpip.h> // 윈속2 확장 헤더
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>

#define _CRT_SECURE_NO_WARNINGS
#define   BUFSIZE   512

class UDPSocket
{
public:
	UDPSocket() {};
	UDPSocket(TCC& tcc);
	~UDPSocket();
	void createSocket(TCC& tcc);
	void sendPos(Position sendpos);
	void sendEvent(const char *sendEvent);
	void receiveData();
	void err_quit(const char* msg);
	void err_display(const char* msg);
	Position getMinitPos();
	Position getMcurPos();
private:
	Position MinitPos;
	Position McurPos;
	MissileState Mstate;
	SOCKET udpSocket;
	struct sockaddr_in serveraddr;
};

