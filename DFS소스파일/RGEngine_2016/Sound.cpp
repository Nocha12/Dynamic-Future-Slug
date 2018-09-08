#include "Sound.h"
#include "GameManager.h"

Sound::Sound(std::string path) : faid(0), isFaidIn(false), isFaidOut(false)
{
	name = "sound";

	audio = AttachComponent<Components::AudioSource>();
	audio->SetSound(path); // 반드시 해주어야 함

						   // 볼륨조절 등의 작업은 반드시 재생 이후에 해야함.
	audio->SetVolume(0.1f);
}
Sound::Sound(std::string path, int loopcount)
{
	audio = AttachComponent<Components::AudioSource>();

	RGAssetSound->Load(path, loopcount);
	audio->SetSound(path); // 반드시 해주어야 함

	if(loopcount != 0)
		audio->Play();
	audio->SetVolume(0.1f);
}

void Sound::OnUpdate()
{
	if (!GM->isPause)
		if (isFaidIn)
			if (faid < maxSound)
				audio->SetVolume(faid += 0.001f);
			else
				isFaidIn = false;
		else if (isFaidOut)
			if (faid > 0)
				audio->SetVolume(faid -= 0.001f);
			else
				isFaidOut = false;
}
