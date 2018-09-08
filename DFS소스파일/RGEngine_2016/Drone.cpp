#include "Drone.h"
#include "TestScene.h"
#include "BossStage.h"
#include "MidBossStage.h"

CDrone::CDrone(bool isAiming) : isAiming(isAiming), isMoving(false), howMoved(0), moveTimer(0), moveInterval(1), isFirst(true)
{
	goalPos = Math::Vector(1150, 100);
	InitImage("resources/Zako/BossDrone.png");
}

CDrone::~CDrone()
{

}

void CDrone::Move()
{
	float speed = 0.005f;
	Math::Vector centerPos;
	centerPos.SetVector(position.x + (float)sprite->GetTexture()->GetWidth() / 2, position.y + (float)sprite->GetTexture()->GetHeight() / 2);

	if (howMoved <= 1)
		position = lerp(position, goalPos, howMoved += speed);
	else
	{
		moveTimer += deltaTime();

		if (ShootTimer >= 0.4f && !isFirst)
		{
			ShootTimer = 0;
			MakeBullet(centerPos.x, centerPos.y, 0.75, 0, 0.02f, 0);
		}

		if (moveTimer >= moveInterval)
		{
			moveTimer = 0;

			if (isAiming)
			{
				if (RGApp->GetScene()->scenetype == "MidBoss")
				{
					goalPos = Math::Vector(RGApp->GetScene<MidBossStage>()->GetPlayer()->position.x + (RGApp->GetScene<MidBossStage>()->GetPlayer()->animation->GetTexture(0)->GetWidth() / 2), position.y);
				}
				else if (RGApp->GetScene()->scenetype == "Boss")
				{
					goalPos = Math::Vector(RGApp->GetScene<BossStage>()->GetPlayer()->position.x + (RGApp->GetScene<BossStage>()->GetPlayer()->animation->GetTexture(0)->GetWidth() / 2), position.y);
				}
			}
			else
				goalPos = Math::Vector(Math::Random(100, 900), position.y);

			howMoved = 0;
			isFirst = false;
		}
	}
	ShootTimer += deltaTime();
}