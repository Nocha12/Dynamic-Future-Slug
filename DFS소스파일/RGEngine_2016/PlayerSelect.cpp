#include "PlayerSelect.h"
#include "GameManager.h"
#include "Story.h"
#include "MainScene.h"

PlayerSelect::PlayerSelect()
{
	PushBackGameObject(BGM = new Sound("resources/Sound/ChoiceTitle.wmv", -1));
	PushBackGameObject(background = new Sprite("resources/Background/PlayerSelect.png"));
	PushBackGameObject(type1 = new Sprite("resources/Button/Sarah.png"));
	type1->position.SetVector(400, 900);
	PushBackGameObject(type2 = new Sprite("resources/Button/Taylor.png"));
	type2->position.SetVector(800, 900);
	PushBackGameObject(type1On = new Sprite("resources/Button/SarahOn.png"));
	type1On->position.SetVector(400, 900);
	PushBackGameObject(type2On = new Sprite("resources/Button/TaylorOn.png"));
	type2On->position.SetVector(800, 900);
	type2On->SetEnabled(false);
}

PlayerSelect::~PlayerSelect()
{
}

void PlayerSelect::OnUpdate(void)
{
	if (RGInput->Trigger(DIK_LEFT))
	{
		type1On->SetEnabled(true);
		type2On->SetEnabled(false);
	}
	else if (RGInput->Trigger(DIK_RIGHT))
	{
		type1On->SetEnabled(false);
		type2On->SetEnabled(true);
	}
	else if (RGInput->Trigger(DIK_RETURN))
	{
		BGM->audio->Stop();
		if (type1On->GetEnabled())
			GM->playerType = 0;
		else 
			GM->playerType = 1;

		RGApp->ChangeScene(new Story());
	}
	else if (RGInput->Trigger(DIK_ESCAPE))
	{
		BGM->audio->Stop();
			RGApp->ChangeScene(new MainScene());
	}
}
