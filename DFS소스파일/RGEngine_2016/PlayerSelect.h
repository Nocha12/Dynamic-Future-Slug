#pragma once
#include "RGEngine.h"

#include "Sound.h"
#include "Sprite.h"
#include "Text.h"

using namespace RGEngine;

class PlayerSelect : public RGEngine::Scene
{
public:
	PlayerSelect();
	~PlayerSelect();

	Sprite *type1;
	Sprite *type2;
	Sprite *type1On;
	Sprite *type2On;
	Sprite *background;
	Sound *BGM;

	void OnUpdate(void) override;
};

