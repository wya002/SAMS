
#define _CRT_SECURE_NO_WARNINGS // ���� C �Լ� ��� �� ��� ����
#define _WINSOCK_DEPRECATED_NO_WARNINGS // ���� ���� API ��� �� ��� ����

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

#include <winsock2.h> // ����2 ���� ���
#include <ws2tcpip.h> // ����2 Ȯ�� ���

#include <tchar.h> // _T(), ...
#include <stdio.h> // printf(), ...
#include <stdlib.h> // exit(), ...

#pragma comment(lib, "ws2_32") // ws2_32.lib ��ũ

#include "tinyxml.h"
#include <tuple>

using namespace std;
using namespace literals;

TiXmlDocument ReadDoc;

class ReadXML {
public:
	tuple<int, int, int, int, int, int> readXML() {
		// xml ���� �б�
		TiXmlDocument ReadDoc;
		ReadDoc.LoadFile("C:/Users/User/Desktop/Test.xml");

		// ��Ʈ ��������
		TiXmlElement* ReadRoot = ReadDoc.FirstChildElement("DB");
		TiXmlElement* sub1 = ReadRoot->FirstChildElement("Synario")->FirstChildElement("SynarioStart");
		TiXmlElement* sub2 = ReadRoot->FirstChildElement("Synario")->FirstChildElement("SynarioDestination");
		TiXmlElement* sub3 = ReadRoot->FirstChildElement("Synario")->FirstChildElement("SynarioMSS");

		// ��带 �ٷ�� ���� �ڵ�
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

		// �ʱ���ġ �� ���� �Ҵ�
		pAttrib1 = pAttrib1->Next();
		int x1 = pAttrib1->IntValue();
		pAttrib1 = pAttrib1->Next();
		int y1 = pAttrib1->IntValue();

		// ��ǥ��ġ �� ���� �Ҵ�
		pAttrib2 = pAttrib2->Next();
		int x2 = pAttrib2->IntValue();
		pAttrib2 = pAttrib2->Next();
		int y2 = pAttrib2->IntValue();

		// ��ǥ��ġ �� ���� �Ҵ�
		pAttrib3 = pAttrib3->Next();
		int x3 = pAttrib3->IntValue();
		pAttrib3 = pAttrib3->Next();
		int y3 = pAttrib3->IntValue();

		return tuple<int, int, int, int, int, int>(x1, y1, x2, y2, x3, y3);
	}
};

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
class Error_code {
public:

};
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

//////// Server 1 IP �Ҵ� ////////
char* SERVERIP1 = (char*)"127.0.0.1";
#define SERVERPORT1 9000

