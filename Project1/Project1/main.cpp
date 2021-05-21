#include<DxLib.h>
#include<string>
#include<sstream>
#include<iomanip>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetGraphMode(1280, 720, 32);
	ChangeWindowMode(true);
	SetWindowText("1916027_���d�Ց�N");

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	int x = 100;
	int y = 100;

	//int gHandle = LoadGraph("Asset/Adventurer-1.5/Individual Sprites/adventurer-run-00.png");
	//int gHandle[6] = {};

	while (ProcessMessage() == 0)
	{
		if (CheckHitKey(KEY_INPUT_UP))
		{
			y -= 5;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			y += 5;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			x += 5;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			x -= 5;
		}

		ClsDrawScreen();

		DrawBox(x, y, x + 100, y + 100, 0xffffff, false);
		DrawString(610, 355, "Hello, World!", 0xffffff);
		//DrawRotaGraph(x, y, 4.0, 0.0, gHandle, true, false);

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}