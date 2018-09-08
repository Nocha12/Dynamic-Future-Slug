#include "Chain.h"
#include "GameManager.h"
#include "MainScene.h"

CChain::CChain()
{
	chainImg = AttachComponent<Components::SpriteRenderer>();
	chainImg->SetTexture("resources/Bullet/Chain.png");
	auto collider = AttachComponent<Components::BoxCollider>();
	collider->box.SetRect(0.0f, 0.0f, (float)chainImg->GetTexture()->GetWidth(), (float)chainImg->GetTexture()->GetHeight());
	this->tag = "EBullet";
}

CChain::~CChain()
{
}

void CChain::OnCollision(GameObject * col)
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

