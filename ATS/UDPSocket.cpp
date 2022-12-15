#include "UDPSocket.h"
#include <thread>
#include <chrono>
#include <cassert>

#define	BUFSIZE	512

using namespace std;

UDPSocket::UDPSocket(TCC& tcc, AirThreat& at) : airThreat(at)
{
	// ���� �ʱ�ȭ
	WSADATA wsa;
	while (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {};
	tccReceived = false;
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

	while (!tccReceived) { sendForConnecting(); }

}

void UDPSocket::sendForConnecting()
{
	char buf[BUFSIZE + 1];
	sprintf(buf, "MSS_CONNECTED");

	int len2 = (int)strlen(buf);

	if (buf[len2 - 1] == '\n')
		buf[len2 - 1] = '\0';

	// ������ ������
	int retval = sendto(udpSocket, buf, (int)strlen(buf), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) {
		err_display("sendto()");
	}
	printf("[UDPSocket Ŭ���̾�Ʈ] %d����Ʈ�� ���½��ϴ�.\n", retval);

	this_thread::sleep_for(1000ms);
	
	struct sockaddr_in peeraddr;

	if (!tccReceived)
	{

		char receiveBuf[BUFSIZE + 1];
		// ������ �ޱ�
		int addrlen = sizeof(peeraddr);

		string str;
		int retval = recvfrom(udpSocket, receiveBuf, BUFSIZE, 0, (struct sockaddr*)&peeraddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			err_display("recvfrom()");
		}

		// ���ŵ� serveraddr ���� inet_ntop() �� ���ڿ� ������ addr �� ������
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &peeraddr.sin_addr, addr, sizeof(addr));

		// ���ڿ� ������ �ּ� addr �� ���� ������ ���
		receiveBuf[retval] = '\0';

		str = receiveBuf;
		cout << "First Receive : ";
		cout << str << endl;

		tccReceived = true;
	}
}

void UDPSocket::sendData()
{
	while (1) {
		char buf[BUFSIZE + 1];

		if (airThreat.getMsgQueue().size() > 0) {
			cout << "\nSend Message : ";
			strcpy_s(buf, airThreat.getMsgQueue().front().c_str());
			cout << buf << endl;
			airThreat.getMsgQueue().pop();

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
	}
}

void UDPSocket::receiveData()
{
	struct sockaddr_in peeraddr;

	while (1) {

		char buf[BUFSIZE + 1];
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

		if (str.find("AI:") != string::npos)
		{
			cout << "�ʱ���ġ����" << endl;
		}
		else if (str.find("AS:START") != string::npos)
		{
			airThreat.setState(State::START);
		}
		else if (str.find("AS:PAUSE") != string::npos)
		{
			airThreat.setState(State::PAUSE);
		}
		else if (str.find("AS:DONE") != string::npos)
		{
			airThreat.setState(State::DONE);
		}

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

void UDPSocket::setATSCurPos(Position atsCurPos)
{
	udpCurPos = atsCurPos;
}

void UDPSocket::getATSState(string atsStatus)
{
	atsState = atsStatus;
}