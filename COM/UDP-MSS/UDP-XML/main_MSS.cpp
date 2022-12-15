
#define _CRT_SECURE_NO_WARNINGS // 구형 C 함수 사용 시 경고 끄기
#define _WINSOCK_DEPRECATED_NO_WARNINGS // 구형 소켓 API 사용 시 경고 끄기

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

#include <winsock2.h> // 윈속2 메인 헤더
#include <ws2tcpip.h> // 윈속2 확장 헤더

#include <tchar.h> // _T(), ...
#include <stdio.h> // printf(), ...
#include <stdlib.h> // exit(), ...

#include "tinyxml.h"
#include <sstream>

#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

// 소켓 함수 오류 출력 후 종료
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

// 소켓 함수 오류 출력
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

// 소켓 함수 오류 출력
void err_display(int errcode)
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

// 서버의 포트번호. 클라이언트는 여기로 접속하면 됩니다.
#define SERVERPORT 9000
#define BUFSIZE    512

void rcv(SOCKET& sock)
{
	// 데이터를 수신하였을 때, 해당 클라이언트의 정보가 여기 저장됨
	sockaddr_in clientaddr;
	char buf[BUFSIZE + 1];
	char buf2[BUFSIZE + 1];

	int x = 30;
	int y = 40;
	sprintf(buf2, "%s, %d, %d","Current MSS Pos", x, y);

	// 클라이언트와 데이터 통신
	while (1) {
		// 데이터 받기
		int addrlen = sizeof(clientaddr);
		int retval = recvfrom(sock, buf, BUFSIZE, 0, (struct sockaddr*)&clientaddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			err_display("recvfrom()");
			break;
		}

		// 수신된 clientaddr 값을 inet_ntop() 로 문자열 형태의 addr 로 변경함
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

		// 문자열 형태의 주소 addr 과 받은 데이터 출력
		buf[retval] = '\0';
		printf("[UDP/%s:%d] %s\n", addr, ntohs(clientaddr.sin_port), buf);

		// '\n' 문자 제거
		int len = (int)strlen(buf2);
		if (buf2[len - 1] == '\n')
			buf2[len - 1] = '\0';

		// 데이터 보내기
		int retval2 = sendto(sock, buf2, (int)strlen(buf2), 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
		if (retval2 == SOCKET_ERROR) {
			err_display("sendto()");
			break;
		}

	}
	std::cout << "thread 종료" << std::endl;
}

int main(int argc, char* argv[])
{
	// 시작 시간 측정
	auto start = std::chrono::steady_clock::now();

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
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


	// 수신 스레드 예제
	std::thread rcv_thread(rcv, std::ref(sock));

	// 초기화 종료 시간 측정
	auto end = std::chrono::steady_clock::now();

	// 걸린 시간을 ms 단위로 출력
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Elapsed time in milliseconds: " << ms.count() << " ms" << std::endl;

	// 걸린 시간을 sec 단위로 출력
	std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cout << "Elapsed time in seconds: " << sec.count() << " sec" << std::endl;

	// 원하는 동작 수행 가능

	while (1) {
		std::string s;
		std::cin >> s;
		if (s == "q")
			break;

		// 입력 받은거 출력
		std::cout << s << std::endl;
	}

	// 소켓 닫기
	// 다른 thread 에서 이 sock 으로 send/recv 중이면 중지됨
	closesocket(sock);

	// rcv_thread 종료시까지 대기
	rcv_thread.join();


	// 윈속 종료
	WSACleanup();
	return 0;
}
