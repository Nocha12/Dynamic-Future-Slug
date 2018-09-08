#pragma once
#include "Enemy.h"

class CNormal : public CEnemy
{
public:
	CNormal();
	~CNormal();

	float speed;
	bool isMoving;

	void Move();
};

