#include "MineExplode.h"
#include "GameManager.h"
#include "MainScene.h"

CMineExplode::CMineExplode(Math::Vector pos) : deleteTimer(0)
{
	InitImage("resources/Boom/Explode.png");
	this->position = pos;

	tag = "EBullet";

	auto collider = AttachComponent<Components::BoxCollider>();
	collider->box.SetRect(
		Math::Vector(0.0f, 0.0f),
		Math::Vector((float)sprite->GetTexture()->GetWidth(), (float)sprite->GetTexture()->GetHeight())
	);
}

CMineExplode::~CMineExplode()
{
}

void CMineExplode::Move()
{
	if (deleteTimer >= 0.5)
		this->Destroy();
	deleteTimer+=deltaTime();
}

void CMineExplode::OnCollision(GameObject * col)
{
	if (col->tag.compare("Player") == 0)
	{
		if (GM->deathTimer >= 3)
		{
			GM->deathTimer = 0;
			if (GM->life == 0)
				RGApp->ChangeScene(new MainScene());
			--GM->life;
			col->SetEnabled(false);
			GM->isDeath = true;
		}
	}
}
