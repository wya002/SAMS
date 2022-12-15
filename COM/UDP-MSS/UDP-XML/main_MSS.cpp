
#define _CRT_SECURE_NO_WARNINGS // ���� C �Լ� ��� �� ��� ����
#define _WINSOCK_DEPRECATED_NO_WARNINGS // ���� ���� API ��� �� ��� ����

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

#include <winsock2.h> // ����2 ���� ���
#include <ws2tcpip.h> // ����2 Ȯ�� ���

#include <tchar.h> // _T(), ...
#include <stdio.h> // printf(), ...
#include <stdlib.h> // exit(), ...

#include "tinyxml.h"
#include <sstream>

#pragma comment(lib, "ws2_32") // ws2_32.lib ��ũ

// ���� �Լ� ���� ��� �� ����
void err_quit(const char* msg)
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
void err_display(const char* msg)
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

// ���� �Լ� ���� ���
void err_display(int errcode)
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

// ������ ��Ʈ��ȣ. Ŭ���̾�Ʈ�� ����� �����ϸ� �˴ϴ�.
#define SERVERPORT 9000
#define BUFSIZE    512

void rcv(SOCKET& sock)
{
	// �����͸� �����Ͽ��� ��, �ش� Ŭ���̾�Ʈ�� ������ ���� �����
	sockaddr_in clientaddr;
	char buf[BUFSIZE + 1];
	char buf2[BUFSIZE + 1];

	int x = 30;
	int y = 40;
	sprintf(buf2, "%s, %d, %d","Current MSS Pos", x, y);

	// Ŭ���̾�Ʈ�� ������ ���
	while (1) {
		// ������ �ޱ�
		int addrlen = sizeof(clientaddr);
		int retval = recvfrom(sock, buf, BUFSIZE, 0, (struct sockaddr*)&clientaddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			err_display("recvfrom()");
			break;
		}

		// ���ŵ� clientaddr ���� inet_ntop() �� ���ڿ� ������ addr �� ������
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

		// ���ڿ� ������ �ּ� addr �� ���� ������ ���
		buf[retval] = '\0';
		printf("[UDP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port), buf);

		// '\n' ���� ����
		int len = (int)strlen(buf2);
		if (buf2[len - 1] == '\n')
			buf2[len - 1] = '\0';

		// ������ ������
		int retval2 = sendto(sock, buf2, (int)strlen(buf2), 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
		if (retval2 == SOCKET_ERROR) {
			err_display("sendto()");
			break;
		}

	}
	std::cout << "thread ����" << std::endl;
}

int main(int argc, char* argv[])
{
	// ���� �ð� ����
	auto start = std::chrono::steady_clock::now();

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	int retval = bind(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");


	// ���� ������ ����
	std::thread rcv_thread(rcv, std::ref(sock));

	// �ʱ�ȭ ���� �ð� ����
	auto end = std::chrono::steady_clock::now();

	// �ɸ� �ð��� ms ������ ���
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Elapsed time in milliseconds: " << ms.count() << " ms" << std::endl;

	// �ɸ� �ð��� sec ������ ���
	std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cout << "Elapsed time in seconds: " << sec.count() << " sec" << std::endl;

	// ���ϴ� ���� ���� ����

	while (1) {
		std::string s;
		std::cin >> s;
		if (s == "q")
			break;

		// �Է� ������ ���
		std::cout << s << std::endl;
	}

	// ���� �ݱ�
	// �ٸ� thread ���� �� sock ���� send/recv ���̸� ������
	closesocket(sock);

	// rcv_thread ����ñ��� ���
	rcv_thread.join();


	// ���� ����
	WSACleanup();
	return 0;
}
