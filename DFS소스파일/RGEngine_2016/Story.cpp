#include "Story.h"
#include "PlayerSelect.h"
#include "TestScene.h"
#include "ZakoStage.h"

Story::Story() : pageCount(0)
{
	PushBackGameObject(BGM = new Sound("resources/Sound/Stage1.wmv", -1));
	PushBackGameObject(tutorial = new Sprite("resources/Background/Tuto.png"));
	PushBackGameObject(story = new Sprite("resources/Background/Story.png"));
	PushBackGameObject(ChangeSceneLBtn = new Sprite("resources/Button/ChangeSceneL.png"));
	ChangeSceneLBtn->position.SetVector(10, 500);
	PushBackGameObject(ChangeSceneRBtn = new Sprite("resources/Button/ChangeSceneR.png"));
	ChangeSceneRBtn->position.SetVector(1150, 500);
}

Story::~Story()
{
}

void Story::OnUpdate(void)
{
	if (RGInput->Trigger(DIK_LEFT) && pageCount != 0)
	{
		story->SetEnabled(true);
		tutorial->SetEnabled(false);
		--pageCount;
	}
	else if (RGInput->Trigger(DIK_LEFT) && pageCount == 0)
	{
		RGApp->ChangeScene(new PlayerSelect());
	}
	else if ((RGInput->Trigger(DIK_RIGHT) || RGInput->Trigger(DIK_RETURN)) && pageCount != 1)
	{
		story->SetEnabled(false);
		tutorial->SetEnabled(true);
		++pageCount;
	}
	else if ((RGInput->Trigger(DIK_RIGHT) || RGInput->Trigger(DIK_RETURN)) && pageCount == 1)
	{
		BGM->audio->Stop();
		RGApp->ChangeScene(new ZakoStage(1));
	}
	else if (RGInput->Trigger(DIK_ESCAPE))
	{
		BGM->audio->Stop();
		RGApp->ChangeScene(new PlayerSelect());
	}
}
