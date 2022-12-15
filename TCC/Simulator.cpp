#include "Simulator.h"
#include <string>

using namespace std;

Simulator::Simulator()
{
	initPos = { 0,0 };
	curPos = { 0,0 };
}

const char* Simulator::getIp()
{
	return ip;
}

int Simulator::getPort()
{
	return port;
}


void Simulator::setInitPosition(Position pos)
{
	initPos = pos;
}

void Simulator::setCurPosition(Position pos)
{
	curPos = pos;
}

Position Simulator::getInitPosition()
{
	return initPos;
}

Position Simulator::getCurPosition()
{
	return curPos;
}

