#include "MidBoss2.h"
#include "MidBossStage.h"

CMidBoss2::CMidBoss2() : isWarning(false), isShotLaser(false), isReset(false), shotTimer2(0)
{
	maxHp = 1000;
	hp = 1000;
	patternCount = 0;
	phase = 0;
	maxPhase = 2;

	InitImage("resources/Boss/2StageMid.png");
	SetCollider();
}

CMidBoss2::~CMidBoss2()
{

}

void CMidBoss2::Move()
{
	CEnemy::Move();
	Math::Vector centerPos;
	centerPos.SetVector(position.x + (float)sprite->GetTexture()->GetWidth() / 2, position.y + (float)sprite->GetTexture()->GetHeight() / 2);

	if (phase == 0)
	{
		if (PatternTimer <= 1)
		{
			if (!isWarning)
			{
				RGApp->GetScene<MidBossStage>()->PushBackGameObject(warning = new Sprite("resources/Bullet/Warning.png"));
				warning->position.SetVector(-1380 + centerPos.x, centerPos.y);
				isWarning = true;
			}
		}
		else if (PatternTimer <= 5 && PatternTimer > 2)
		{
			if (!isShotLaser)
			{
				RGApp->GetScene<MidBossStage>()->PushBackGameObject(laser = new CLaser());
				laser->position.SetVector(warning->position.x, warning->position.y - 20);
				warning->Destroy();
				isShotLaser = true;
			}
		}
		else if (PatternTimer <= 6 && PatternTimer > 5)
		{
			if (!isReset)
			{
				isShotLaser = false;
				isWarning = false;
				isReset = true;
			}
			if (!isWarning)
			{
				laser->Destroy();
				RGApp->GetScene<MidBossStage>()->PushBackGameObject(warning = new Sprite("resources/Bullet/Warning.png"));
				warning->position.SetVector(-1380 + centerPos.x, centerPos.y - 80);
				isWarning = true;
			}
		}
		else if (PatternTimer <= 9 && PatternTimer > 6)
		{
			if (!isShotLaser)
			{
				RGApp->GetScene<MidBossStage>()->PushBackGameObject(laser = new CLaser());
				laser->position.SetVector(warning->position.x, warning->position.y - 20);
				warning->Destroy();
				isShotLaser = true;
			}
		}
		else if (PatternTimer > 9)
		{
			laser->Destroy();
			PatternTimer = 0;
			isShotLaser = false;
			isWarning = false;
			isReset = false;
		}
		if (hp < (maxHp / maxPhase) * (maxPhase - 1 - phase) && PatternTimer == 0)
			++phase;
	}
	else if (phase == 1)
	{
		if (shotTimer2 >= 0.3f && PatternTimer <= 1 && PatternTimer > 0)
		{
			shotTimer2 = 0;
			MakeBullet(centerPos.x, centerPos.y, 0, 0, 0.03f, 0);
		}
		if (ShootTimer >= 0.1f && PatternTimer <= 1 && PatternTimer > 0)
		{
			ShootTimer = 0;
			MakeBullet(centerPos.x + 100, centerPos.y, 0.25, 0, 0.03f, 0.0005f);
		}
		else if (ShootTimer >= 0.3f && PatternTimer <= 8 && PatternTimer > 1)
		{
			ShootTimer = 0;
			MakeBullet(Math::Random(50, 1000), -50, 0.75, 0, 0.005f, 0.0005f);
		}
		if (PatternTimer > 8)
			PatternTimer = 0;
	}
	shotTimer2 += deltaTime();
	ShootTimer += deltaTime();
	PatternTimer += deltaTime();
}