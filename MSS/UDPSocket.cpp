#include "UDPSocket.h"

using namespace std;


UDPSocket::UDPSocket(TCC& tcc, Missile& ms) : missile(ms)
{
    // 윈속 초기화
    WSADATA wsa;
    while (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {};
    tccReceived = false;
    createSocket(tcc);
}

UDPSocket::~UDPSocket()
{
    // 소켓 닫기
    closesocket(udpSocket);

    // 윈속 종료
    WSACleanup();
}

void UDPSocket::createSocket(TCC& tcc)
{
    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (udpSocket == INVALID_SOCKET) err_quit("socket()");

    // SERVERIP와 SERVERPORT로 소켓 주소 구조체 초기화

    memset(&serveraddr, 0, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;

    // 문자열 형태의 서버 아이피를 변환하여 serveraddr.sin_addr에 넣음
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

    // 데이터 보내기
    int retval = sendto(udpSocket, buf, (int)strlen(buf), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR) {
        err_display("sendto()");
    }
    printf("[UDPSocket 클라이언트] %d바이트를 보냈습니다.\n", retval);

    this_thread::sleep_for(1000ms);

    struct sockaddr_in peeraddr;

    if (!tccReceived)
    {

        char receiveBuf[BUFSIZE + 1];
        // 데이터 받기
        int addrlen = sizeof(peeraddr);

        string str;
        int retval = recvfrom(udpSocket, receiveBuf, BUFSIZE, 0, (struct sockaddr*)&peeraddr, &addrlen);
        if (retval == SOCKET_ERROR) {
            err_display("recvfrom()");
        }

        // 수신된 serveraddr 값을 inet_ntop() 로 문자열 형태의 addr 로 변경함
        char addr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &peeraddr.sin_addr, addr, sizeof(addr));

        // 문자열 형태의 주소 addr 과 받은 데이터 출력
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

        if (missile.getMsgQueue().size() > 0) {
            cout << "\nSend Message : ";
            strcpy_s(buf, missile.getMsgQueue().front().c_str());
            cout << buf << endl;
            missile.getMsgQueue().pop();

            int len2 = (int)strlen(buf);

            if (buf[len2 - 1] == '\n')
                buf[len2 - 1] = '\0';

            // 데이터 보내기
            int retval = sendto(udpSocket, buf, (int)strlen(buf), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
            if (retval == SOCKET_ERROR) {
                err_display("sendto()");
            }
            printf("[UDPSocket 클라이언트] %d바이트를 보냈습니다.\n", retval);

        }
    }
}

void UDPSocket::receiveData()
{
    struct sockaddr_in peeraddr;
    char buf[BUFSIZE + 1];

    while (1) {
        cout << "데이터 받는 중" << endl;
        // 데이터 받기
        int addrlen = sizeof(peeraddr);

        string in_str;
        int retval = recvfrom(udpSocket, buf, BUFSIZE, 0, (struct sockaddr*)&peeraddr, &addrlen);
        if (retval == SOCKET_ERROR) {
            err_display("recvfrom()");
            break;
        }

        // 수신된 serveraddr 값을 inet_ntop() 로 문자열 형태의 addr 로 변경함
        char addr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &peeraddr.sin_addr, addr, sizeof(addr));

        // 문자열 형태의 주소 addr 과 받은 데이터 출력
        buf[retval] = '\0';

        in_str = buf;

        //if (in_str.find("MI"))
        //{
        //    McurPos.x = stod(in_str.substr(2));
        //    McurPos.y = stod(in_str.substr(2));
        //}

        cout << in_str << endl;

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

// 소켓 함수 오류 출력
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
Position UDPSocket::getMinitPos()
{
    return MinitPos;
}
Position UDPSocket::getMcurPos()
{
    return McurPos;
}