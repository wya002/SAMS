 #include "UDP.h"
#include <thread>
#include <chrono>
#include <ws2tcpip.h> // 윈속2 확장 헤더
#include <iostream>
#include "Simulator.h"
#include "ATS.h"

#define _CRT_SECURE_NO_WARNINGS // 구형 C 함수 사용 시 경고 끄기
#define _WINSOCK_DEPRECATED_NO_WARNINGS // 구형 소켓 API 사용 시 경고 끄기
#define	BUFSIZE	512

UDP::UDP(int simulatorPort, queue<string>* aMsgQueue, queue<string>* mMsgQueue)
{
	port = simulatorPort;
	atsMsgQueue = aMsgQueue;
	mssMsgQueue = mMsgQueue;
	received = false;

	// 시작 시간 측정
	auto start = std::chrono::steady_clock::now();

	// 윈속 초기화
	WSADATA wsa;
	while (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {};

	createSocket();
}

UDP::~UDP()
{
	// 소켓 닫기
	closesocket(udpSocket);

	// 윈속 종료
	WSACleanup();
}

bool UDP::getReceived()
{
	return received;
}

void UDP::createSocket()
{
	// 소켓 생성
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

			// '\n' 문자 제거
			int len = (int)strlen(buf);
			if (buf[len - 1] == '\n')
				buf[len - 1] = '\0';

			// 데이터 보내기
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
		// 데이터 받기
		int addrlen = sizeof(simulatorAddr);
		int retval = recvfrom(udpSocket, receiveBuf, BUFSIZE, 0, (struct sockaddr*)&simulatorAddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			err_display("recvfrom()");
			break;
		}

		// 수신된 clientaddr 값을 inet_ntop() 로 문자열 형태의 addr 로 변경함
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &simulatorAddr.sin_addr, addr, sizeof(addr));

		// 문자열 형태의 주소 addr 과 받은 데이터 출력
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

// 소켓 함수 오류 출력
void UDP::err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[오류] %s\n", (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// 소켓 함수 오류 출력
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
