#include "NormalDrone.h"

CNormalDrone::CNormalDrone() : isLeft(true), speed(5)
{
	hp = 25;
	ShootTimer = 0;
	InitImage("resources/Zako/Drone.png");
	SetCollider();
}

CNormalDrone::~CNormalDrone()
{
}

void CNormalDrone::Move()
{
	CEnemy::Move();

	Math::Vector centerPos;
	centerPos.SetVector(position.x + (float)sprite->GetTexture()->GetWidth() / 2, position.y + (float)sprite->GetTexture()->GetHeight() / 2);

	if (isLeft)
	{
		position.Transform(speed, 0);
		if (position.x >= 1100)
			isLeft = false;
		if (ShootTimer >= 1.6f)
		{
			ShootTimer = 0;
			MakeBullet(centerPos.x, centerPos.y, 0.6f, 0, 0.02f, 0);
		}
	}
	else
	{
		position.Transform(-speed, 0);
		if (position.x <= 80)
			isLeft = true;
		if (ShootTimer >= 1.6f)
		{
			ShootTimer = 0;
			MakeBullet(centerPos.x, centerPos.y, -0.1f, 0, 0.02f, 0);
		}
	}

	ShootTimer += deltaTime();
}

