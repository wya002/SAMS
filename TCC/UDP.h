#pragma once
#pragma comment(lib, "ws2_32") // ws2_32.lib ��ũ
#include "Simulator.h"
#include <winsock2.h> // ����2 ���� ���
#include <queue>
#include <string>

using namespace std;

class UDP
{
public :
	UDP() {};
	UDP(int simulatorPort, queue<string>* aMsgQueue, queue<string>* mMsgQueue);
	~UDP();
	void createSocket();
	void sendData();
	void receiveData();
	void err_quit(const char* msg);
	void err_display(const char* msg);
	void err_display(int errcode);
	bool getReceived();

private :

	queue<string>* atsMsgQueue;
	queue<string>* mssMsgQueue;
	struct sockaddr_in simulatorAddr;
	SOCKET udpSocket;
	int port;
	bool received;

};