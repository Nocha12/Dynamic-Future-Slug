#pragma once
#include "Mover.h"

#define GROUND CGround::GetInstance()

class CGround :	public CMover
{
public:
	CGround();
	~CGround();

	static CGround *GetInstance();

	void Move();
};

