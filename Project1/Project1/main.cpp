#include<Dxlib.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetGraphMode(1280, 720, 32);
	ChangeWindowMode(true);
	SetWindowText(L"1916027_ìøèdå’ëÂòN");

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == 0 )
	{
		ClsDrawScreen();

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}