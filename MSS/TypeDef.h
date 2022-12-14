#pragma once

struct Position
{
	double x;
	double y;
};

struct Velocity
{
	double velX;
	double velY;
};

enum class TCCstate
{
	IDLE, STBY, OPERATION, PAUSE, END
};

enum class MissileEvent
{
	InterceptSuccess, InterceptFail
};

enum class MissileState			// STOP : �̻��� ����, CHASE : �̻��� �⵿ ��
{
	STOP, CHASE
};

enum class LauncherState		// STOP : ź��  ����, LAUNCH : ź�� ����
{
	STOP, LAUNCH
};
