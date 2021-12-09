#include <DxLib.h>
#include "TextScroll.h"
#include "SceneManager.h"

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

	//for (auto& info : infos)
	//{
	//	info.pos.x += m_speed * sceneManager_->GetDeltaTime();
	//}
}

void TextScroll::Draw(void)
{
	auto infos = textMap_[type_];

	VECTOR pos = {0.0f, 0.0f, 0.0f};
	for (auto& info : infos)
	{
		for (auto& msg : info.message)
		{
			DrawBillboard3D(info.pos, 0.5f, 0.5f, 20.0f, 0.0f, imageH_[msg], true);
		}
	}
}

void TextScroll::Release(void)
{
	for (int i = 0; i < m_num; i++)
	{
		DeleteGraph(imageH_[i]);
	}
}

MsgInfo TextScroll::MakeMsgInfo(std::string msg, int mapCount)
{
	MsgInfo ret;

	std::vector<int> messages;

	int ascii;
	int len = msg.size();
	for (int i = 0; i < len; i++)
	{
		ascii = msg.at(i);

		if (ascii == 32)
		{
			ascii = 52;
		}

		messages.push_back(ascii);
	}

	ret.pos = { 0.0f, 0.0f, 0.0f };
	ret.message = messages;

	return ret;
}
