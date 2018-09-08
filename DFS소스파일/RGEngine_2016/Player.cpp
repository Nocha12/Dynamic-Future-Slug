#include "Player.h"
#include "BulletManager.h"
#include "GameManager.h"
#include "ZakoStage.h"
#include "Ground.h"
#include "MidBossStage.h"
#include "BossStage.h"
#include "MainScene.h"
bool CPlayer::isLeft{ NULL };

CPlayer::CPlayer() : isOnGround(true), initialized(false), gravity(0.f), speed(400.f), weight(20.f), hp(1), ap(100), ammo(15), ultTime(30.0f), //attribute
aimUp(false), aimDown(false), // aim
jump(false), jumpPower(1000.f), // jump
cameraSpeed(150.f), // camera_view
beforeState(-2), state(0), setState(false), minX(0), maxX(1200) // animation
{
	isLeft = false;
	tag = "Player";
	shot = new Sound("resources/Sound/PlayerShot.wav", 0);
	reload = new Sound("resources/Sound/Reload.wav", 0);
	if (GM->playerType == 0)
	{
		InitAnimation("resources/Player/stop_fem.png"); // 0
		InitAnimation("resources/Player/1.png"); // 1
		InitAnimation("resources/Player/2.png");
		InitAnimation("resources/Player/3.png");
		InitAnimation("resources/Player/4.png");
		InitAnimation("resources/Player/5.png");
		InitAnimation("resources/Player/6.png");
		InitAnimation("resources/Player/7.png");
		InitAnimation("resources/Player/8.png");
		InitAnimation("resources/Player/jump_fem1.png"); // 2
		InitAnimation("resources/Player/jump_fem2.png");
		InitAnimation("resources/Player/jump_fem3.png");
		InitAnimation("resources/Player/jump_fem4.png");
		InitAnimation("resources/Player/slide_fem1.png");  // 3
		InitAnimation("resources/Player/slide_fem2.png");
		InitAnimation("resources/Player/dead_fem.png");  // -1
	}
	else if (GM->playerType == 1)
	{
		InitAnimation("resources/Player/stop_m.png"); // 0
		InitAnimation("resources/Player/B1.png"); // 1
		InitAnimation("resources/Player/B2.png");
		InitAnimation("resources/Player/B3.png");
		InitAnimation("resources/Player/B4.png");
		InitAnimation("resources/Player/B5.png");
		InitAnimation("resources/Player/B6.png");
		InitAnimation("resources/Player/B7.png");
		InitAnimation("resources/Player/B8.png");
		InitAnimation("resources/Player/jump_m1.png"); // 2
		InitAnimation("resources/Player/jump_m2.png");
		InitAnimation("resources/Player/jump_m3.png");
		InitAnimation("resources/Player/jump_m4.png");
		InitAnimation("resources/Player/slide_m1.png");  // 3
		InitAnimation("resources/Player/slide_m2.png");
		InitAnimation("resources/Player/dead_m.png");  // -1
	}

	animation->speed = 10.0f;

	auto collider = AttachComponent<Components::BoxCollider>();
	collider->box.SetRect(
		Math::Vector(0.0f, 0.0f),
		Math::Vector((float)animation->GetTexture(0)->GetWidth(), (float)animation->GetTexture(0)->GetHeight())
	);
}

CPlayer::~CPlayer()
{
}

void CPlayer::SetArm()
{
	arm = new CArm();
	if(RGApp->GetScene()->scenetype == "Zako")
		RGApp->GetScene<ZakoStage>()->PushBackGameObject(arm);
	else if(RGApp->GetScene()->scenetype == "MidBoss")
		RGApp->GetScene<MidBossStage>()->PushBackGameObject(arm);
	else if (RGApp->GetScene()->scenetype == "Boss")
		RGApp->GetScene<BossStage>()->PushBackGameObject(arm);
}

void CPlayer::Ultimate(float x, float y, float angle)
{
	CLaser *laser = new CLaser();
	RGApp->GetScene()->PushBackGameObject(laser);
	laser->position.SetVector(x, y);
	laser->rotate = D3DXToRadian(angle);
}

void CPlayer::MakeBullet(float x, float y, float angle, float angleRate, float speed, float speedRate)
{
	auto temp = new CBullet(x, y, angle, angleRate, speed, speedRate);
	temp->tag = "PBullet";
	if (RGApp->GetScene()->scenetype == "Zako")
		RGApp->GetScene<ZakoStage>()->PushBackGameObject(temp);
	else if (RGApp->GetScene()->scenetype == "MidBoss")
		RGApp->GetScene<MidBossStage>()->PushBackGameObject(temp);
	else if (RGApp->GetScene()->scenetype == "Boss")
		RGApp->GetScene<BossStage>()->PushBackGameObject(temp);
	BM->bulletList.push_back(temp);
	shot->audio->Play();
	shot->audio->SetVolume(0.03f);
}

