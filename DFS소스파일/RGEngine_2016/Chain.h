#pragma once
#include "RGEngine.h"

using namespace RGEngine;

class CChain : public RGEngine::GameObject
{
public:
	CChain();
	~CChain();

	Components::SpriteRenderer *chainImg;
	void OnCollision(GameObject *col);
};

