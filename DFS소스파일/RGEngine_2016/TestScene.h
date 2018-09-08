#pragma once
#include "RGEngine.h"

#include "Sound.h"
#include "Sprite.h"
#include "Text.h"
#include "Normal.h"
#include "MidBoss1.h"
#include "Player.h"
#include "Grenade.h"
#include "Board.h"

using namespace RGEngine;

class TestScene : public RGEngine::Scene
{
private:
	Sprite *background;
	Text *text;
	CMidBoss1 *boss;
	CPlayer *player;
	CGrenade *grenades[2];
	CBoard *board; // maybe array
	Text *ammoText, *ultimateText;

public:
	TestScene(void);
	~TestScene() override;

public:
	void OnUpdate(void) override;
	CPlayer *GetPlayer(void)
	{
		if (player) return player;
		else return NULL;
	}
};

