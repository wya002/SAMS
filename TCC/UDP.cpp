#include "UDP.h"
#include <thread>
#include <chrono>
#include <ws2tcpip.h> // ����2 Ȯ�� ���
#include <iostream>
#include <string>
#include "Simulator.h"
#include "ATS.h"

#define _CRT_SECURE_NO_WARNINGS // ���� C �Լ� ��� �� ��� ����
#define _WINSOCK_DEPRECATED_NO_WARNINGS // ���� ���� API ��� �� ��� ����
#define	BUFSIZE	512

using namespace std;

UDP::UDP(Simulator& simulator)
{
	// ���� �ð� ����
	auto start = std::chrono::steady_clock::now();
	// ���� �ʱ�ȭ
	WSADATA wsa;
	while (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {};
	createSocket(simulator);
}

UDP::~UDP()
{
	// ���� �ݱ�
	closesocket(udpSocket);

	// ���� ����
	WSACleanup();
}

void UDP::createSocket(Simulator& simulator)
{
	// ���� ����
	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (udpSocket == INVALID_SOCKET) err_quit("socket()");

	// bind()
	struct sockaddr_in simulatorAddr;
	memset(&simulatorAddr, 0, sizeof(simulatorAddr));
	simulatorAddr.sin_family = AF_INET;
	simulatorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	simulatorAddr.sin_port = htons(simulator.getPort());
	int retval = bind(udpSocket, (struct sockaddr*)&simulatorAddr, sizeof(simulatorAddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	thread t(&UDP::receiveData, this);
	
	//sendData();

	t.join();
}

void UDP::sendData()
{
	struct sockaddr_in simulatorAddr;
	char buf[BUFSIZE + 1] = "hello";

	// '\n' ���� ����
	int len = (int)strlen(buf);
	if (buf[len - 1] == '\n')
		buf[len - 1] = '\0';

	// ������ ������
	int retval2 = sendto(udpSocket, buf, (int)strlen(buf), 0, (struct sockaddr*)&simulatorAddr, sizeof(simulatorAddr));
	if (retval2 == SOCKET_ERROR) {
		err_display("sendto()");
	}
}

void UDP::receiveData()
{
	struct sockaddr_in simulatorAddr;
	char sendBuf[BUFSIZE + 1] = "Hello World";
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

		// '\n' ���� ����
		int len = (int)strlen(sendBuf);
		if (sendBuf[len - 1] == '\n')
			sendBuf[len - 1] = '\0';

		// ������ ������
		int retval1 = sendto(udpSocket, sendBuf, (int)strlen(sendBuf), 0, (struct sockaddr*)&simulatorAddr, sizeof(simulatorAddr));
		if (retval1 == SOCKET_ERROR) {
			err_display("sendto()");
			break;
		}
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

int main()
{
	ATS ats = ATS("127.0.0.1", 5000);
	UDP udp = UDP(ats);

}