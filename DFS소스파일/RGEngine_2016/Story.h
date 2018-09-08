#pragma once
#include "RGEngine.h"

#include "Sound.h"
#include "Sprite.h"
#include "Text.h"

using namespace RGEngine;

class Story : public RGEngine::Scene
{
public:
	Story();
	~Story();

	int pageCount;
	Sprite *story;
	Sprite *tutorial;
	Sprite *ChangeSceneLBtn;
	Sprite *ChangeSceneRBtn;
	Sound *BGM;

	void OnUpdate(void) override;
};

