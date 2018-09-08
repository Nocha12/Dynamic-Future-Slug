#include "MidBoss1.h"

CMidBoss1::CMidBoss1() : speed(0), isTurn(false)
{
	maxHp = 500;
	hp = 500;
	InitImage("resources/Boss/1StageMid.png");
	patternCount = 0;
	phase = 0;
	maxPhase = 2;

	SetCollider();
}

CMidBoss1::~CMidBoss1()
{
}

void CMidBoss1::Move()
{
	CEnemy::Move();

	int minX = 25, maxX = 1055;
	bool isMoving = false;
	int baseSpeed = 5;
	float shotDelay = 0.2f;
	Math::Vector centerPos;

	centerPos.SetVector(position.x + (float)sprite->GetTexture()->GetWidth() / 2, position.y + (float)sprite->GetTexture()->GetHeight() / 2);

	if (phase == 0)
	{
		if (patternCount == 0)
		{
			if (position.x > minX)
			{
				position.x += speed;
				speed -= deltaTime() * baseSpeed;
				isMoving = true;
			}
			else if (ShootTimer >= shotDelay && PatternTimer <= 1 && PatternTimer > 0)
			{
				if (!isTurn)
				{
					scale.x *= -1;
					isTurn = true;
				}
				ShootTimer = 0;
				MakeBullet(centerPos.x, centerPos.y, 0.5f, 0, 0.03f, 0);
			}
			else if (PatternTimer > 1)
			{
				speed = 0;
				++patternCount;
			}
		}
		else if (patternCount == 1)
		{
			if (position.x < maxX)
			{
				position.x += speed;
				speed += deltaTime() * baseSpeed;
				isMoving = true;
			}
			else if (ShootTimer >= shotDelay && PatternTimer <= 2 && PatternTimer > 1)
			{
				if (isTurn)
				{
					scale.x *= -1;
					isTurn = false;
				}
				ShootTimer = 0;
				MakeBullet(centerPos.x, centerPos.y, 1, 0, 0.03f, 0);
			}
			else if (PatternTimer > 2)
			{
				speed = 0;
				patternCount = 0;
				PatternTimer = 0;
			}
			if (hp <= maxHp / maxPhase && patternCount == 0)
				phase++;
		}
	}
	else if (phase == 1)
	{
		if (patternCount == 0)
		{
			if (position.x > minX)
			{
				position.x += speed;
				speed -= deltaTime() * baseSpeed;
				isMoving = true;
			}
			else if (ShootTimer >= shotDelay && PatternTimer <= 1 && PatternTimer > 0)
			{
				if (!isTurn)
				{
					scale.x *= -1;
					isTurn = true;
				}
				ShootTimer = 0;
				ShootNWay(centerPos.x, centerPos.y, 0.5f, 0.1f, 0.03f, 5, 0, 0, Math::Vector(-100, -1000), Math::Vector(600, 1040));
			}
			else if (PatternTimer > 1)
			{
				speed = 0;
				++patternCount;
			}
		}
		else if (patternCount == 1)
		{
			if (position.x < maxX)
			{
				position.x += speed;
				speed += deltaTime() * baseSpeed;
				isMoving = true;
			}
			else if (ShootTimer >= shotDelay && PatternTimer <= 2 && PatternTimer > 1)
			{
				if (isTurn)
				{
					scale.x *= -1;
					isTurn = false;
				}
				ShootTimer = 0;
				ShootNWay(centerPos.x, centerPos.y, 1, 0.1f, 0.03f, 5, 0, 0, Math::Vector(700, -1000), Math::Vector(1300, 1040));
			}
			else if (PatternTimer > 2)
			{
				speed = 0;
				patternCount = 0;
				PatternTimer = 0;
			}
		}
	}

	if (!isMoving)
		PatternTimer += deltaTime();
	ShootTimer += deltaTime();
}