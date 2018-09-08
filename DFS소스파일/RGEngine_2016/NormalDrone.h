#pragma once
#include "Enemy.h"

class CNormalDrone : public CEnemy
{
public:
	CNormalDrone();
	~CNormalDrone();

	bool isLeft;
	float speed;

	void Move() override;
};

