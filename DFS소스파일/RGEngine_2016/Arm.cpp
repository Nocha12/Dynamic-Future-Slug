#include "Arm.h"
#include "Player.h"

CArm::CArm()
{
	InitImage("resources/Player/arm.png");
	//InitImage("resources/line.png");
	rotationCenter.SetVector(10, 25);
	sprite->GetGameObject()->rotationCenter.SetVector(10, 25);
}


CArm::~CArm()
{
}

void CArm::Move()
{
}