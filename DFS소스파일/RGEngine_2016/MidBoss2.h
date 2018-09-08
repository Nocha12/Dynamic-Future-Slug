#pragma once
#include "Enemy.h"
#include "Laser.h"
#include "Sprite.h"

class CMidBoss2 : public CEnemy
{
public:
	Sprite *warning;
	CLaser *laser;

	bool isWarning;
	bool isShotLaser;
	bool isReset;
	float shotTimer2;

	CMidBoss2();
	~CMidBoss2();

	void Move() override;
};

