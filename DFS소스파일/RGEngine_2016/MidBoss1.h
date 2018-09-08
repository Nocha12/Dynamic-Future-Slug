#pragma once
#include "Enemy.h"

class CMidBoss1 : public CEnemy
{
public:
	CMidBoss1();
	~CMidBoss1();

	float speed;
	bool isTurn;

	void Move() override;
};

