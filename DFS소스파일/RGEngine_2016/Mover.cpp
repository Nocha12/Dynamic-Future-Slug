#include "Mover.h"

CMover::CMover() { animation = AttachComponent<Components::AnimationRenderer>(); }

CMover::CMover(std::string path)
{
	sprite = AttachComponent<Components::SpriteRenderer>();
	sprite->SetTexture(path);
	sprite->GetGameObject()->rotationCenter.SetVector(
		sprite->GetTexture()->GetWidth() / 2.0f,
		sprite->GetTexture()->GetHeight() / 2.0f);
}

void CMover::InitImage(std::string path)
{
	sprite = AttachComponent<Components::SpriteRenderer>();
	sprite->SetTexture(path);

	sprite->GetGameObject()->rotationCenter.SetVector(
		sprite->GetTexture()->GetWidth() / 2.0f,
		sprite->GetTexture()->GetHeight() / 2.0f);

	sprite->GetGameObject()->scalingCenter.SetVector(
		sprite->GetTexture()->GetWidth() / 2.0f,
		sprite->GetTexture()->GetHeight() / 2.0f);
}

void CMover::InitAnimation(std::string path)
{
	animation->PushBackFrame(path);
	animation->GetGameObject()->rotationCenter.SetVector(
		animation->GetTexture(0)->GetWidth() / 2.0f,
		animation->GetTexture(0)->GetHeight() / 2.0f);
	
	animation->GetGameObject()->scalingCenter.SetVector(
		animation->GetTexture(0)->GetWidth() / 2.0f,
		animation->GetTexture(0)->GetHeight() / 2.0f);
}
