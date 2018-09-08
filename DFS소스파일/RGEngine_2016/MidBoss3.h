#pragma once
#include "Enemy.h"

class CMidBoss3 : public CEnemy
{
public:
	CMidBoss3();
	~CMidBoss3();

	float speed;

	void Move() override;
};

