#include "Boss3.h"
#include "BossStage.h"

CBoss3::CBoss3() : isShotLaser(false), isWarning(false), howDroneSpawn(0), mineCount(0)
{
	maxHp = 1500;
	hp = 1500;
	patternCount = 0;
	phase = 0;
	maxPhase = 3;

	InitImage("resources/Boss/3StageMain.png");
	SetCollider();
}

CBoss3::~CBoss3()
{
}

void CBoss3::Move()
{
	CEnemy::Move();
	Math::Vector centerPos;
	centerPos.SetVector(position.x + (float)sprite->GetTexture()->GetWidth() / 2, position.y + (float)sprite->GetTexture()->GetHeight() / 2);

	if (phase == 0)
	{
		if (PatternTimer <= 1 && (howDroneSpawn == 0 || howDroneSpawn == 1))
		{
			RGApp->GetScene<BossStage>()->PushBackGameObject(Drone[howDroneSpawn] = new CDrone(false));
			Drone[howDroneSpawn++]->position.SetVector(1200, 700);
		}
		else if (PatternTimer <= 1 && howDroneSpawn == 2)
		{
			RGApp->GetScene<BossStage>()->PushBackGameObject(Drone[howDroneSpawn] = new CDrone(true));
			Drone[howDroneSpawn++]->position.SetVector(1200, 700);
		}
		if (PatternTimer <= 1 && PatternTimer > 0.01f)
		{
			if (!isWarning)
			{
				RGApp->GetScene<BossStage>()->PushBackGameObject(warning[1] = new Sprite("resources/Bullet/Warning.png"));
				warning[1]->position.SetVector(-1480 + centerPos.x, centerPos.y);
				isWarning = true;
			}
		}
		else if (PatternTimer <= 3.5f && PatternTimer > 2.5f)
		{
			if (!isShotLaser)
			{
				RGApp->GetScene<BossStage>()->PushBackGameObject(laser[1] = new CLaser());
				laser[1]->position.SetVector(warning[1]->position.x, warning[1]->position.y - 20);
				warning[1]->Destroy();
				isShotLaser = true;
				isWarning = false;
			}
		}
		else if (PatternTimer <= 5 && PatternTimer > 4.9f)
		{
			if (isShotLaser)
			{
				laser[1]->Destroy();
				isShotLaser = false;
			}
		}
		else if (MineTimer >= 0.4f && PatternTimer <= 6 && PatternTimer > 5)
		{
			if (!isWarning)
			{
				RGApp->GetScene<BossStage>()->PushBackGameObject(warning[1] = new Sprite("resources/Bullet/Warning.png"));
				warning[1]->position.SetVector(-1480 + centerPos.x, centerPos.y);
				isWarning = true;
			}

			MineTimer = 0;
			auto temp = new CMine();
			if (RGApp->GetScene<BossStage>()->GetPlayer())
			{
				if (mineCount == 0)
					temp->position.SetVector(RGApp->GetScene<BossStage>()->GetPlayer()->position.x + 50, 870);
				else if (mineCount == 1)
					temp->position.SetVector(RGApp->GetScene<BossStage>()->GetPlayer()->position.x + 50, 870);
				else
					temp->position.SetVector(RGApp->GetScene<BossStage>()->GetPlayer()->position.x + 50, 870);

				RGApp->GetScene<BossStage>()->PushBackGameObject(temp);
				mineList[mineCount++] = temp;
			}
		}
		else if (PatternTimer <= 7 && PatternTimer > 6)
			mineCount = 0;
		else if (MineTimer >= 0.4f && PatternTimer <= 8 && PatternTimer > 7)
		{
			if (!isShotLaser)
			{
				RGApp->GetScene<BossStage>()->PushBackGameObject(laser[1] = new CLaser());
				laser[1]->position.SetVector(warning[1]->position.x, warning[1]->position.y - 20);
				warning[1]->Destroy();
				isShotLaser = true;
				isWarning = false;
			}
			MineTimer = 0;
			CMine *mine = mineList[mineCount++];
			Math::Vector tempPos;
			tempPos.SetVector(mine->position.x, mine->position.y - 220);
			RGApp->GetScene<BossStage>()->PushBackGameObject(new CMineExplode(tempPos));
			mine->Destroy();
		}
		else if (MineTimer >= 0.4f && PatternTimer <= 9 && PatternTimer > 8)
		{
			if (isShotLaser)
			{
				laser[1]->Destroy();
				isShotLaser = false;
			}
		}
		if (PatternTimer > 9)
		{
			PatternTimer = 0;
		}
		if (hp < (maxHp / maxPhase) * (maxPhase - 1 - phase) && PatternTimer == 0)
			++phase;
	}
	else if (phase == 1)
	{
		if (PatternTimer <= 1 && PatternTimer > 0.02f)
		{
			if (!isWarning)
			{
				RGApp->GetScene<BossStage>()->PushBackGameObject(warning[0] = new Sprite("resources/Bullet/Warning.png"));
				warning[0]->position.SetVector(-1480 + centerPos.x, centerPos.y + 100);
				RGApp->GetScene<BossStage>()->PushBackGameObject(warning[2] = new Sprite("resources/Bullet/Warning.png"));
				warning[2]->position.SetVector(-1480 + centerPos.x, centerPos.y - 100);
				isWarning = true;
			}
		}
		else if (PatternTimer <= 3.5f && PatternTimer > 2.5f)
		{
			if (!isShotLaser)
			{
				RGApp->GetScene<BossStage>()->PushBackGameObject(laser[0] = new CLaser());
				laser[0]->position.SetVector(warning[0]->position.x, warning[0]->position.y - 20);
				warning[0]->Destroy();
				RGApp->GetScene<BossStage>()->PushBackGameObject(laser[2] = new CLaser());
				laser[2]->position.SetVector(warning[2]->position.x, warning[2]->position.y - 20);
				warning[2]->Destroy();

				isShotLaser = true;
				isWarning = false;
			}
		}
		else if (PatternTimer <= 5 && PatternTimer > 4.9f)
		{
			if (isShotLaser)
			{
				laser[0]->Destroy();
				laser[2]->Destroy();
				isShotLaser = false;
			}
		}
		else if (PatternTimer <= 6 && PatternTimer > 5)
		{
			if (!isWarning)
			{
				RGApp->GetScene<BossStage>()->PushBackGameObject(warning[0] = new Sprite("resources/Bullet/Warning.png"));
				warning[0]->position.SetVector(-1480 + centerPos.x, centerPos.y);
				RGApp->GetScene<BossStage>()->PushBackGameObject(warning[2] = new Sprite("resources/Bullet/Warning.png"));
				warning[2]->position.SetVector(-1480 + centerPos.x, centerPos.y - 100);
				isWarning = true;
			}
		}
		else if (PatternTimer <= 8.5f && PatternTimer > 7.5f)
		{
			if (!isShotLaser)
			{
				RGApp->GetScene<BossStage>()->PushBackGameObject(laser[0] = new CLaser());
				laser[0]->position.SetVector(warning[0]->position.x, warning[0]->position.y - 20);
				warning[0]->Destroy();
				RGApp->GetScene<BossStage>()->PushBackGameObject(laser[2] = new CLaser());
				laser[2]->position.SetVector(warning[2]->position.x, warning[2]->position.y - 20);
				warning[2]->Destroy();

				isShotLaser = true;
				isWarning = false;
			}
		}
		else if (PatternTimer <= 10 && PatternTimer > 9.9f)
		{
			if (isShotLaser)
			{
				laser[0]->Destroy();
				laser[2]->Destroy();
				isShotLaser = false;
			}
		}
		else if (PatternTimer <= 11 && PatternTimer > 10)
		{
			if (!isWarning)
			{
				RGApp->GetScene<BossStage>()->PushBackGameObject(warning[0] = new Sprite("resources/Bullet/Warning.png"));
				warning[0]->position.SetVector(-1480 + centerPos.x, centerPos.y);
				RGApp->GetScene<BossStage>()->PushBackGameObject(warning[2] = new Sprite("resources/Bullet/Warning.png"));
				warning[2]->position.SetVector(-1480 + centerPos.x, centerPos.y + 100);
				isWarning = true;
			}
		}
		else if (PatternTimer <= 13.5f && PatternTimer > 12.5f)
		{
			if (!isShotLaser)
			{
				RGApp->GetScene<BossStage>()->PushBackGameObject(laser[0] = new CLaser());
				laser[0]->position.SetVector(warning[0]->position.x, warning[0]->position.y - 20);
				warning[0]->Destroy();
				RGApp->GetScene<BossStage>()->PushBackGameObject(laser[2] = new CLaser());
				laser[2]->position.SetVector(warning[2]->position.x, warning[2]->position.y - 20);
				warning[2]->Destroy();

				isShotLaser = true;
				isWarning = false;
			}
		}
		else if (PatternTimer <= 16 && PatternTimer > 15.9f)
		{
			if (isShotLaser)
			{
				laser[0]->Destroy();
				laser[2]->Destroy();
				isShotLaser = false;
			}
		}
		if (PatternTimer > 16)
		{
			PatternTimer = 0;
		}
		if (hp < (maxHp / maxPhase) * (maxPhase - 1 - phase) && PatternTimer == 0)
			++phase;
	}
	else if (phase == 2)
	{
		if (ShootTimer >= 0.2f && PatternTimer <= 1 && PatternTimer > 0.001f)
		{
			if (!isWarning)
			{
				RGApp->GetScene<BossStage>()->PushBackGameObject(warning[1] = new Sprite("resources/Bullet/Warning.png"));
				warning[1]->position.SetVector(-1480 + centerPos.x, centerPos.y);
				isWarning = true;
			}
			ShootTimer = 0;
			ShootNWay(centerPos.x, centerPos.y, 1, 0.1f, 0.03f, 5, 0, 0, Math::Vector(600, -1000), Math::Vector(1300, 1040));
		}
		else if (PatternTimer <= 3.5f && PatternTimer > 2.5f)
		{
			if (!isShotLaser)
			{
				RGApp->GetScene<BossStage>()->PushBackGameObject(laser[1] = new CLaser());
				laser[1]->position.SetVector(warning[1]->position.x, warning[1]->position.y - 20);
				warning[1]->Destroy();
				isShotLaser = true;
				isWarning = false;
			}
		}
		else if (PatternTimer <= 5 && PatternTimer > 4.9f)
		{
			if (isShotLaser)
			{
				laser[1]->Destroy();
				isShotLaser = false;
			}
		}
		if (MineTimer >= 0.4f && PatternTimer <= 6 && PatternTimer > 5)
		{
			MineTimer = 0;
			auto temp = new CMine();
			if (RGApp->GetScene<BossStage>()->GetPlayer())
			{
				if (!isWarning)
				{
					RGApp->GetScene<BossStage>()->PushBackGameObject(warning[0] = new Sprite("resources/Bullet/Warning.png"));
					warning[0]->position.SetVector(-1480 + centerPos.x, centerPos.y + 100);
					RGApp->GetScene<BossStage>()->PushBackGameObject(warning[2] = new Sprite("resources/Bullet/Warning.png"));
					warning[2]->position.SetVector(-1480 + centerPos.x, centerPos.y - 100);
					isWarning = true;
				}
				if (mineCount == 0)
					temp->position.SetVector(RGApp->GetScene<BossStage>()->GetPlayer()->position.x - 10, 840);
				else if (mineCount == 1)
					temp->position.SetVector(RGApp->GetScene<BossStage>()->GetPlayer()->position.x - 10, 840);
				else
					temp->position.SetVector(RGApp->GetScene<BossStage>()->GetPlayer()->position.x - 10, 840);

				RGApp->GetScene<BossStage>()->PushBackGameObject(temp);
				mineList[mineCount++] = temp;
			}
		}
		if (PatternTimer <= 7 && PatternTimer > 6.5f)
			mineCount = 0;
		if (MineTimer >= 0.4f && PatternTimer <= 8 && PatternTimer > 7)
		{
			if (!isShotLaser)
			{
				RGApp->GetScene<BossStage>()->PushBackGameObject(laser[0] = new CLaser());
				laser[0]->position.SetVector(warning[0]->position.x, warning[0]->position.y - 20);
				warning[0]->Destroy();
				RGApp->GetScene<BossStage>()->PushBackGameObject(laser[2] = new CLaser());
				laser[2]->position.SetVector(warning[2]->position.x, warning[2]->position.y - 20);
				warning[2]->Destroy();

				isShotLaser = true;
				isWarning = false;
			}
			MineTimer = 0;
			CMine *mine = mineList[mineCount++];
			Math::Vector tempPos;
			tempPos.SetVector(mine->position.x, mine->position.y - 300);
			RGApp->GetScene<BossStage>()->PushBackGameObject(new CMineExplode(tempPos));
			mine->Destroy();
		}
		else if (PatternTimer <= 10 && PatternTimer > 9.9f)
		{
			if (isShotLaser)
			{
				laser[0]->Destroy();
				laser[2]->Destroy();
				isShotLaser = false;
			}
		}
		if (PatternTimer > 10)
		{
			PatternTimer = 0;
			mineCount = 0;
		}
	}
	PatternTimer += deltaTime();
	MineTimer += deltaTime();
	ShootTimer += deltaTime();
}
