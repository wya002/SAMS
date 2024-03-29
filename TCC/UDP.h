#pragma once
#pragma comment(lib, "ws2_32") // ws2_32.lib 링크
#include "Simulator.h"
#include <winsock2.h> // 윈속2 메인 헤더
#include <queue>
#include <string>

using namespace std;

class UDP
{
public :
	UDP();
	UDP(int simulatorPort, queue<string>* aMsgQueue, queue<string>* mMsgQueue, pair<bool&, bool&> c);
	~UDP();
	void createSocket();
	void sendData();
	void receiveData();
	void err_display(const char* msg);
	void err_display(int errcode);
	bool getReceived();

private :
	pair<bool&, bool&> connect;
	queue<string>* atsMsgQueue;
	queue<string>* mssMsgQueue;
	struct sockaddr_in simulatorAddr;
	SOCKET udpSocket;
	int port;
	bool received;

};