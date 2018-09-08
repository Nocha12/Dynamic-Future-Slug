#include "Enemy.h"
#include "BulletManager.h"
#include "SpawnManager.h"
#include "GameManager.h"
#include "Ground.h"
#include "ZakoStage.h"
#include "MidBossStage.h"
#include "BossStage.h"
#include "Emitter.h"

CEnemy::CEnemy() : ShootTimer(0), PatternTimer(0), MineTimer(0),
				   isOnGround(true), gravity(0.f), weight(30.f),
				   isOnBoard(false), boardLeft(0.0f), boardRight(0.0f), boardTop(0.0f)
{
	tag = "Enemy";
}

CEnemy::~CEnemy()
{
}

void CEnemy::MakeBullet(float x, float y, float angle, float angleRate, float speed, float speedRate)
{
	auto temp = new CBullet(x, y, angle, angleRate, speed, speedRate, Blue);
	temp->tag = "EBullet";
	if(RGApp->GetScene()->scenetype == "Zako")
		RGApp->GetScene<ZakoStage>()->PushBackGameObject(temp);
	else if (RGApp->GetScene()->scenetype == "MidBoss")
		RGApp->GetScene<MidBossStage>()->PushBackGameObject(temp);
	else if (RGApp->GetScene()->scenetype == "Boss")
		RGApp->GetScene<BossStage>()->PushBackGameObject(temp);
	BM->bulletList.push_back(temp);
}

void CEnemy::MakeBullet(float x, float y, float angle, float angleRate, float speed, float speedRate, Math::Vector minPos, Math::Vector maxPos)
{
	auto temp = new CBullet(x, y, angle, angleRate, speed, speedRate, Blue, minPos, maxPos);
	temp->tag = "EBullet";
	if (RGApp->GetScene()->scenetype == "Zako")
		RGApp->GetScene<ZakoStage>()->PushBackGameObject(temp);
	else if (RGApp->GetScene()->scenetype == "MidBoss")
		RGApp->GetScene<MidBossStage>()->PushBackGameObject(temp);
	else if (RGApp->GetScene()->scenetype == "Boss")
		RGApp->GetScene<BossStage>()->PushBackGameObject(temp);
	BM->bulletList.push_back(temp);
}

void CEnemy::Move()
{
	if (hp <= 0)
	{
		if(GM->isBoss)
			Boom(0.1f, 7, 5);
		else 
			Boom(10, 5, 1);
		SpawnMgr->deleteEnemy(this);
	}

	if (!isOnBoard)
	{
		if (!isOnGround)
		{
			gravity += ((CGameManager::g + weight) * deltaTime());

			if ((position.y + animation->GetTexture(0)->GetHeight() + gravity) >= GROUND->position.y)
			{
				position.SetVector(position.x, GROUND->position.y - animation->GetTexture(0)->GetHeight());

				isOnGround = true;
				gravity = 0.0f;
			}
			else
				position.Transform(0.0f, gravity);
		}
	}
	else {

		if ((this->position.x + this->animation->GetTexture(0)->GetWidth()) <= boardLeft
			|| this->position.x >= boardRight
			|| this->position.y < boardTop)
		{
			isOnBoard = false;
		}

	}
	// Gravity

	//("%f, %f, %f, %f\n", this->position.x + this->animation->GetTexture(0)->GetWidth(), boardLeft, this->position.x, boardRight);
}

void CEnemy::OnCollision(GameObject *col)
{
	//if(col->tag.compare("Pbullet") == 0)

	if (col->tag.compare("Board") == 0)
	{
		if (!isOnGround)
		{
			if (this->position.y + this->animation->GetTexture(0)->GetHeight() > col->position.y
				&& this->position.y + this->animation->GetTexture(0)->GetHeight() < col->position.y + col->GetComponent<Components::SpriteRenderer>()->GetTexture()->GetHeight()
				&& this->position.x + this->animation->GetTexture(0)->GetWidth() > col->position.x
				&& this->position.x < col->position.x + col->GetComponent<Components::SpriteRenderer>()->GetTexture()->GetWidth())
			{
				//printf("Overlap!");

				gravity = 0.0f;

				this->position.y = col->position.y - this->animation->GetTexture(0)->GetHeight();

				boardLeft = col->position.x;
				boardRight = col->position.x + col->GetComponent<Components::SpriteRenderer>()->GetTexture()->GetWidth();
				boardTop = col->position.y;

				isOnBoard = true;
			}
		}
	}
}

void CEnemy::Boom(float time, int count, int repeat)
{
	auto emitter = new CEmitter("resources/Effect/Nut.png");
	emitter->lifeTime(0.3f, 0.5f)
		->speed(0.001f, 0.015f)
		->color(D3DXCOLOR(1, 1, 1, 1), D3DXCOLOR(1, 1, 1, 0))
		->start(time, count, repeat);
	emitter->position.SetVector(position.x + this->sprite->GetTexture()->GetWidth() / 4, position.y + this->sprite->GetTexture()->GetHeight() / 4);
	if (RGApp->GetScene()->scenetype == "Boss")
		RGApp->GetScene<BossStage>()->PushBackGameObject(emitter);
	if (RGApp->GetScene()->scenetype == "MidBoss")
		RGApp->GetScene<MidBossStage>()->PushBackGameObject(emitter);
	if (RGApp->GetScene()->scenetype == "Zako")
		RGApp->GetScene<ZakoStage>()->PushBackGameObject(emitter);
}

void CEnemy::SetCollider()
{
	auto collider = AttachComponent<Components::BoxCollider>();
	collider->box.SetRect(
		Math::Vector(0.0f, 0.0f),
		Math::Vector((float)sprite->GetTexture()->GetWidth(), (float)sprite->GetTexture()->GetHeight())
	);
}