#pragma once
#include "AirThreat.h"

class Launcher
{
public:
	void launch();
private:
	AirThreat airThreat;
	int oder = 0;	// �߻� ��� 1 �ƴϸ� 0
};