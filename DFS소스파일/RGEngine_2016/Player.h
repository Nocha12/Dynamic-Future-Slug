#pragma once
#include "Mover.h"
#include "Arm.h"
#include "Bullet.h"
#include "Grenade.h"
#include "Laser.h"
#include "Sound.h"

class CPlayer : public CMover
{
private:
	bool isOnGround, initialized;
	float gravity, weight, speed,
		armPos[8][2] = { // right arm position
			{ 100,200 },
			{ 100,200 },
			{ 100,200 },
			{ 100,200 },
			{ 100,200 },
			{ 100,200 },
			{ 100,200 },
			{ 100,200 }
	}, leftArmPos[8][2] = { // left arm position
		{ 100, 150 },
		{ 100, 150 },
		{ 100, 150 },
		{ 100, 150 },
		{ 100, 150 },
		{ 100, 150 },
		{ 100, 150 },
		{ 100, 150 }
	};
	Sound *shot;
	Sound *reload;
	int hp, ap;
	int beforeState, state; // 0: stop, 1: walk, 2: jump, 3: sliding, -1: dead
	bool setState;
	// attribute

	CArm *arm;
	bool aimUp, aimDown;
	//arm

	CGrenade *grenades[2];
	//grenade

	bool jump;
	float jumpPower;
	// jump

	float cameraSpeed;
	// camera_view

	//------------
	bool isOnBoard;
	float boardLeft, boardRight, boardTop;
	//-----------

public:
	static bool isLeft;
	int ammo;
	float ultTime;
	float minX, maxX;

public:
	CPlayer();
	~CPlayer();

	void SetArm();
	void MakeBullet(float x, float y, float angle, float angleRate, float speed, float speedRate);
	void Ultimate(float x, float y, float angle);
	void PrecomposeGrenade(CGrenade *grenades[]);
	void ThrowGrenade();
	void ChangeAnimation(int state);

	void Move();
	void OnCollision(GameObject *col);
};

