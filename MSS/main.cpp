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
    // 메시지 들어왔을 때 어떻게 Position으로 바꿔줄 것인가? 를 추가
    // 메시지 들어왔을 때 어떻게 상태를 바꿔줄 것인가?

    Launcher launcher;
    Missile& missile = launcher.getMissileinfo();
    ATS ats;

    TCC tcc = TCC("127.0.0.1", 9000);
	UDPSocket udp = UDPSocket(tcc, missile, launcher, ats);

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



