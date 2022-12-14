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

enum class MissileState			// STOP : 미사일 정지, CHASE : 미사일 기동 중
{
	STOP, CHASE
};

enum class LauncherState		// STOP : 탄이  있음, LAUNCH : 탄이 없음
{
	STOP, LAUNCH
};
