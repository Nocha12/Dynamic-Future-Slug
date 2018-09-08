#pragma once
#include "Mover.h"

class CBullet : public CMover
{
public:
	float Angle;
	float AngleRate;
	float Speed;
	float SpeedRate;
	Math::Vector minPos;
	Math::Vector maxPos;

public:
	CBullet(float x, float y, float angle, float angleRate, float speed, float speedRate, BulletShape shapeType = Red, Math::Vector minPos = Math::Vector(-100, -1000), Math::Vector maxPos = Math::Vector(1300, 1040));
	~CBullet() { }

	virtual void Move();
	void OnCollision(GameObject *col);
};