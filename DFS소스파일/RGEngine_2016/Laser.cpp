#include "Laser.h"
#include "GameManager.h"
#include "MainScene.h"

CLaser::CLaser()
{
	laserImg = AttachComponent<Components::SpriteRenderer>();
	laserImg->SetTexture("resources/Bullet/Laser.png");
	auto colliderr = AttachComponent<Components::BoxCollider>();
	colliderr->box.SetRect(0.0f, 0.0f, (float)laserImg->GetTexture()->GetWidth(), (float)laserImg->GetTexture()->GetHeight());
	this->tag = "EBullet";
}

CLaser::~CLaser()
{
}

void CLaser::OnUpdate()
{
	if (times >= 0.75f)
		Destroy();
	times += deltaTime();
}

void CLaser::OnCollision(GameObject *col)
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