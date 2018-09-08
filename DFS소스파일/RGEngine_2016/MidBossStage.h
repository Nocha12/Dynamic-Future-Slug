#pragma once
#include "RGEngine.h"

#include "Sound.h"
#include "Sprite.h"
#include "Text.h"
#include "Player.h"
#include "Board.h"
#include "MidBoss1.h"
#include "MidBoss2.h"
#include "MidBoss3.h"
#include "GameManager.h"

using namespace RGEngine;

class MidBossStage : public RGEngine::Scene
{
public:
	MidBossStage(int nowStage);
	~MidBossStage();

	Sound *BGM;
	CBoard *board[4];
	CEnemy *MidBoss;
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

