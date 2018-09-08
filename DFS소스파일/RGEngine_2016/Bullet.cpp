#include "Bullet.h"
#include "BulletManager.h"
#include "SpawnManager.h"
#include "GameManager.h"
#include "MainScene.h"
CBullet::CBullet(float x, float y, float angle, float angleRate, float speed, float speedRate, BulletShape bulletShape, Math::Vector minPos, Math::Vector maxPos) : Angle(angle), AngleRate(angleRate), Speed(speed), SpeedRate(speedRate), maxPos(maxPos), minPos(minPos)
{
	position.SetVector(x, y);
	tag = "Bullet";
	if(bulletShape == Red)
		InitImage("resources/Bullet/Bullet.png");
	else if(bulletShape == Blue)
		InitImage("resources/Bullet/EnemyBullet.png");
		
	auto collider = AttachComponent<Components::BoxCollider>();
	collider->box.SetRect(
		Math::Vector(0.0f, 0.0f),
		Math::Vector((float)sprite->GetTexture()->GetWidth(), (float)sprite->GetTexture()->GetHeight())
	);
}

void CBullet::Move()
{
	float rad = Angle * D3DX_PI * 2;
	
	this->position.x -= (Speed * cosf(rad) * deltaTime() * 50) * 512;
	this->position.y -= (Speed * sinf(rad) * deltaTime() * 50) * 512;

	Angle += AngleRate;
	Speed += SpeedRate;

	if (position.x <= minPos.x || position.x >= maxPos.x || position.y <= minPos.y || position.y >= maxPos.y)
	{
		BM->bulletList.remove(this);
		this->Destroy();
	}
}

void CBullet::OnCollision(GameObject *col)
{
	if (tag.compare("EBullet") == 0 && col->tag.compare("Player") == 0)
	{
		if (GM->deathTimer >= 3)
		{
			GM->deathTimer = 0;
			if (GM->life == 0)
				RGApp->ChangeScene(new MainScene());
			--GM->life;
			BM->bulletList.remove(this);
			this->Destroy();
			col->SetEnabled(false);
			GM->isDeath = true;
		}
	}
	else if (tag.compare("PBullet") == 0 && col->tag.compare("Enemy") == 0) {
		col->hp -= 10;
		BM->bulletList.remove(this);
		this->Destroy();
	}
}