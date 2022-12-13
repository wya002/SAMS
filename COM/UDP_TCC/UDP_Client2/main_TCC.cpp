
#define _CRT_SECURE_NO_WARNINGS // 구형 C 함수 사용 시 경고 끄기
#define _WINSOCK_DEPRECATED_NO_WARNINGS // 구형 소켓 API 사용 시 경고 끄기

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

#include <winsock2.h> // 윈속2 메인 헤더
#include <ws2tcpip.h> // 윈속2 확장 헤더

#include <tchar.h> // _T(), ...
#include <stdio.h> // printf(), ...
#include <stdlib.h> // exit(), ...

#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

#include "tinyxml.h"
#include <tuple>

using namespace std;
using namespace literals;

TiXmlDocument ReadDoc;

class ReadXML {
public:
	tuple<int, int, int, int, int, int> readXML() {
		// xml 파일 읽기
		TiXmlDocument ReadDoc;
		ReadDoc.LoadFile("C:/Users/User/Desktop/Test.xml");

		// 루트 가져오기
		TiXmlElement* ReadRoot = ReadDoc.FirstChildElement("DB");
		TiXmlElement* sub1 = ReadRoot->FirstChildElement("Synario")->FirstChildElement("SynarioStart");
		TiXmlElement* sub2 = ReadRoot->FirstChildElement("Synario")->FirstChildElement("SynarioDestination");
		TiXmlElement* sub3 = ReadRoot->FirstChildElement("Synario")->FirstChildElement("SynarioMSS");

		// 노드를 다루기 위한 핸들
		TiXmlHandle handle1(0);
		TiXmlHandle handle2(0);
		TiXmlHandle handle3(0);
		handle1 = TiXmlHandle(sub1);
		handle2 = TiXmlHandle(sub2);
		handle3 = TiXmlHandle(sub3);

		TiXmlAttribute* pAttrib1;
		TiXmlAttribute* pAttrib2;
		TiXmlAttribute* pAttrib3;
		pAttrib1 = sub1->FirstAttribute();
		pAttrib2 = sub2->FirstAttribute();
		pAttrib3 = sub3->FirstAttribute();

		// 초기위치 값 변수 할당
		pAttrib1 = pAttrib1->Next();
		int x1 = pAttrib1->IntValue();
		pAttrib1 = pAttrib1->Next();
		int y1 = pAttrib1->IntValue();

		// 목표위치 값 변수 할당
		pAttrib2 = pAttrib2->Next();
		int x2 = pAttrib2->IntValue();
		pAttrib2 = pAttrib2->Next();
		int y2 = pAttrib2->IntValue();

		// 목표위치 값 변수 할당
		pAttrib3 = pAttrib3->Next();
		int x3 = pAttrib3->IntValue();
		pAttrib3 = pAttrib3->Next();
		int y3 = pAttrib3->IntValue();

		return tuple<int, int, int, int, int, int>(x1, y1, x2, y2, x3, y3);
	}
};

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
class Error_code {
public:

};
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

//////// Server 1 IP 할당 ////////
char* SERVERIP1 = (char*)"127.0.0.1";
#define SERVERPORT1 9000

//////// Server 2 IP 할당 ////////
char* SERVERIP2 = (char*)"192.168.0.100";
#define SERVERPORT2 5000

#define BUFSIZE    512

