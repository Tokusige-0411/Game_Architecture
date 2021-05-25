#include<DxLib.h>
#include<string>
#include<sstream>
#include<iomanip>
#include<cassert>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetGraphMode(1280, 720, 32);
	ChangeWindowMode(true);
	SetWindowText("1916027_ìøèdå’ëÂòN");

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	int x = 100;
	int y = 100;

	//int gHandle = LoadGraph("Asset/Adventurer-1.5/Individual Sprites/adventurer-run-00.png");
	int gHandle[6] = {};

	for (int i = 0; i < 6; i++)
	{
		std::ostringstream oss;
		oss << "Asset/Adventurer-1.5/Individual Sprites/adventurer-run-";
		oss << std::setw(2);
		oss << std::setfill('0');
		oss << i << ".png";
		gHandle[i] = LoadGraph(oss.str().c_str());
	}

	int frame = 0;

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
		DrawRotaGraph(x, y, 4.0, 0.0, gHandle[frame / 10 % 6], true, false);

		ScreenFlip();

		frame++;
	}

	DxLib_End();
	return 0;
}