void CPlayer::PrecomposeGrenade(CGrenade *_grenades[])
{
	for (int i = 0; i < 2; i++)
	{
		grenades[i] = _grenades[i];
		grenades[i]->SetEnabled(false);
	}
}

void CPlayer::ThrowGrenade()
{
	float x = position.x + animation->GetTexture(0)->GetWidth();

	if (isLeft)
		x = position.x;

	if (!grenades[0]->GetEnabled())
	{
		grenades[0]->SetEnabled(true);
		grenades[0]->position.SetVector(x, position.y + animation->GetTexture(0)->GetHeight() / 2.f);
	}
	else if (!grenades[1]->GetEnabled())
	{
		grenades[1]->SetEnabled(true);
		grenades[1]->position.SetVector(x, position.y + animation->GetTexture(0)->GetHeight() / 2.f);
	}
}

void CPlayer::ChangeAnimation(int state)
{
	if (hp == 0)
		this->state = state = -1;

	if (beforeState != state)
	{
		if (!animation->loop)
			animation->loop = true;

		if (animation->speed != 10.0f)
			animation->speed = 10.0f;
		
		switch (state)
		{
		case 0: // stop
			animation->startFrame = 0;
			animation->nowFrame = 0;
			animation->endFrame = 1;
			break;
		case 1: // walk
			animation->startFrame = 1;
			animation->nowFrame = 1;
			animation->endFrame = 9;
			break;
		case 2: // jump
			animation->loop = false;
			animation->speed = 7.5f;
			animation->startFrame = 9;
			animation->nowFrame = 9;
			animation->endFrame = 13;
			break;
		case 3: // slide
			animation->startFrame = 13;
			animation->nowFrame = 13;
			animation->endFrame = 15;
			break;
		case -1: // dead
			animation->startFrame = 15;
			animation->nowFrame = 15;
			animation->endFrame = 16;
		}
		if (animation->pause)
			animation->pause = false;
		beforeState = state;
	}
}

