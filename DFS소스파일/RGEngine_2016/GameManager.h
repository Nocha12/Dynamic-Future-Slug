#pragma once
#include "RGEngine.h"

#define GM CGameManager::GetInstance()
#define MAXLIFE 5

using namespace RGEngine;

class CGameManager
{
public:
	bool isPause;
	static float g;
	int playerType;
	int stage;
	int life;
	float deathTimer;
	bool isDeath;
	bool isBoss;

public:
	CGameManager();
	~CGameManager() {}

	static CGameManager* GetInstance()
	{
		static CGameManager GameManagerIns;
		return &GameManagerIns;
	}

	void Initiate();
	void DeathManage();
};

