#include "RGEngine.h"
#include "MainScene.h"

int main(void)
{
	SetCursor(false);
	RGApp->Initialize(L"Dynamic Future Slug", 1280, 1024, false);
	RGAsset->Initialize();

	RGApp->ChangeScene(new MainScene());

	while (RGGraphic->Validate())
	{
		if (RGGraphic->Process())
		{
			RGApp->Update();

			if (RGGraphic->BeginScene())
			{
				RGApp->Render();
				
				RGGraphic->EndScene();
			}
		}
	}

	return 0;
}