#pragma once
#include "RGEngine.h"

using namespace RGEngine;

class CMover : public RGEngine::GameObject
{
public: 
	enum BulletShape
	{
		Red,
		Blue
	};

public:
	Components::SpriteRenderer *sprite;
	Components::AnimationRenderer *animation;

public:
	CMover();
	CMover(std::string path);
	~CMover() {}

	virtual void Move() = 0;
	void InitImage(std::string path);
	void InitAnimation(std::string path);
};

