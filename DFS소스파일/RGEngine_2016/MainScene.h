#pragma once
#include "RGEngine.h"

#include "Sound.h"
#include "Sprite.h"
#include "Text.h"

using namespace RGEngine;

class MainScene : public RGEngine::Scene
{
public:
	MainScene();
	~MainScene();

	Sprite *StartBtn;
	Sprite *ExitBtn;
	Sprite *StartBtnOn;
	Sprite *ExitBtnOn;
	Sprite *Background;
	Sound *BGM;

	void OnUpdate(void) override;
};

