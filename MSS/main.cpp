#include "UDPSocket.h"
#include <string>
#include <iostream>

int main()
{
    Position testpos = { 1.13, 2.31 };
    const char* testevent = "START";

    TCC tcc = TCC("192.168.0.100", 5000);
    UDPSocket udp = UDPSocket(tcc);

    udp.sendPos(testpos);
    udp.sendEvent(testevent);

    std::string str = "START";
    std::cout << str.substr(2);

}

