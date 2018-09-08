#pragma once
#include "Mover.h"
#include "Bullet.h"

class CEnemy : public CMover
{
public:
	CEnemy();
	~CEnemy();

	std::list<CBullet> bulletList;
	float ShootTimer;
	float PatternTimer;
	float MineTimer;

	int maxHp;
	int phase;
	int maxPhase;
	int patternCount;

	//------------
	bool isOnGround;
	float gravity, weight;

	bool isOnBoard;
	float boardLeft, boardRight, boardTop;
	//-----------


	void MakeBullet(float x, float y, float angle, float angleRate, float speed, float speedRate);
	void MakeBullet(float x, float y, float angle, float angleRate, float speed, float speedRate, Math::Vector minPos, Math::Vector maxPos);
	
	void CEnemy::ShootNWay(float x, float y, float angle, float angleRange, float speed, int count, float angleRate, float speedRate)
	{
		if (count > 1)
			for (int i = 0; i < count; i++)
				MakeBullet(x, y, angle + angleRange*((float)i / (count - 1) - 0.5f), angleRate, speed, speedRate);
		else if (count == 1)
			MakeBullet(x, y, angle, angleRate, speed, speedRate);
	}
	void CEnemy::ShootNWay(float x, float y, float angle, float angleRange, float speed, int count, float angleRate, float speedRate, Math::Vector minPos, Math::Vector maxPos)
	{
		if (count > 1)
			for (int i = 0; i < count; i++)
				MakeBullet(x, y, angle + angleRange*((float)i / (count - 1) - 0.5f), angleRate, speed, speedRate, minPos, maxPos);
		else if (count == 1)
			MakeBullet(x, y, angle, angleRate, speed, speedRate);
	}

	void Move();
	void SetCollider();
	void OnCollision(GameObject *col);

	Math::Vector lerp(Math::Vector p1, Math::Vector p2, float d1) {
		return Math::Vector((1 - d1) * p1.x + d1 * p2.x, (1 - d1) * p1.y + d1 * p2.y);
	}
	void Boom(float time, int count, int repeat);
};