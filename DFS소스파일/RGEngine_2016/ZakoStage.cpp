#include "ZakoStage.h"
#include "SpawnManager.h"
#include "Ground.h"
#include "MidBossStage.h"
#include "BossStage.h"

ZakoStage::ZakoStage(int nowStage) : timer(0), enemyCount(0), runCount(0), droneCount(0), nowStage(nowStage)
{
	scenetype = "Zako";
	PushBackGameObject(BGM = new Sound("resources/Sound/Stage1.wmv", -1));
	if(nowStage == 1)
		PushBackGameObject(background = new Sprite("resources/Background/Stage1_Zako.png"));
	else if(nowStage == 2)
		PushBackGameObject(background = new Sprite("resources/Background/Stage2_Zako.png"));
	else if (nowStage == 3)
		PushBackGameObject(background = new Sprite("resources/Background/Stage3_Zako.png"));
	PushBackGameObject(nextScene = new Sprite("resources/Button/NextButton.png"));
	PushBackGameObject(UIBackground = new Sprite("resources/UI/UibackGround.png"));
	UIBackground->position.SetVector(0, 904);
	if(GM->playerType == 0)
		PushBackGameObject(head = new Sprite("resources/UI/GirlFace.png"));
	else
		PushBackGameObject(head = new Sprite("resources/UI/ManFace.png"));
	head->position.SetVector(-50, 884);

	for (int i = 0; i < MAXLIFE; i++)
	{
		PushBackGameObject(life[i] = new Sprite("resources/UI/LifeIn.png"));
		life[i]->position.SetVector(150 + 80 * i, 950);
	}
	nextScene->position.SetVector(1050, 100);
	nextScene->SetEnabled(false);
	PushBackGameObject(player = new CPlayer());
	player->position.SetVector(0, GROUND->position.y - player->animation->GetTexture(0)->GetHeight() - 100);

	for (int i = 0; i < 4; ++i)
		PushBackGameObject(board[i] = new CBoard());

	board[0]->position.SetVector(100.0f, 650.0f);
	board[1]->position.SetVector(400.0f, 550.0f);
	board[2]->position.SetVector(700.0f, 550.0f);
	board[3]->position.SetVector(1000.0f, 650.0f);
	GM->isBoss = false;
}

ZakoStage::~ZakoStage()
{
}

void ZakoStage::OnUpdate()
{
	//test
	//RGApp->ChangeScene(new BossStage(3));
	if (GM->life == 0)
		BGM->audio->Stop();
	GM->DeathManage();
	if (GM->isDeath)
	{
		GM->isDeath = false;
		player->SetEnabled(true);
		player->position.SetVector(0, GROUND->position.y - player->animation->GetTexture(0)->GetHeight() - 100);
	}
	if (enemyCount > 10 && SpawnMgr->enemyList.empty())
	{
		if (player->position.x > 1300)
		{
			BGM->audio->Stop();
			RGApp->ChangeScene(new MidBossStage(nowStage));
		}
		nextScene->SetEnabled(true);
		player->maxX = 1500;
	}
	if (timer >= 1 && enemyCount <= 10)
	{
		int t = Math::Random(0, 2);

		if (t == 1 && droneCount < 2)
		{
			timer = 0;
			++enemyCount;
			SpawnMgr->addEnemy(Math::Vector(1300, Math::Random(50, 100)), (Enemy::Type)t);
			++droneCount;
		}
		else if (t == 0 && runCount < 3)
		{
			timer = 0;
			++enemyCount;
			SpawnMgr->addEnemy(Math::Vector(1300, 730), (Enemy::Type)t);
			++runCount;
		}
		else if (t == 2)
		{
			timer = 0;
			++enemyCount;
			SpawnMgr->addEnemy(Math::Vector(1300, 730), (Enemy::Type)t);
		}

	}
	timer += deltaTime();

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
