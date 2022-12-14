#pragma once
#include "Simulator.h"
#include <winsock2.h> // ����2 ���� ���
#pragma comment(lib, "ws2_32") // ws2_32.lib ��ũ

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

