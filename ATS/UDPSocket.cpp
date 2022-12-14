#include "UDPSocket.h"

#define	BUFSIZE	512

#include <thread>
#include <chrono>
#include <ws2tcpip.h> // ����2 Ȯ�� ���
#include <iostream>
#include <string>

using namespace std;

UDPSocket::UDPSocket(TCC& tcc)
{
	// ���� �ʱ�ȭ
	WSADATA wsa;
	while (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {};
	createSocket(tcc);
}

UDPSocket::~UDPSocket()
{
	// ���� �ݱ�
	closesocket(udpSocket);

	// ���� ����
	WSACleanup();
}

void UDPSocket::createSocket(TCC& tcc)
{
	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

	if (udpSocket == INVALID_SOCKET) err_quit("socket()");

	// SERVERIP�� SERVERPORT�� ���� �ּ� ����ü �ʱ�ȭ

	memset(&serveraddr, 0, sizeof(serveraddr));

	serveraddr.sin_family = AF_INET;

	// ���ڿ� ������ ���� �����Ǹ� ��ȯ�Ͽ� serveraddr.sin_addr�� ����
	inet_pton(AF_INET, tcc.getIp(), &serveraddr.sin_addr);
	serveraddr.sin_port = htons(tcc.getPort());

	sendData();

	thread t(&UDPSocket::receiveData, this);
	t.join();
}

void UDPSocket::sendData()
{
	char buf[BUFSIZE + 1] = "hello";

	int len2 = (int)strlen(buf);

	if (buf[len2 - 1] == '\n')
		buf[len2 - 1] = '\0';

	// ������ ������
	int retval = sendto(udpSocket, buf, (int)strlen(buf), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) {
		err_display("sendto()");
	}
	printf("[UDPSocket Ŭ���̾�Ʈ] %d����Ʈ�� ���½��ϴ�.\n", retval);
}

void UDPSocket::receiveData()
{
	struct sockaddr_in peeraddr;
	char buf[BUFSIZE + 1];

	while (1) {
		// ������ �ޱ�
		int addrlen = sizeof(peeraddr);

		string str;
		int retval = recvfrom(udpSocket, buf, BUFSIZE, 0, (struct sockaddr*)&peeraddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			err_display("recvfrom()");
			break;
		}

		// ���ŵ� serveraddr ���� inet_ntop() �� ���ڿ� ������ addr �� ������
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &peeraddr.sin_addr, addr, sizeof(addr));

		// ���ڿ� ������ �ּ� addr �� ���� ������ ���
		buf[retval] = '\0';

		str = buf;
		cout << str << endl;
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

void UDPSocket::err_quit(const char* msg)
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
void UDPSocket::err_display(const char* msg)
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
	TCC tcc = TCC("192.168.0.3", 5000);
	UDPSocket udp = UDPSocket(tcc);

}