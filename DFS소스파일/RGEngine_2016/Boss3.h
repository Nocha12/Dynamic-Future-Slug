#pragma once
#include "Enemy.h"
#include "Mine.h"
#include "Drone.h"
#include "Laser.h"
#include "Sprite.h"
#include "MineExplode.h"

class CBoss3 : public CEnemy
{
public:
	CBoss3();
	~CBoss3();

	Sprite *warning[3];
	CLaser *laser[3];
	bool isWarning;
	bool isShotLaser;

	int mineCount;
	CMine* mineList[3];

	CDrone *Drone[3];
	int howDroneSpawn;

	void Move() override;
};

