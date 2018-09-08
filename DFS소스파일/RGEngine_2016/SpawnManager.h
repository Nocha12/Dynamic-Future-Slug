#pragma once
#include "Normal.h"
#include "NormalDrone.h"
#include "Turret.h"
#include "Boss1.h"
#include "Boss2.h"
#include "Boss3.h"
#include "MidBoss1.h"
#include "MidBoss2.h"
#include "MidBoss3.h"

#define SpawnMgr CSpawnManager::GetInstance()

namespace Enemy
{
	enum Type
	{
		Normal,
		Drone,
		Turret,
		Boss1,
		Boss2,
		Boss3,
		MidBoss1,
		MidBoss2,
		MidBoss3
	};
}

using namespace std;

class CSpawnManager
{
public:
	list<CEnemy*> enemyList;
public:
	CSpawnManager();
	~CSpawnManager();

	static CSpawnManager *GetInstance();

	void addEnemy(float x, float y, Enemy::Type type = Enemy::Normal);
	void addEnemy(const RGEngine::Math::Vector &v, Enemy::Type type = Enemy::Normal);
	void deleteEnemy(CEnemy *enemy);
	void popEnemy();
};