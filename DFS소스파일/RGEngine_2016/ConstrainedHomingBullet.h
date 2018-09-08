#pragma once
#include "Bullet.h"

class CConstrainedHomingBullet : public CBullet
{
public:
	//최대 선회 각속도
	float MaxAngleRate;
	
public:
	CConstrainedHomingBullet(BulletShape shapeType, float x,float y,float angle, float speed, float maxAngleRate);
	~CConstrainedHomingBullet();
	void Move();
	float GetMyShipAngle(float x, float y);
};

