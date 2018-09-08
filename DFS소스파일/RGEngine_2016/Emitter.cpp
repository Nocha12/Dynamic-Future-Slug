#include "Emitter.h"
#include "BossStage.h"
#include "ZakoStage.h"
#include "MidBossStage.h"

CEmitter::CEmitter(std::string path) : spritePath(path), started(false), currentCount(0), time(0), rotationSpeed(0)
{
	this->color(D3DXCOLOR(1, 1, 1, 1), D3DXCOLOR(1, 1, 1, 1))
		->speed(0, 0)
		->scale(1, 1)
		->lifeTime(0, 0)
		->rotation(0, 1);
	time = 9999;
}

CEmitter::~CEmitter()
{
}

void CEmitter::start(float frequency, int quantity, int emitCount)
{
	this->frequency = frequency;
	this->quantity = quantity;
	this->emitCount = emitCount;
	started = true;
}

void CEmitter::createParticle()
{
	float angle = Math::Random(rotationMin, rotationMax) + rotationOffset;
	float speed = Math::Random(speedMin, speedMax);
	float lifeTime = Math::Random(lifeTimeMin, lifeTimeMax);
	CParticle *p = new CParticle(spritePath, angle, speed);
	p->position = this->position;
	if(RGApp->GetScene()->scenetype == "Boss")
		RGApp->GetScene<BossStage>()->PushBackGameObject(p);
	if (RGApp->GetScene()->scenetype == "MidBoss")
		RGApp->GetScene<MidBossStage>()->PushBackGameObject(p);
	if (RGApp->GetScene()->scenetype == "Zako")
		RGApp->GetScene<ZakoStage>()->PushBackGameObject(p);
	p->LifeTimeOrigin = lifeTime;
	particleList.push_back(p);
}

CEmitter* CEmitter::color(D3DXCOLOR from, D3DXCOLOR to)
{
	colorFrom = from;
	colorTo = to;
	return this;
}

CEmitter* CEmitter::speed(float min, float max)
{
	speedMin = min;
	speedMax = max;
	return this;
}

CEmitter* CEmitter::scale(float min, float max)
{
	scaleMin = min;
	scaleMax = max;
	return this;
}

CEmitter* CEmitter::lifeTime(float min, float max)
{
	lifeTimeMin = min;
	lifeTimeMax = max;
	return this;
}

CEmitter* CEmitter::rotation(float min, float max)
{
	rotationMin = min;
	rotationMax = max;
	return this;
}

void CEmitter::Move()
{
	time += deltaTime();
	if (time >= frequency)
	{
		time = 0;
		currentCount++;
		if (currentCount > emitCount)
			return;
		for (int i = 0; i < quantity; i++)
			createParticle();
	}
	if (particleList.empty())
		Destroy();
	for (auto i = particleList.begin(); i != particleList.end(); i++)
	{
		(*i)->LifeTime += deltaTime();
		(*i)->sprite->GetTexture()->color = colorFrom + (colorTo - colorFrom) * ((*i)->LifeTime / (*i)->LifeTimeOrigin);

		if ((*i)->LifeTime >(*i)->LifeTimeOrigin)
		{
			(*i)->Destroy();
			i = particleList.erase(i);
			if (i == particleList.end())
				break;
		}
	}
}

CParticle::CParticle(std::string path, float angle, float speed) : Angle(angle), Speed(speed)
{
	InitImage(path);
}

void CParticle::Move()
{
	float rad = Angle * D3DX_PI * 2;
	position.x += (Speed * cosf(rad) * deltaTime() * 50) * 375;
	position.y += (Speed * sinf(rad) * deltaTime() * 50) * 375;
}