//////// Server 2 IP �Ҵ� ////////
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


	// ����� �μ��� ������ IP �ּҷ� ���
	if (argc > 1) {
		SERVERIP1 = argv[1];
		SERVERIP2 = argv[1];
	}

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	//////// Server 1 IP ���� ////////
	// ���� ����
	SOCKET sock1 = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock1 == INVALID_SOCKET) err_quit("socket()");
	// SERVERIP�� SERVERPORT�� ���� �ּ� ����ü �ʱ�ȭ
	struct sockaddr_in serveraddr1;
	memset(&serveraddr1, 0, sizeof(serveraddr1));
	serveraddr1.sin_family = AF_INET;
	// ���ڿ� ������ ���� �����Ǹ� ��ȯ�Ͽ� serveraddr.sin_addr�� ����
	inet_pton(AF_INET, SERVERIP1, &serveraddr1.sin_addr);
	serveraddr1.sin_port = htons(SERVERPORT1);

	//////// Server 2 IP ���� ////////
	// ���� ����
	SOCKET sock2 = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock2 == INVALID_SOCKET) err_quit("socket()");
	// SERVERIP�� SERVERPORT�� ���� �ּ� ����ü �ʱ�ȭ
	struct sockaddr_in serveraddr2;
	memset(&serveraddr2, 0, sizeof(serveraddr2));
	serveraddr2.sin_family = AF_INET;
	// ���ڿ� ������ ���� �����Ǹ� ��ȯ�Ͽ� serveraddr.sin_addr�� ����
	inet_pton(AF_INET, SERVERIP2, &serveraddr2.sin_addr);
	serveraddr2.sin_port = htons(SERVERPORT2);

	// ������ ��ſ� ����� ����
	struct sockaddr_in peeraddr;
	char buf1[BUFSIZE + 1];  // Server1�� �����͸� ������ ���� buffer ����
	char buf2[BUFSIZE + 1]; // Server2�� �����͸� ������ ���� buffer ����
	char buf3[BUFSIZE + 1]; // Server1���� ���� �����͸� �ޱ� ���� buffer ����
	char buf4[BUFSIZE + 1]; // Server2���� ���� �����͸� �ޱ� ���� buffer ����
	char buf5[BUFSIZE + 1]; // Server2���� ���� �����͸� �ޱ� ���� buffer ����
	

	sprintf(buf1, "%s, %d, %d, %d, %d", "Scenario ATS Pos", x1, y1, x2, y2);
	sprintf(buf2, "%s, %d, %d", "Scenario MSS Pos", x3, y3);

	// ������ ������ ���
	while (1) {

		//////////////// Server 1�� ������ ������ ////////////////
		//������ �Է�
		printf("\n[���� ������] ");
		if (fgets(buf5, BUFSIZE + 1, stdin) == NULL)
			break;

		// '\n' ���� ����
		int len1 = (int)strlen(buf1);
		if (buf1[len1 - 1] == '\n')
			buf1[len1 - 1] = '\0';

		// ���α׷� ���� ����
		if (strlen(buf1) == 0)
			break;

		// ������ ������
		int retval1 = sendto(sock1, buf1, (int)strlen(buf1), 0, (struct sockaddr*)&serveraddr1, sizeof(serveraddr1));
		if (retval1 == SOCKET_ERROR) {
			err_display("sendto()");
			break;
		}
		printf("[UDP Ŭ���̾�Ʈ] %d����Ʈ�� ���½��ϴ�.\n", retval1);


		//////////////// Server 2�� ������ ������ ////////////////
		// '\n' ���� ����
		int len2 = (int)strlen(buf2);
		if (buf2[len2 - 1] == '\n')
			buf2[len2 - 1] = '\0';

		// ������ ������
		int retval2 = sendto(sock2, buf2, (int)strlen(buf2), 0, (struct sockaddr*)&serveraddr2, sizeof(serveraddr2));
		if (retval2 == SOCKET_ERROR) {
			err_display("sendto()");
			break;
		}
		printf("[UDP Ŭ���̾�Ʈ] %d����Ʈ�� ���½��ϴ�.\n", retval2);

		//////////////// Server 1���� ������ �ޱ� ////////////////
		// ������ �ޱ�
		int addrlen = sizeof(peeraddr);

		string str;
		int retval3 = recvfrom(sock1, buf3, BUFSIZE, 0, (struct sockaddr*)&peeraddr, &addrlen);
		if (retval3 == SOCKET_ERROR) {
			err_display("recvfrom()");
			break;
		}

		// ���ŵ� serveraddr ���� inet_ntop() �� ���ڿ� ������ addr �� ������
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &peeraddr.sin_addr, addr, sizeof(addr));

		// ���ڿ� ������ �ּ� addr �� ���� ������ ���
		buf3[retval3] = '\0';

		str = buf3;
		cout << str << endl;

		//////////////// Server 2���� ������ �ޱ� ////////////////
		// ������ �ޱ�
		addrlen = sizeof(peeraddr);

		int retval4 = recvfrom(sock2, buf4, BUFSIZE, 0, (struct sockaddr*)&peeraddr, &addrlen);
		if (retval4 == SOCKET_ERROR) {
			err_display("recvfrom()");
			break;
		}

		// ���ŵ� serveraddr ���� inet_ntop() �� ���ڿ� ������ addr �� ������
		addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &peeraddr.sin_addr, addr, sizeof(addr));

		// ���ڿ� ������ �ּ� addr �� ���� ������ ���
		buf4[retval4] = '\0';

		str = buf4;
		cout << str << endl;
	}

	// ���� �ݱ�
	closesocket(sock1);
	closesocket(sock2);

	// ���� ����
	WSACleanup();

	return 0;
}