void CPlayer::Move()
{
	if (!initialized)
	{
		SetArm();
		initialized = true;
	}

	if ((!RGInput->Press(DIK_LEFTARROW) && !RGInput->Press(DIK_RIGHTARROW))
		|| (RGInput->Press(DIK_LEFTARROW) && RGInput->Press(DIK_RIGHTARROW)))
	{
		if (state != 2 && state != 3)
		{
			state = 0;
			ChangeAnimation(state);
		}
	}

	if (RGInput->Press(DIK_LEFTARROW))
	{
		this->position.Transform(-speed * deltaTime(), 0.f);
		if (!isLeft)
		{
			this->scale.x = -1;
			arm->scale.y = -1;
			//arm->rotationCenter.SetVector(0, 25);
			isLeft = true;
		}
		if (state != 2 && state != 3)
		{
			state = 1;
			ChangeAnimation(state);
		}
	}
	// Move Left

	if (RGInput->Press(DIK_RIGHTARROW))
	{
		this->position.Transform(speed * deltaTime(), 0.f);
		if (isLeft)
		{
			this->scale.x = 1;
			arm->scale.y = 1;
			//arm->rotationCenter.SetVector(0, 25);
			isLeft = false;
		}
		if (state != 2 && state != 3)
		{
			state = 1;
			ChangeAnimation(state);
		}
	}
	// Move Right

	if (RGInput->Press(DIK_UPARROW))
	{
		aimUp = true;
		if (aimDown)
			aimDown = false;
		arm->rotate = -1.5f;
	}
	//Aim Up

	else if (isLeft) {
		arm->rotate = 3.0f;
		aimUp = false;
		aimDown = false;
	} else {
		arm->rotate = 0.0f;
		aimUp = false;
		aimDown = false;
	}

	if (RGInput->Trigger(DIK_Z))
	{
		if (ammo > 0)
		{
			float x = this->position.x + this->animation->GetTexture(0)->GetWidth() / 2;
			float y = this->position.y + this->animation->GetTexture(0)->GetHeight() / 2 - 30;
			if (isLeft)
			{
				if (aimUp)
				{
					MakeBullet(x, y - 30, 0.25f, 0.0f, 0.03f, 0.0f);
				}
				else {
					MakeBullet(x - 80, y, 0.0f, 0.0f, 0.03f, 0.0f);
				}
			}
			else
			{
				if (aimUp)
				{
					MakeBullet(x, y - 30, 0.25f, 0.0f, 0.03f, 0.0f);
				}
				else {
					MakeBullet(x + 80, y, 0.5f, 0.0f, 0.03f, 0.0f);
				}
			}

			--ammo;
		}
	}

	if(!isLeft)
		arm->position.SetVector(position.x + 45, position.y + 60);
	else if(isLeft)
		arm->position.SetVector(position.x + 10, position.y + 45);
	if (!jump)
	{
		if (RGInput->Trigger(DIK_C))
		{
			state = 2;
			ChangeAnimation(state);
			jump = true;
			isOnGround = false;
		}
	}
	if (jump)
	{
		position.SetVector(position.x, position.y - (jumpPower * deltaTime()));
	}
	// Jump

	if (RGInput->Trigger(DIK_D))
	{
		if (ultTime <= 0.0f)
		{
			if (isLeft)
			{
				if (aimUp)
				{
					Ultimate(this->position.x + this->animation->GetTexture(0)->GetWidth() / 2, this->position.y - 70.0f, -90.0f);
				}
				else if (aimDown) {
					Ultimate(this->position.x + 160.0f, this->position.y + this->animation->GetTexture(0)->GetHeight(), 90.0f);
				}
				else {
					Ultimate(this->position.x - 70.0f, this->position.y + this->animation->GetTexture(0)->GetHeight() / 2 - 50.0f, 180.0f);
				}
			}
			else
			{
				if (aimUp)
				{
					Ultimate(this->position.x + this->animation->GetTexture(0)->GetWidth() / 2, this->position.y - 70.0f, -90.0f);
				}
				else if (aimDown) {
					Ultimate(this->position.x + 160.0f, this->position.y + this->animation->GetTexture(0)->GetHeight(), 90.0f);
				}
				else {
					Ultimate(this->position.x - 70.0f, this->position.y + this->animation->GetTexture(0)->GetHeight() / 2 - 50.0f, 0.0f);
				}
			}
			ultTime = 30.0f;
		}
		
	}

	if (RGInput->Trigger(DIK_X))
	{
		if (ammo == 0)
		{
			reload->audio->Play();
			reload->audio->SetVolume(0.05f);
			ammo = 15;
		}
	}

	if (!isOnBoard)
	{
		if (!isOnGround)
		{
			gravity += ((CGameManager::g + weight) * deltaTime());

			if ((position.y + animation->GetTexture(0)->GetHeight() + gravity) >= GROUND->position.y - 100)
			{
				position.SetVector(position.x, GROUND->position.y - animation->GetTexture(0)->GetHeight() - 100);

				isOnGround = true;

				if (jump)
					jump = false;

				gravity = 0.0f;

				if (state == 2)
					state = 0;
			}
			else
				position.Transform(0.0f, gravity);
		}
	} else {
			if (state == 2)
			{
				state = 0;
				ChangeAnimation(state);
			}

		if ((this->position.x + this->animation->GetTexture(0)->GetWidth()) <= boardLeft
			|| this->position.x >= boardRight
			|| this->position.y < boardTop)
		{
			isOnBoard = false;
		}

	}
	// Gravity
	if (ultTime - deltaTime() < 0.0f)
		ultTime = 0.0f;
	else
		ultTime -= deltaTime();
	if (position.x < minX)
		position.x = minX;
	else if (position.x > maxX)
		position.x = maxX;
}

void CPlayer::OnCollision(GameObject *col)
{
	if (col->tag.compare("Enemy") == 0)
	{
		if (!GM->isBoss)
		{
			if (GM->deathTimer >= 3)
			{
				GM->deathTimer = 0;
				if (GM->life == 0)
					RGApp->ChangeScene(new MainScene());
				--GM->life;
				this->SetEnabled(false);
				GM->isDeath = true;
			}
		}
	}

	if (col->tag.compare("Board") == 0)
	{
		if (!isOnGround)
		{
			if (this->position.y + this->animation->GetTexture(0)->GetHeight() > col->position.y
				&& this->position.y + this->animation->GetTexture(0)->GetHeight() < col->position.y + col->GetComponent<Components::SpriteRenderer>()->GetTexture()->GetHeight()
				&& this->position.x + this->animation->GetTexture(0)->GetWidth() > col->position.x
				&& this->position.x < col->position.x + col->GetComponent<Components::SpriteRenderer>()->GetTexture()->GetWidth())
			{
				gravity = 0.0f;

				this->position.y = col->position.y - this->animation->GetTexture(0)->GetHeight();

				boardLeft = col->position.x;
				boardRight = col->position.x + col->GetComponent<Components::SpriteRenderer>()->GetTexture()->GetWidth();
				boardTop = col->position.y;

				if (jump)
					jump = false;
				
				isOnBoard = true;

				if (state == 2)
				{
					state = 0;
					ChangeAnimation(state);
				}
			}
		}
	}
}