int main(int argc, char* argv[])
{

	ReadXML readXML;

	tuple<int, int, int, int, int, int> result = readXML.readXML();
	int x1 = get<0>(result);
	int y1 = get<1>(result);
	int x2 = get<2>(result);
	int y2 = get<3>(result);
	int x3 = get<4>(result);
	int y3 = get<5>(result);


	// 명령행 인수가 있으면 IP 주소로 사용
	if (argc > 1) {
		SERVERIP1 = argv[1];
		SERVERIP2 = argv[1];
	}

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	//////// Server 1 IP 설정 ////////
	// 소켓 생성
	SOCKET sock1 = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock1 == INVALID_SOCKET) err_quit("socket()");
	// SERVERIP와 SERVERPORT로 소켓 주소 구조체 초기화
	struct sockaddr_in serveraddr1;
	memset(&serveraddr1, 0, sizeof(serveraddr1));
	serveraddr1.sin_family = AF_INET;
	// 문자열 형태의 서버 아이피를 변환하여 serveraddr.sin_addr에 넣음
	inet_pton(AF_INET, SERVERIP1, &serveraddr1.sin_addr);
	serveraddr1.sin_port = htons(SERVERPORT1);

	//////// Server 2 IP 설정 ////////
	// 소켓 생성
	SOCKET sock2 = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock2 == INVALID_SOCKET) err_quit("socket()");
	// SERVERIP와 SERVERPORT로 소켓 주소 구조체 초기화
	struct sockaddr_in serveraddr2;
	memset(&serveraddr2, 0, sizeof(serveraddr2));
	serveraddr2.sin_family = AF_INET;
	// 문자열 형태의 서버 아이피를 변환하여 serveraddr.sin_addr에 넣음
	inet_pton(AF_INET, SERVERIP2, &serveraddr2.sin_addr);
	serveraddr2.sin_port = htons(SERVERPORT2);

	// 데이터 통신에 사용할 변수
	struct sockaddr_in peeraddr;
	char buf1[BUFSIZE + 1];  // Server1에 데이터를 보내기 위한 buffer 설정
	char buf2[BUFSIZE + 1]; // Server2에 데이터를 보내기 위한 buffer 설정
	char buf3[BUFSIZE + 1]; // Server1에서 받은 데이터를 받기 위한 buffer 설정
	char buf4[BUFSIZE + 1]; // Server2에서 받은 데이터를 받기 위한 buffer 설정
	char buf5[BUFSIZE + 1]; // Server2에서 받은 데이터를 받기 위한 buffer 설정
	

	sprintf(buf1, "%s, %d, %d, %d, %d", "Scenario ATS Pos", x1, y1, x2, y2);
	sprintf(buf2, "%s, %d, %d", "Scenario MSS Pos", x3, y3);

	// 서버와 데이터 통신
	while (1) {

		//////////////// Server 1로 데이터 보내기 ////////////////
		//데이터 입력
		printf("\n[보낼 데이터] ");
		if (fgets(buf5, BUFSIZE + 1, stdin) == NULL)
			break;

		// '\n' 문자 제거
		int len1 = (int)strlen(buf1);
		if (buf1[len1 - 1] == '\n')
			buf1[len1 - 1] = '\0';

		// 프로그램 종료 조건
		if (strlen(buf1) == 0)
			break;

		// 데이터 보내기
		int retval1 = sendto(sock1, buf1, (int)strlen(buf1), 0, (struct sockaddr*)&serveraddr1, sizeof(serveraddr1));
		if (retval1 == SOCKET_ERROR) {
			err_display("sendto()");
			break;
		}
		printf("[UDP 클라이언트] %d바이트를 보냈습니다.\n", retval1);


		//////////////// Server 2로 데이터 보내기 ////////////////
		// '\n' 문자 제거
		int len2 = (int)strlen(buf2);
		if (buf2[len2 - 1] == '\n')
			buf2[len2 - 1] = '\0';

		// 데이터 보내기
		int retval2 = sendto(sock2, buf2, (int)strlen(buf2), 0, (struct sockaddr*)&serveraddr2, sizeof(serveraddr2));
		if (retval2 == SOCKET_ERROR) {
			err_display("sendto()");
			break;
		}
		printf("[UDP 클라이언트] %d바이트를 보냈습니다.\n", retval2);

		//////////////// Server 1에서 데이터 받기 ////////////////
		// 데이터 받기
		int addrlen = sizeof(peeraddr);

		string str;
		int retval3 = recvfrom(sock1, buf3, BUFSIZE, 0, (struct sockaddr*)&peeraddr, &addrlen);
		if (retval3 == SOCKET_ERROR) {
			err_display("recvfrom()");
			break;
		}

		// 수신된 serveraddr 값을 inet_ntop() 로 문자열 형태의 addr 로 변경함
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &peeraddr.sin_addr, addr, sizeof(addr));

		// 문자열 형태의 주소 addr 과 받은 데이터 출력
		buf3[retval3] = '\0';

		str = buf3;
		cout << str << endl;

		//////////////// Server 2에서 데이터 받기 ////////////////
		// 데이터 받기
		addrlen = sizeof(peeraddr);

		int retval4 = recvfrom(sock2, buf4, BUFSIZE, 0, (struct sockaddr*)&peeraddr, &addrlen);
		if (retval4 == SOCKET_ERROR) {
			err_display("recvfrom()");
			break;
		}

		// 수신된 serveraddr 값을 inet_ntop() 로 문자열 형태의 addr 로 변경함
		addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &peeraddr.sin_addr, addr, sizeof(addr));

		// 문자열 형태의 주소 addr 과 받은 데이터 출력
		buf4[retval4] = '\0';

		str = buf4;
		cout << str << endl;
	}

	// 소켓 닫기
	closesocket(sock1);
	closesocket(sock2);

	// 윈속 종료
	WSACleanup();

	return 0;
}