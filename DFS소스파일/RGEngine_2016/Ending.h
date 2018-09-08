#pragma once
#include "RGEngine.h"

#include "Sprite.h"

using namespace RGEngine;

class Ending : public RGEngine::Scene
{
public:
	Ending(int nowStage);
	~Ending();

	Sprite *story;
	int stage;

	void OnUpdate(void) override;
};

