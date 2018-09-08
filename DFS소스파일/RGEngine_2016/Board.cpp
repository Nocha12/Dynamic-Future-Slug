#include "Board.h"

CBoard::CBoard()
{
	tag = "Board";

	InitImage("resources/Board/Board.png");

	auto collider = AttachComponent<Components::BoxCollider>();
	collider->box.SetRect(
		Math::Vector(0.0f, 0.0f),
		Math::Vector((float)sprite->GetTexture()->GetWidth(), (float)sprite->GetTexture()->GetHeight())
	);
}

CBoard::~CBoard()
{
}

void CBoard::Move()
{

}