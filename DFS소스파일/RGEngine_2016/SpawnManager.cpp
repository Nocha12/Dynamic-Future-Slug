#include "SpawnManager.h"

CSpawnManager::CSpawnManager()
{
}

CSpawnManager::~CSpawnManager()
{
}

CSpawnManager* CSpawnManager::GetInstance()
{
	static CSpawnManager instance;
	return &instance;
}

void CSpawnManager::addEnemy(float x, float y, Enemy::Type type)
{
	CEnemy* enemy = new CEnemy();

	switch (type)
	{
	case Enemy::Normal:
		enemy = new CNormal();
		break;
	case Enemy::Drone:
		enemy = new CNormalDrone();
		break;
	case Enemy::Turret:
		enemy = new CTurret();
		break;
	case Enemy::Boss1:
		enemy = new CBoss1();
		break;
	case Enemy::Boss2:
		enemy = new CBoss2();
		break;
	case Enemy::Boss3:
		enemy = new CBoss3();
		break;
	case Enemy::MidBoss1:
		enemy = new CMidBoss1();
		break;
	case Enemy::MidBoss2:
		enemy = new CMidBoss2();
		break;
	case Enemy::MidBoss3:
		enemy = new CMidBoss3();
		break;
	}

	enemy->position.SetVector(x, y);
	RGApp->GetScene()->PushBackGameObject(enemy);
	enemyList.push_back(enemy);
}

void CSpawnManager::addEnemy(const RGEngine::Math::Vector &v, Enemy::Type type)
{
	CEnemy* enemy = new CEnemy();

	switch (type)
	{
	case Enemy::Normal:
		enemy = new CNormal();
		break;
	case Enemy::Drone:
		enemy = new CNormalDrone();
		break;
	case Enemy::Turret:
		enemy = new CTurret();
		break;
	case Enemy::Boss1:
		enemy = new CBoss1();
		break;
	case Enemy::Boss2:
		enemy = new CBoss2();
		break;
	case Enemy::Boss3:
		enemy = new CBoss3();
		break;
	case Enemy::MidBoss1:
		enemy = new CMidBoss1();
		break;
	case Enemy::MidBoss2:
		enemy = new CMidBoss2();
		break;
	case Enemy::MidBoss3:
		enemy = new CMidBoss3();
		break;
	}

	enemy->position.SetVector(v);
	RGApp->GetScene()->PushBackGameObject(enemy);
	enemyList.push_back(enemy);
}

void CSpawnManager::deleteEnemy(CEnemy *enemy)
{
	enemyList.remove(enemy);
	enemy->Destroy();
}

void CSpawnManager::popEnemy()
{
	if (enemyList.size() > 0)
	{
		CEnemy *enemy = enemyList.front();
		enemyList.pop_front();
		enemy->Destroy();
	}
}