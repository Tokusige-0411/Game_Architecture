#include<DxLib.h>
#include<string>
#include<sstream>
#include<iomanip>
#include<cassert>
#include"Geometry.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(true);
	SetWindowText("1916027_徳重虎大朗");

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

	int gHandleB = LoadGraph("image/ground.png");
	int gHandleA = LoadGraph("image/arrow.png");

	int frame = 0;
	int mousePtx = 0;
	int mousePty = 0;
	int frameForAngle = 0;

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

		GetMousePoint(&mousePtx, &mousePty);
		Vector2 dis = {(float)(mousePtx - x), (float)(mousePty - y)};
		float angle = atan2f(dis.y, dis.x);

		ClsDrawScreen();

		// サインカーブを描く
		constexpr size_t blockSize = 32;
		constexpr size_t width = 1000;
		int count = width / blockSize;
		float weight = 800.0f / (float)width;
		int baseY = 240;
		int cx = 0;
		int cy = baseY;
		Vector2 pos0 = { 0, (float)baseY };
		Vector2 lastPos = { 0.0f, 0.0f };
		Vector2 lastDeltaVec[2] = { {0.0f, 0.0f}, {0.0f, 0.0f} };
		for (int i = 0; i < count; i++)
		{
			auto pos1 = pos0;
			auto deltaVec = Vector2(blockSize, (blockSize * 2) * sinf(0.5f * (float)(frameForAngle + blockSize * i) * DX_PI_F / 180.0f)).Normalized() * blockSize;
			pos1 += deltaVec;

			DrawLineAA(lastPos.x, lastPos.y, pos0.x, pos0.y, 0xffffff, 5.0f);

			auto leftPos = lastPos + deltaVec.Rotate90();
			DrawLineAA(lastPos.x, lastPos.y, leftPos.x, leftPos.y, 0xffffff, 1.0f);

			auto rightPos = pos0 + deltaVec.Rotate90();
			DrawLineAA(pos0.x, pos0.y, rightPos.x, rightPos.y, 0xffffff, 1.0f);

			auto middleVec = deltaVec;
			if (lastDeltaVec[0] != Vector2::Zero())
			{
				middleVec = (deltaVec.Rotate90() + lastDeltaVec[0]).Normalized() * blockSize;
			}

			auto middleVec1 = deltaVec;
			if (lastDeltaVec[1] != Vector2::Zero())
			{
				middleVec1 = (lastDeltaVec[0] + lastDeltaVec[1]).Normalized() * blockSize;
			}

			auto middlePosL = lastPos + middleVec1;
			auto middlePosR = pos0 + middleVec;
			DrawLineAA(lastPos.x, lastPos.y, middlePosL.x, middlePosL.y, 0xff0000, 1.0f);

			if (lastPos != Vector2::Zero())
			{
				DrawModiGraph(
					lastPos.x, lastPos.y,
					pos0.x, pos0.y,
					middlePosR.x, middlePosR.y,
					middlePosL.x, middlePosL.y,
					gHandleB, true
				);
			}

			lastPos = pos0;
			pos0 = pos1;
			lastDeltaVec[1] = lastDeltaVec[0];
			lastDeltaVec[0] = deltaVec.Rotate90();
		}

		DrawBox(x, y, x + 100, y + 100, 0xffffff, false);
		DrawString(610, 355, "Hello, World!", 0xffffff);
		DrawRotaGraph(x, y, 4.0, (double)angle, gHandle[frame / 10 % 6], true, false);

		ScreenFlip();

		frame++;
		frameForAngle = (frameForAngle)+1 % 720;
	}

	DxLib_End();
	return 0;
}