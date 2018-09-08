#pragma once
#include "Enemy.h"

class CTurret : public CEnemy
{
public:
	CTurret();
	~CTurret();

	float speed;

	void Move() override;
};

