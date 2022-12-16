#include "UDPSocket.h"
#include "Launcher.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>
#include <ctime>

using namespace std;

int main()
{
    // �޽��� ������ �� ��� Position���� �ٲ��� ���ΰ�? �� �߰�
    // �޽��� ������ �� ��� ���¸� �ٲ��� ���ΰ�?

    Launcher launcher;
    Missile& missile = launcher.getMissileinfo();
    ATS ats;

    TCC tcc = TCC("192.168.0.200", 5000);
	UDPSocket udp = UDPSocket(tcc, missile);

    // missile.getMsgQueue().push("hello");

	thread t([&]() { udp.sendData(); });
	thread t2([&]() { udp.receiveData(); });

    t.join();
    t2.join();

    Position mssInitPos;
    Position receivedatsPos;
    Position result;

    TCCstate tccstate;

    return 0;
}



