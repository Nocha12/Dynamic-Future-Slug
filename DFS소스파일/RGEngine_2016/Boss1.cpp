#include "Boss1.h"
#include "BossStage.h"

CBoss1::CBoss1() : mineCount(0)
{
	MineTimer = 1;
	patternCount = 0;
	phase = 0;
	maxPhase = 3;
	hp = 800;
	maxHp = 800;
	InitImage("resources/Boss/1StageMain.png");
	SetCollider();
}

CBoss1::~CBoss1()
{
}

void CBoss1::Move()
{
	CEnemy::Move();

	Math::Vector centerPos;
	centerPos.SetVector(position.x + (float)sprite->GetTexture()->GetWidth() / 2, position.y + (float)sprite->GetTexture()->GetHeight() / 2);

	if (phase == 0)
	{
		if (ShootTimer >= 0.2f && PatternTimer <= 1.1f)
		{
			ShootTimer = 0;
			ShootNWay(centerPos.x, centerPos.y, 0.01f, 0.1f, 0.03f, 2, 0, 0);
		}
		else if (ShootTimer >= 0.2f && PatternTimer <= 3 && PatternTimer > 2)
		{
			ShootTimer = 0;
			MakeBullet(centerPos.x, centerPos.y, 0, 0, 0.03f, 0);
		}
		else if (ShootTimer >= 0.2f && PatternTimer <= 5 && PatternTimer > 4)
		{
			ShootTimer = 0;
			ShootNWay(centerPos.x, centerPos.y, 0.01f, 0.1f, 0.03f, 2, 0, 0);
		}
		else if (PatternTimer <= 6 && PatternTimer > 5)
			mineCount = 0;
		else if (ShootTimer >= 0.2f && PatternTimer <= 7 && PatternTimer > 6)
		{
			ShootTimer = 0;
			MakeBullet(centerPos.x, centerPos.y, 0, 0, 0.03f, 0);
		}
		//Áö·Ú
		if (MineTimer >= 0.4f && PatternTimer <= 5 && PatternTimer >= 4)
		{
			MineTimer = 0;
			auto temp = new CMine();
			if (mineCount == 0)
				temp->position.SetVector(850, 870);
			else if (mineCount == 1)
				temp->position.SetVector(700, 870);
			else
				temp->position.SetVector(550, 870);
			RGApp->GetScene<BossStage>()->PushBackGameObject(temp);
			mineList[mineCount++] = temp;
		}
		//Áö·Ú Á¦°Å
		if (MineTimer >= 0.4f && PatternTimer <= 7 && PatternTimer >= 6)
		{
			MineTimer = 0;
			CMine *mine = mineList[mineCount++];
			Math::Vector tempPos;
			tempPos.SetVector(mine->position.x, mine->position.y - 220);
			RGApp->GetScene<BossStage>()->PushBackGameObject(new CMineExplode(tempPos));
			mine->Destroy();
		}
		if (PatternTimer > 8)
		{
			PatternTimer = 0;
			mineCount = 0;
		}
		if (hp < (maxHp / maxPhase) * (maxPhase - 1 - phase) && PatternTimer == 0)
			++phase;
	}
	else if (phase == 1)
	{
		if (ShootTimer >= 0.1f && PatternTimer <= 1 && PatternTimer > 0 && PatternTimer == 0)
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
		{
			PatternTimer = 0;
			mineCount = 0;
			MineTimer = 1;
		}
		if (hp < (maxHp / maxPhase) * (maxPhase - 1 - phase) && PatternTimer == 0)
			++phase;
	}
	else if (phase == 2)
	{
		if (ShootTimer >= 0.2f && PatternTimer <= 1.1f && PatternTimer > 0)
		{
			ShootTimer = 0;
			ShootNWay(centerPos.x, centerPos.y, 0.05f, 0.1f, 0.03f, 2, 0, 0);
		}
		else if (ShootTimer >= 0.2f && PatternTimer <= 3 && PatternTimer > 2)
		{
			ShootTimer = 0;
			ShootNWay(centerPos.x, centerPos.y, -0.05f, 0.1f, 0.03f, 2, 0, 0);
		}
		else if (ShootTimer >= 0.2f && PatternTimer <= 5 && PatternTimer > 4)
		{
			ShootTimer = 0;
			ShootNWay(centerPos.x, centerPos.y, 1, 0.1f, 0.03f, 5, 0, 0, Math::Vector(700, -1000), Math::Vector(1300, 1040));
		}
		if (PatternTimer > 6)
		{
			PatternTimer = 0;
			mineCount = 0;
		}
		if (MineTimer >= 0.4f && PatternTimer <= 1 && PatternTimer >= 0)
		{
			MineTimer = 0;
			auto temp = new CMine();
			if (RGApp->GetScene<BossStage>()->GetPlayer())
			{
				if (mineCount == 0)
					temp->position.SetVector(RGApp->GetScene<BossStage>()->GetPlayer()->position.x + 100, 870);
				else if (mineCount == 1)
					temp->position.SetVector(RGApp->GetScene<BossStage>()->GetPlayer()->position.x + 100, 870);
				else
					temp->position.SetVector(RGApp->GetScene<BossStage>()->GetPlayer()->position.x + 100, 870);

				RGApp->GetScene<BossStage>()->PushBackGameObject(temp);
				mineList[mineCount++] = temp;
			}
		}
		if (PatternTimer <= 2 && PatternTimer > 1.5f)
			mineCount = 0;
		if (MineTimer >= 0.4f && PatternTimer <= 3 && PatternTimer >= 2)
		{
			MineTimer = 0;
			CMine *mine = mineList[mineCount++];
			Math::Vector tempPos;
			tempPos.SetVector(mine->position.x, mine->position.y - 220);
			RGApp->GetScene<BossStage>()->PushBackGameObject(new CMineExplode(tempPos));
			mine->Destroy();
		}
	}
	PatternTimer += deltaTime();
	ShootTimer += deltaTime();
	MineTimer += deltaTime();
}
