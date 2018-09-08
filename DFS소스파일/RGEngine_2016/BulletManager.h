#pragma once
#pragma once
#include "RGEngine.h"

#include "Bullet.h"
#include "ConstrainedHomingBullet.h"

#define BM CBulletManager::GetInstance()

using namespace RGEngine;

class CBulletManager
{
public:
	CBulletManager();
	~CBulletManager();

	static CBulletManager* GetInstance()
	{
		static CBulletManager BulletManagerIns;
		return &BulletManagerIns;
	}

	std::list<CBullet *> bulletList;
};

