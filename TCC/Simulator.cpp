#include "Simulator.h"
#include <string>

using namespace std;

Simulator::Simulator()
{
	ip = "127.0.0.0";
	port = "8080";
	initPos = { 0,0 };
	curPos = { 0,0 };
}

string Simulator::getIp()
{
	return ip;
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

