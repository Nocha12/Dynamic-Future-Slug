#pragma once
#include "Enemy.h"
class CDrone : public CEnemy
{
public:
	CDrone(bool isAiming);
	~CDrone();

	Math::Vector goalPos;
	float speed;
	float howMoved;
	bool isAiming;
	bool isMoving;
	bool isFirst;
	float moveTimer;
	float moveInterval;

	void Move() override;
};

