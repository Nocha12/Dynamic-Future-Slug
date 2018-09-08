#pragma once
#include "Mine.h"

class CMineExplode : public CMine
{
public:
	CMineExplode(Math::Vector pos);
	~CMineExplode();

	float deleteTimer;

	void Move() override;
	void OnCollision(GameObject *col);
};

