#pragma once
#include "Mover.h"

class CGrenade : public CMover
{
private:
	float gravity, throwSpeed, throwPower, weight;
	float times;

public:
	CGrenade();
	~CGrenade();

	void OnEnabled(void);
	void Move();
};

