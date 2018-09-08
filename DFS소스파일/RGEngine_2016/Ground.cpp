#include "Ground.h"

CGround::CGround()
{
	tag = "Ground";

	InitImage("resources/Board/Board.png");

	this->position.SetVector(0.0f, RGApp->GetGraphic()->GetScreenHeight() - this->sprite->GetTexture()->GetHeight());

	auto collider = AttachComponent<Components::BoxCollider>();
	collider->box.SetRect(
		Math::Vector(0.0f, 0.0f),
		Math::Vector((float)sprite->GetTexture()->GetWidth(), (float)sprite->GetTexture()->GetHeight())
	);
}

CGround::~CGround()
{
}

CGround *CGround::GetInstance()
{
	static CGround instance;
	return &instance;
}

void CGround::Move()
{

}