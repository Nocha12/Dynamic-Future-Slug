#pragma once
#include "RGEngine.h"

using namespace RGEngine;

class Sprite : public RGEngine::GameObject
{
public:
	Components::SpriteRenderer *sprite;
	bool isFaidIn;
	bool isFaidOut;
	bool isFaidInNOut;
	bool isDestroy;
	float faid;
public:
	Sprite(std::string path);
	~Sprite() {}

	void OnUpdate() override;
	void FaidIn() { isFaidIn = true, faid = 0; }
	void FaidOut(bool isDestroy = false) { 
		isFaidOut = true, faid = 1; 
		this->isDestroy = isDestroy;
	}
	void FaidInNOut(bool isDestroy = false) {
		isFaidInNOut = true;
		isFaidIn = true;
		faid = 0;
		this->isDestroy = isDestroy;
	}
};

