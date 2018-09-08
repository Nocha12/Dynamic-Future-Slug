#include "MainScene.h"
#include "PlayerSelect.h"
#include "GameManager.h"
MainScene::MainScene()
{
	PushBackGameObject(BGM = new Sound("resources/Sound/MainTitle.wmv", -1));
	PushBackGameObject(Background = new Sprite("resources/Background/Title.png"));
	PushBackGameObject(StartBtn = new Sprite("resources/Button/Start.png"));
	StartBtn->position.SetVector(550, 700);
	PushBackGameObject(StartBtnOn = new Sprite("resources/Button/StartOn.png"));
	StartBtnOn->position.SetVector(550, 700);
	PushBackGameObject(ExitBtn = new Sprite("resources/Button/Exit.png"));
	ExitBtn->position.SetVector(550, 800);
	PushBackGameObject(ExitBtnOn = new Sprite("resources/Button/ExitOn.png"));
	ExitBtnOn->position.SetVector(550, 800);
	ExitBtnOn->SetEnabled(false);
}

MainScene::~MainScene()
{
}

void MainScene::OnUpdate(void)
{
	GM->Initiate();
	if (RGInput->Trigger(DIK_UP))
	{
		StartBtnOn->SetEnabled(true);
		ExitBtnOn->SetEnabled(false);
	}
	else if (RGInput->Trigger(DIK_DOWN))
	{
		StartBtnOn->SetEnabled(false);
		ExitBtnOn->SetEnabled(true);
	}
	else if (RGInput->Trigger(DIK_RETURN))
	{
		BGM->audio->Stop();
		if (StartBtnOn->GetEnabled())
			RGApp->ChangeScene(new PlayerSelect());
		else
			exit(0);
	}
}
