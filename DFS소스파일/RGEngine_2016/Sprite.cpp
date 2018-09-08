#include "Sprite.h"
#include "GameManager.h"

Sprite::Sprite(std::string path) : faid(0), isFaidIn(false), isFaidOut(false), isFaidInNOut(false)
{
	sprite = AttachComponent<Components::SpriteRenderer>();
	sprite->SetTexture(path); // 반드시 해주어야 함
}

void Sprite::OnUpdate()
{
	if (!GM->isPause)
		if (isFaidIn)
			if (faid < 1)
				sprite->GetTexture()->color.SetColor(1.0f, 1.0f, 1.0f, faid += 0.01f);
			else if (isFaidInNOut)
			{
				isFaidInNOut = false;
				isFaidOut = true;
				isFaidIn = false;
			}
			else
				isFaidIn = false;
		else if (isFaidOut)
		{
			if (faid > 0)
				sprite->GetTexture()->color.SetColor(1.0f, 1.0f, 1.0f, faid -= 0.01f);
			else if (isDestroy)
				this->Destroy();
			else
				isFaidOut = false;
		}
}
