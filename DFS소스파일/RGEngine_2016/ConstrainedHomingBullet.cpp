#include "ConstrainedHomingBullet.h"

CConstrainedHomingBullet::CConstrainedHomingBullet(BulletShape shapeType, float x,
	float y, float angle, float speed, float maxAngleRate)
	:CBullet(x, y, angle, 0, speed, 0), MaxAngleRate(maxAngleRate)
{
}


CConstrainedHomingBullet::~CConstrainedHomingBullet()
{
}

void CConstrainedHomingBullet::Move()
{
	//선회 각속도 계산
	float angleRate = GetMyShipAngle(this->center.x, this->center.y)-Angle;
	
	//선회 각속도를 0.0~1.0의 범위로 한정
	angleRate -= floor(angleRate);
	

	if (angleRate <= MaxAngleRate || (1.0f - angleRate) <= MaxAngleRate)
	{
		//선회 각속도가 최대 선회 각속도 이하이면
		//선회 각속도로 선회
		Angle += angleRate;
	}
	else 
	{
		//선회 각속도가 최대 선회 각속도보다 클 경우
		//최대 선회 각속도로 선회
		Angle += (angleRate < 0.5f) ? MaxAngleRate : -MaxAngleRate;
	}

	//각도를 0.0~1.0의 범위로 한정
	Angle -= floor(Angle);

	//기본적인 탄 이동 처리 호출
	CBullet::Move();
}

float CConstrainedHomingBullet::GetMyShipAngle(float x, float y)
{
	return NULL;
	//플레이어 유도
		//return atan2f(RGApp->GetScene<CPlayStage>()->GetPlayer()->realy - y,
		//	RGApp->GetScene<CPlayStage>()->GetPlayer()->realx - x) / D3DX_PI / 2;
}
