#include "Turret.h"
#include "TestScene.h"
#include "ZakoStage.h"

CTurret::CTurret() : speed(3)
{
	ShootTimer = 0;
	hp = 25;
	InitImage("resources/Zako/NormalRang.png");
	auto collider = AttachComponent<Components::BoxCollider>();
	collider->box.SetRect(
		Math::Vector(0.0f, 0.0f),
		Math::Vector((float)sprite->GetTexture()->GetWidth(), (float)sprite->GetTexture()->GetHeight())
	);
}

CTurret::~CTurret()
{
}

void CTurret::Move()
{
	CEnemy::Move();

	Math::Vector centerPos;
	centerPos.SetVector(position.x + (float)sprite->GetTexture()->GetWidth() / 2, position.y + (float)sprite->GetTexture()->GetHeight() / 2);

	if (position.x > RGApp->GetScene<ZakoStage>()->GetPlayer()->position.x + 300)
		position.Transform(-speed, 0);

	if (ShootTimer >= 0.8f)
	{
		ShootTimer = 0;
		MakeBullet(centerPos.x, centerPos.y, 0, 0, 0.02f, 0);
	}
	ShootTimer += deltaTime();
}