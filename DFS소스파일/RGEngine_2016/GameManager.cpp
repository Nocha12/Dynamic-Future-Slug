#include "GameManager.h"

float CGameManager::g{ NULL };

CGameManager::CGameManager() : stage(1), playerType(0), isPause(false), life(MAXLIFE), deathTimer(0), isDeath(false), isBoss(false) { g = 9.81f; }

void CGameManager::Initiate()
{
	life = MAXLIFE;
	deathTimer = 0;
	stage = 1;
	isPause = false;
	isBoss = false;
}

void CGameManager::DeathManage()
{
	deathTimer += deltaTime();
}

