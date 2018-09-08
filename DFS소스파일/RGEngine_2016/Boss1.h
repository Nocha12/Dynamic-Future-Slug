#pragma once
#include "Enemy.h"
#include "Mine.h"
#include "MineExplode.h"

class CBoss1 : public CEnemy
{
public:
	CBoss1();
	~CBoss1();

	int mineCount;
	CMine* mineList[3];

	virtual void Move() override;
};

