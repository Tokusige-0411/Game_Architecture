#include <DxLib.h>
#include "TextScroll.h"
#include "SceneManager.h"

namespace
{
	constexpr float msg_diff_z = -30.0f;
	constexpr float msg_diff_x = 20.0f;
}

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

	info.emplace_back(MakeMsgInfo("Hello", info.size()));
	info.emplace_back(MakeMsgInfo("World", info.size()));

	textMap_.emplace(type_, info);
	int count = 0;
	for (auto& text : textMap_[type_])
	{
		text.pos.z = -400 + count * msg_diff_z;
		count++;
	}
}

void TextScroll::Update(void)
{
	auto& infos = textMap_[type_];

	for (auto& info : infos)
	{
		info.pos.z = info.pos.z + (m_speed * sceneManager_->GetDeltaTime());
	}
}

void TextScroll::Draw(void)
{
	auto& infos = textMap_[type_];

	for (auto& info : infos)
	{
		int count = 0;
		for (auto& msg : info.message)
		{
			info.pos.x = -100 + count * msg_diff_x;
			DrawBillboard3D(info.pos, 0.5f, 0.5f, 20.0f, 0.0f, imageH_[msg], true);
			count++;
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

		if (ascii >= 65 && ascii <= 90)
		{
			ascii = ascii - 65;
		}
		if (ascii >= 97 && ascii <= 122)
		{
			ascii = ascii - 97;
		}
		if (ascii == 32)
		{
			ascii = 52;
		}
		if (ascii == 46)
		{
			ascii = 53;
		}
		if (ascii == 44)
		{
			ascii = 54;
		}

		messages.push_back(ascii);
	}

	ret.pos = { 0.0f, 0.0f, 0.0f };
	ret.message = messages;

	return ret;
}
