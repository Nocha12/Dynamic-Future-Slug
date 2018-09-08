#pragma once
#include "RGEngine.h"

using namespace RGEngine;

class CLaser : public RGEngine::GameObject
{
public:
	float times;

public:
	Components::SpriteRenderer *laserImg;

	CLaser();
	~CLaser();

	void OnUpdate();
	void OnCollision(GameObject *col);
};

