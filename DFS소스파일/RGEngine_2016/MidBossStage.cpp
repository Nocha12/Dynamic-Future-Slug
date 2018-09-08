#include "MidBossStage.h"
#include "BossStage.h"
#include "Ground.h"

MidBossStage::MidBossStage(int nowStage) : nowStage(nowStage), isBossSpawn(false)
{
	PushBackGameObject(BGM = new Sound("resources/Sound/Stage2.wmv", -1));
	RGAssetTexture->Load("resources/Boss/BossHPBack.png");
	bossHPbarBack = RGAssetTexture->Get("resources/Boss/BossHPBack.png");

	RGAssetTexture->Load("resources/Boss/BossHP.png");
	bossHPbar = RGAssetTexture->Get("resources/Boss/BossHP.png");
	bossHPbar->flagAutoRect = false;

	tBossHP = new GameObject();
	tBossHP->position.SetVector(32.5f, 30.0f);

	scenetype = "MidBoss";

	if (nowStage == 1)
		PushBackGameObject(background = new Sprite("resources/Background/Stage1_MidBoss.png"));
	else if (nowStage == 2)
		PushBackGameObject(background = new Sprite("resources/Background/Stage2_MidBoss.png"));
	else if (nowStage == 3)
		PushBackGameObject(background = new Sprite("resources/Background/Stage3_MidBoss.png"));
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
	nextScene->position.SetVector(1050, 100);
	nextScene->SetEnabled(false);
	PushBackGameObject(player = new CPlayer());
	player->position.SetVector(0, GROUND->position.y - player->animation->GetTexture(0)->GetHeight() - 100);

	if (nowStage == 1)
	{
		for (int i = 0; i < 3; ++i)
			PushBackGameObject(board[i] = new CBoard());

		board[0]->position.SetVector(0, 650.0f);
		board[1]->position.SetVector(550.0f, 650.0f);
		board[2]->position.SetVector(1100.0f, 650.0f);
	}
	else if (nowStage == 2)
	{
		PushBackGameObject(board[0] = new CBoard());
		PushBackGameObject(board[1] = new CBoard());
		board[0]->position.SetVector(0, 650.0f);
		board[1]->position.SetVector(550.0f, 650.0f);
	}
	GM->isBoss = true;
}

MidBossStage::~MidBossStage()
{
}

void MidBossStage::OnUpdate()
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
			PushBackGameObject(MidBoss = new CMidBoss1());
			MidBoss->position.SetVector(1300, 600);
		}
		if (nowStage == 2)
		{
			PushBackGameObject(MidBoss = new CMidBoss2());
			MidBoss->position.SetVector(950, 750);
		}
		if (nowStage == 3)
		{
			PushBackGameObject(MidBoss = new CMidBoss3());
			MidBoss->position.SetVector(1250, 680);
		}
		isBossSpawn = true;
	}
	if(MidBoss->hp >= 0)
		bossHPbar->sourceRect.right = (float)MidBoss->hp / MidBoss->maxHp * 1160;
	if (MidBoss->hp <= 0)
	{
		if (player->position.x > 1300)
		{
			BGM->audio->Stop();
			RGApp->ChangeScene(new BossStage(nowStage));
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

void MidBossStage::OnAfterRender()
{
	tBossHP->Render();
	bossHPbarBack->Blt();
	bossHPbar->Blt();
}
