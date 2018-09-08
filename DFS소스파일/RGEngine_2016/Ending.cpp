#include "Ending.h"
#include "ZakoStage.h"
#include "MainScene.h"

Ending::Ending(int nowStage) : stage(nowStage)
{
	if(nowStage == 1)
		PushBackGameObject(story = new Sprite("resources/Background/story1.png"));
	if (nowStage == 2)
		PushBackGameObject(story = new Sprite("resources/Background/story2.png"));
	if (nowStage == 3)
		PushBackGameObject(story = new Sprite("resources/Background/Ending.png"));
}

Ending::~Ending()
{
}

void Ending::OnUpdate(void)
{
	if (RGInput->Trigger(DIK_RETURN))
		if(stage != 3)
			RGApp->ChangeScene(new ZakoStage(stage + 1));
		else
			RGApp->ChangeScene(new MainScene());
}
