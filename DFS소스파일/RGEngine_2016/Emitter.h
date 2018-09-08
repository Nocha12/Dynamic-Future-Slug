#pragma once
#include "Mover.h"

class CParticle : public CMover
{
public:
	CParticle(std::string path, float angle, float Speed);
	~CParticle() { }

	float Angle;
	float Speed;
	float LifeTime;
	float LifeTimeOrigin;

	virtual void Move() override;
};

class CEmitter : public CMover
{
public:
	CEmitter(std::string path);
	~CEmitter();

	D3DXCOLOR colorFrom, colorTo;
	float scaleMin, scaleMax;
	float speedMin, speedMax;
	float lifeTimeMin, lifeTimeMax;
	float rotationMin, rotationMax;
	float rotationOffset;
	float rotationSpeed;
	bool isBlending;
	std::string spritePath;
	std::list<CParticle*> particleList;
	float time;
	float frequency;
	int quantity;
	int emitCount;
	int currentCount;
	bool started;

	virtual void Move() override;
	CEmitter* color(D3DXCOLOR from, D3DXCOLOR to);
	CEmitter* speed(float min, float max);
	CEmitter* scale(float min, float max);
	CEmitter* lifeTime(float min, float max);
	CEmitter* rotation(float min, float max);
	void start(float frequency, int quantity, int emitCount = INT_MAX);
	void createParticle();
};

