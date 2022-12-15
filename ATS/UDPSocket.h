#pragma once
#include "TCC.h"
#include <winsock2.h> // ����2 ���� ���
#pragma comment(lib, "ws2_32") // ws2_32.lib ��ũ
#include <thread>
#include <chrono>
#include <ws2tcpip.h> // ����2 Ȯ�� ���
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <queue>
#include "Position.h"
#include "AirThreat.h"

using namespace std;

struct ATSPosition
{
	double x, y;
};

class UDPSocket
{
public:
	UDPSocket();
	UDPSocket(TCC& tcc, AirThreat& at);
	~UDPSocket();
	void createSocket(TCC& tcc);
	void sendData();
	void receiveData();
	void err_quit(const char* msg);
	void err_display(const char* msg);
	void setATSCurPos(Position atsCurPos);
	void getATSState(string atsStatus);
	void sendForConnecting();

private:
	AirThreat& airThreat;
	SOCKET udpSocket;
	struct sockaddr_in serveraddr;
	Position udpCurPos;
	ATSPosition atsInitPos;
	ATSPosition atsTargetPos;
	string atsState;
	bool tccReceived;
};
