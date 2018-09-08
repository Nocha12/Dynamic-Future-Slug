#include "Boss2.h"
#include "BossStage.h"

CBoss2::CBoss2() : howDroneSpawn(0), isChainSpawn(false), isChainGo(true), chainSpeed(0), speed(0), isLeft(true)
{
	MineTimer = 1;
	patternCount = 0;
	phase = 0;
	maxPhase = 3;
	hp = 1000;
	maxHp = 1000;

	ShootTimer = 10;
	PatternTimer = 0;
	InitImage("resources/Boss/2StageMain.png");
	SetCollider();
}

CBoss2::~CBoss2()
{
}

void CBoss2::Move()
{
	CEnemy::Move();
	Math::Vector centerPos;
	int minX = 55, maxX = 930;

	centerPos.SetVector(position.x + (float)sprite->GetTexture()->GetWidth() / 2, position.y + (float)sprite->GetTexture()->GetHeight() / 2);
	int baseSpeed = 10;
	if (phase == 0)
	{
		if (PatternTimer <= 1 && howDroneSpawn == 0)
		{
			RGApp->GetScene<BossStage>()->PushBackGameObject(Drone[howDroneSpawn] = new CDrone(true));
			Drone[howDroneSpawn]->position.x = 1200;
			Drone[howDroneSpawn++]->position.y = 700;
		}
		else if (PatternTimer <= 4.1f && PatternTimer >= 4 && howDroneSpawn == 1)
		{
			RGApp->GetScene<BossStage>()->PushBackGameObject(Drone[howDroneSpawn] = new CDrone(false));
			Drone[howDroneSpawn]->position.x = 1200;
			Drone[howDroneSpawn++]->position.y = 700;
		}

		if (PatternTimer >= 1 && PatternTimer <= 1.9f && ShootTimer >= 0.2f)
		{
			ShootTimer = 0;
			MakeBullet(centerPos.x, centerPos.y, 0, 0, 0.03f, 0);
		}
		if (PatternTimer >= 4.5f)
			PatternTimer = 0;
		if (hp < (maxHp / maxPhase) * (maxPhase - 1 - phase) && PatternTimer == 0)
			++phase;
	}
	if (phase == 1)
	{
		if (PatternTimer >= 0.01f && PatternTimer <= 0.1f && !isChainSpawn)
		{
			RGApp->GetScene<BossStage>()->PushBackGameObject(chain = new CChain());
			chain->position.SetVector(centerPos.x, centerPos.y + 50);
			PatternTimer = 1;
			isChainSpawn = true;
		}
		if (isChainSpawn && isChainGo)
		{
			if (chain->position.x <= 10)
			{
				isChainGo = false;
				chainSpeed = 0;
			}
			chain->position.x -= chainSpeed;
			chainSpeed += deltaTime() * 10;
		}
		else if (isChainSpawn && !isChainGo)
		{
			if (chain->position.x >= 1400)
			{
				chain->Destroy();
				isChainSpawn = false;
				chainSpeed = 0;
			}
			else
			{
				chain->position.x += chainSpeed;
				chainSpeed += deltaTime() * 10;
			}
		}

		if (ShootTimer >= 0.1f && PatternTimer <= 2 && PatternTimer > 1)
		{
			ShootTimer = 0;
			MakeBullet(centerPos.x + 100, centerPos.y, 0.25, 0, 0.03f, 0.0005f);
		}
		else if (ShootTimer >= 0.3f && PatternTimer <= 7 && PatternTimer > 2)
		{
			ShootTimer = 0;
			MakeBullet(Math::Random(50, 1000), -50, 0.75, 0, 0.005f, 0.0005f);
		}
		if (position.x >= minX && PatternTimer >= 7 && isLeft)
		{
			position.x += speed;
			speed -= deltaTime() * baseSpeed;
		}
		if (position.x <= minX && PatternTimer >= 7 && isLeft)
		{
			speed = 0;
			isLeft = false;
		}
		if (!isLeft && position.x <= maxX && PatternTimer >= 7)
		{
			position.x += speed;
			speed += deltaTime() * baseSpeed;
		}
		if (!isLeft && position.x >= maxX)
		{
			PatternTimer = 0;
			isLeft = true;
			isChainGo = true;
			speed = 0;
		}
		if (hp < (maxHp / maxPhase) * (maxPhase - 1 - phase) && PatternTimer == 0)
			++phase;
	}
	if (phase == 2)
	{
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
		if (PatternTimer <= 4 && PatternTimer >= 3 && ShootTimer >= 0.2f)
		{
			ShootTimer = 0;
			MakeBullet(centerPos.x, centerPos.y, 0, 0, 0.03f, 0);
		}
		if (PatternTimer > 4)
		{
			PatternTimer = 0;
			mineCount = 0;
		}
	}

	ShootTimer += deltaTime();
	if (!isChainSpawn)
		PatternTimer += deltaTime();
	MineTimer += deltaTime();
}
