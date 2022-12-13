#pragma once
#include "IMode.h"

class M_IDLE : public IMode
{
public :
	static M_IDLE& getInstance();
	virtual void deploy();
	virtual void start();
	virtual void pause();
	virtual void restart();
	virtual void done();

	//������, ���������, �Ҹ��� ȣ�� ���� (Singleton)
	M_IDLE(const M_IDLE& ref) = delete;
	M_IDLE& operator=(const M_IDLE& ref) = delete;

private :
	M_IDLE() {};
	~M_IDLE() {};
};

