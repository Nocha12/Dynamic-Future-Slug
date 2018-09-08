#pragma once
#include "Enemy.h"
#include "Drone.h"
#include "Chain.h"
#include "Mine.h"
#include "MineExplode.h"

class CBoss2 : public CEnemy
{
public:
	CBoss2();
	~CBoss2();

	CChain *chain;
	float chainSpeed;
	bool isChainGo;

	CDrone *Drone[2];
	int howDroneSpawn;
	bool isChainSpawn;
	bool isLeft;
	float speed;

	int mineCount;
	CMine* mineList[3];

	void Move() override;
};

