#include "Grenade.h"
#include "GameManager.h"
#include "Player.h"

CGrenade::CGrenade() : gravity(0.f), throwSpeed(500.f), throwPower(200.f), weight(10.f),
					 times(0.f)
{
	tag = "Grenade";
	InitImage("resources/Grenade/Grenade.png");
	rotationCenter.SetVector(sprite->GetTexture()->GetWidth() / 2.f, sprite->GetTexture()->GetHeight() / 2.f);
	auto collider = AttachComponent<Components::CircleCollider>();
	collider->circle.SetCircle(rotationCenter.x, rotationCenter.y, rotationCenter.x);
}

CGrenade::~CGrenade()
{
}

void CGrenade::OnEnabled(void)
{
	throwSpeed = Math::Abs<float>(throwSpeed, NULL);
	gravity = 0.f;
	times = 0.f;
	if (CPlayer::isLeft)
		throwSpeed *= -1;
}

void CGrenade::Move()
{
	position.Transform(throwSpeed * deltaTime(), -throwPower * deltaTime());
	// throw


	gravity += ((CGameManager::g + weight) * deltaTime());

	// When dropped pos overlaps with ground
	if ((position.y + sprite->GetTexture()->GetHeight() + gravity) >= RGGraphic->GetScreenHeight())
	{
		position.SetVector(position.x, RGGraphic->GetScreenHeight() - sprite->GetTexture()->GetHeight());
		printf("BOOM\n");
		
		SetEnabled(false);
	}
	else
		position.Transform(0.f, gravity);

	times += deltaTime();
}