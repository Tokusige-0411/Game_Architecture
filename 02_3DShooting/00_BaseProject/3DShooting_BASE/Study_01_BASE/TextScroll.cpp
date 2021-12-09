#include <DxLib.h>
#include "TextScroll.h"

TextScroll::TextScroll(SceneManager* manager)
{
	sceneManager_ = manager;
}

TextScroll::~TextScroll()
{
}

void TextScroll::Init(void)
{
	LoadDivGraph("Image/Alphabet.png",
		m_num, m_num_x, m_num_y,
		chip_size, chip_size,
		imageH_
	);

	type_ = Type::Title;

	std::vector<MsgInfo> info;

	info.push_back(MakeMsgInfo("Hello", info.size()));
	info.push_back(MakeMsgInfo("World", info.size()));

	textMap_.emplace(type_, info);
}

void TextScroll::Update(void)
{
	auto infos = textMap_[type_];

	for (auto& info : infos)
	{

	}
}

void TextScroll::Draw(void)
{
	auto infos = textMap_[type_];

	VECTOR pos;
	for (auto& info : infos)
	{
		for (auto& msg : info.message)
		{
			DrawBillboard3D(pos, 0.5f, 0.5f, 20.0f, 0.0f, imageH_[msg], true);
		}
	}
}

void TextScroll::DrawGrid(void)
{
}

void TextScroll::Release(void)
{
}

MsgInfo TextScroll::MakeMsgInfo(std::string msg, int mapCount)
{
	return MsgInfo();
}
