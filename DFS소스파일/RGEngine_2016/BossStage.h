#pragma once
#include "RGEngine.h"

#include "Sound.h"
#include "Sprite.h"
#include "Text.h"
#include "Player.h"
#include "Board.h"
#include "Boss1.h"
#include "Boss2.h"
#include "Boss3.h"
#include "GameManager.h"

using namespace RGEngine;

class BossStage : public RGEngine::Scene
{
public:
	BossStage(int nowStage);
	~BossStage();

	Sound *BGM;
	CBoard *board[4];
	CEnemy *Boss;
	Assets::Texture *bossHPbar;
	Assets::Texture *bossHPbarBack;
	Sprite *UIBackground;
	Sprite *head;
	Sprite *life[MAXLIFE];
	CPlayer *player;
	Sprite *background;
	Sprite *nextScene;
	GameObject *tBossHP;
	int nowStage;
	bool isBossSpawn;

	void OnUpdate() override;
	void OnAfterRender() override;

	CPlayer *GetPlayer(void)
	{
		if (player) return player;
		else return NULL;
	}
};

