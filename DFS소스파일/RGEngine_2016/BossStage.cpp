#include "BossStage.h"
#include "ZakoStage.h"
#include "Ground.h"
#include "Ending.h"

BossStage::BossStage(int nowStage) : nowStage(nowStage), isBossSpawn(false)
{
	PushBackGameObject(BGM = new Sound("resources/Sound/Stage3.wmv", -1));
	RGAssetTexture->Load("resources/Boss/BossHPBack.png");
	bossHPbarBack = RGAssetTexture->Get("resources/Boss/BossHPBack.png");

	RGAssetTexture->Load("resources/Boss/BossHP.png");
	bossHPbar = RGAssetTexture->Get("resources/Boss/BossHP.png");
	bossHPbar->flagAutoRect = false;

	tBossHP = new GameObject();
	tBossHP->position.SetVector(32.5f, 30.0f);

	if (nowStage == 1)
		PushBackGameObject(background = new Sprite("resources/Background/Stage1_Boss.png"));
	else if (nowStage == 2)
		PushBackGameObject(background = new Sprite("resources/Background/Stage2_Boss.png"));
	else if (nowStage == 3)
		PushBackGameObject(background = new Sprite("resources/Background/Stage3_Boss.png"));
	PushBackGameObject(UIBackground = new Sprite("resources/UI/UibackGround.png"));
	UIBackground->position.SetVector(0, 904);
	if (GM->playerType == 0)
		PushBackGameObject(head = new Sprite("resources/UI/GirlFace.png"));
	else
		PushBackGameObject(head = new Sprite("resources/UI/ManFace.png"));
	head->position.SetVector(-50, 884);

	for (int i = 0; i < MAXLIFE; i++)
	{
		PushBackGameObject(life[i] = new Sprite("resources/UI/LifeIn.png"));
		life[i]->position.SetVector(150 + 80 * i, 950);
	}
	PushBackGameObject(nextScene = new Sprite("resources/Button/NextButton.png"));
	scenetype = "Boss";

	if (nowStage == 1)
	{
		PushBackGameObject(board[0] = new CBoard());
		board[0]->position.SetVector(0, 650);
	}
	else if (nowStage == 2)
	{
		PushBackGameObject(board[0] = new CBoard());
		board[0]->position.SetVector(0, 650);
		PushBackGameObject(board[1] = new CBoard());
		board[1]->position.SetVector(600, 650);
	}
	
	nextScene->position.SetVector(1050, 100);
	nextScene->SetEnabled(false);
	PushBackGameObject(player = new CPlayer());
	player->position.SetVector(0, GROUND->position.y - player->animation->GetTexture(0)->GetHeight() - 100);
	GM->isBoss = true;
}

BossStage::~BossStage()
{
}

void BossStage::OnUpdate()
{
	if (GM->life == 0)
		BGM->audio->Stop();
	GM->DeathManage();
	if (GM->isDeath)
	{
		GM->isDeath = false;
		player->SetEnabled(true);
		player->position.SetVector(0, GROUND->position.y - player->animation->GetTexture(0)->GetHeight() - 100);
	}
	if (!isBossSpawn)
	{
		if (nowStage == 1)
		{
			PushBackGameObject(Boss = new CBoss1());
			Boss->position.SetVector(1100, 700);
		}
		if (nowStage == 2)
		{
			PushBackGameObject(Boss = new CBoss2());
			Boss->position.SetVector(1000, 650);
		}
		if (nowStage == 3)
		{
			PushBackGameObject(Boss = new CBoss3());
			Boss->position.SetVector(700, 650);
		}
		isBossSpawn = true;
	}
	if (Boss->hp >= 0)
		bossHPbar->sourceRect.right = (float)Boss->hp / Boss->maxHp * 1160;
	if (Boss->hp <= 0)
	{
		if (player->position.x > 1300)
		{
			BGM->audio->Stop();
			RGApp->ChangeScene(new Ending(nowStage));
		}

		nextScene->SetEnabled(true);
		player->maxX = 1500;
	}
	auto gameObjects = GetGameObjects();

	for (int i = 0; i < GetGameObjectSize(); ++i)
	{
		CMover *gameObject = dynamic_cast<CMover*>(gameObjects[i]);
		if (gameObject && gameObject->GetEnabled())
			gameObject->Move();
	}
	for (int i = 0; i < MAXLIFE; i++)
	{
		if (GM->life >= 0)
		{
			if (GM->life > i)
				life[i]->SetEnabled(true);
			else if (life[i]->GetEnabled())
				life[i]->SetEnabled(false);
		}
	}
}

void BossStage::OnAfterRender()
{
	tBossHP->Render();
	bossHPbarBack->Blt();
	bossHPbar->Blt();
}
