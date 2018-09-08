#pragma once
#include "RGEngine.h"

using namespace RGEngine;

class Sound : public RGEngine::GameObject
{
public:
	Components::AudioSource *audio;
	bool isFaidIn;
	bool isFaidOut;
	float faid;
	float maxSound;

public:
	Sound(std::string path);
	Sound(std::string path, int loopcount);
	~Sound() {}

	void OnUpdate() override;

	void FaidIn(float maxSound)
	{
		this->maxSound = maxSound;
		faid = 0;
		isFaidIn = true;
	}
	void FaidOut(float nowSound)
	{
		isFaidOut = true;
		faid = nowSound;
	}
};

