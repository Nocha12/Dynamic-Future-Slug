#include "MidBoss3.h"
#include "MidBossStage.h"

CMidBoss3::CMidBoss3() : speed(1)
{
	maxHp = 300;
	hp = 300;

	InitImage("resources/Boss/3StageMid.png");
	SetCollider();
}

CMidBoss3::~CMidBoss3()
{
}

void CMidBoss3::Move()
{
	CEnemy::Move();
	position.x -= speed;
	speed += deltaTime() * 1;
}
