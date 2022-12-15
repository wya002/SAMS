 #include "UDP.h"
#include <thread>
#include <chrono>
#include <ws2tcpip.h> // ����2 Ȯ�� ���
#include <iostream>
#include "Simulator.h"
#include "ATS.h"

#define _CRT_SECURE_NO_WARNINGS // ���� C �Լ� ��� �� ��� ����
#define _WINSOCK_DEPRECATED_NO_WARNINGS // ���� ���� API ��� �� ��� ����
#define	BUFSIZE	512

UDP::UDP(int simulatorPort, queue<string>* aMsgQueue, queue<string>* mMsgQueue)
{
	port = simulatorPort;
	atsMsgQueue = aMsgQueue;
	mssMsgQueue = mMsgQueue;
	received = false;

	// ���� �ð� ����
	auto start = std::chrono::steady_clock::now();

	// ���� �ʱ�ȭ
	WSADATA wsa;
	while (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {};

	createSocket();
}

UDP::~UDP()
{
	// ���� �ݱ�
	closesocket(udpSocket);

	// ���� ����
	WSACleanup();
}

bool UDP::getReceived()
{
	return received;
}

void UDP::createSocket()
{
	// ���� ����
	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (udpSocket == INVALID_SOCKET) err_quit("socket()");

	// bind()
	struct sockaddr_in simulatorAddr;
	memset(&simulatorAddr, 0, sizeof(simulatorAddr));
	simulatorAddr.sin_family = AF_INET;
	simulatorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	simulatorAddr.sin_port = htons(port);
	int retval = bind(udpSocket, (struct sockaddr*)&simulatorAddr, sizeof(simulatorAddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");
}

void UDP::sendData()
{
	queue<string>* mQueue;

	if (port == 9000) mQueue = atsMsgQueue;
	else mQueue = mssMsgQueue;

	while (1) {
		//struct sockaddr_in sendAddr;

		int addrlen = sizeof(simulatorAddr);
		char buf[BUFSIZE + 1];
		if (mQueue->size() > 0) {
			cout << "\nSend Message : ";
			strcpy_s(buf, mQueue->front().c_str());
			cout << buf << endl;
			mQueue->pop();

			// '\n' ���� ����
			int len = (int)strlen(buf);
			if (buf[len - 1] == '\n')
				buf[len - 1] = '\0';

			// ������ ������
			int retval = sendto(udpSocket, buf, (int)strlen(buf), 0, (struct sockaddr*)&simulatorAddr, addrlen);
			if (retval == SOCKET_ERROR) {
				err_display("sendto()");
			}
		}
	}
}

void UDP::receiveData()
{
	char receiveBuf[BUFSIZE + 1];
	while (1) {
		// ������ �ޱ�
		int addrlen = sizeof(simulatorAddr);
		int retval = recvfrom(udpSocket, receiveBuf, BUFSIZE, 0, (struct sockaddr*)&simulatorAddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			err_display("recvfrom()");
			break;
		}

		// ���ŵ� clientaddr ���� inet_ntop() �� ���ڿ� ������ addr �� ������
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &simulatorAddr.sin_addr, addr, sizeof(addr));

		// ���ڿ� ������ �ּ� addr �� ���� ������ ���
		receiveBuf[retval] = '\0';
		printf("[UDP/%s:%d] %s\n", addr, ntohs(simulatorAddr.sin_port), receiveBuf);

		string str = receiveBuf;
		if (str.compare("MSS_CONNECTED") == 0)
			mssMsgQueue->push("TCC_CONNECTED");
		else if (str.compare("ATS_CONNECTED") == 0)
			atsMsgQueue->push("TCC_CONNECTED");
		else if (str.find("AP") == string::npos)
			mssMsgQueue->push(str);


		received = true;
	}
}

void UDP::err_quit(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	MessageBoxA(NULL, (const char*)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// ���� �Լ� ���� ���
void UDP::err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[����] %s\n", (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// ���� �Լ� ���� ���
void UDP::err_display(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[%s] %s\n", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}
