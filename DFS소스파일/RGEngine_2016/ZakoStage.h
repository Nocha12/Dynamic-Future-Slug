#pragma once
#include "RGEngine.h"

#include "Sound.h"
#include "Sprite.h"
#include "Text.h"
#include "Player.h"
#include "Board.h"
#include "GameManager.h"

using namespace RGEngine;

class ZakoStage : public RGEngine::Scene
{
public:
	ZakoStage(int nowStage);
	~ZakoStage();
	Sound *BGM;
	CPlayer *player;
	Sprite *background;
	Sprite *UIBackground;
	Sprite *head;
	Sprite *life[MAXLIFE];
	Sprite *nextScene;
	int nowStage;
	float timer;
	int enemyCount;
	int runCount;
	int droneCount;
	CBoard *board[4];

	void OnUpdate() override;

	CPlayer *GetPlayer(void)
	{
		if (player) return player;
		else return NULL;
	}
};

