#include "Normal.h"
#include "ZakoStage.h"

CNormal::CNormal() : speed(3), isMoving(true)
{
	ShootTimer = 0;
	hp = 15;
	InitImage("resources/Zako/Normal.png");
	SetCollider();
}

CNormal::~CNormal()
{
}

void CNormal::Move()
{
	CEnemy::Move();

	if (isMoving && position.x > RGApp->GetScene<ZakoStage>()->GetPlayer()->position.x)
	{
		position.Transform(-speed, 0);
		speed += deltaTime() * 2.5f;
	}
	else
		isMoving = false;
}