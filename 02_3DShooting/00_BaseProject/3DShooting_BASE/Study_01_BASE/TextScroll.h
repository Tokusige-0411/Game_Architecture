#pragma once
#include <DxLib.h>
#include <vector>
#include <map>
#include <string>

class SceneManager;

struct MsgInfo
{
	VECTOR pos;
	std::vector<int> message;
};

class TextScroll
{
public:
	static constexpr int m_num_x = 10;
	static constexpr int m_num_y = 6;
	static constexpr int m_num = m_num_x * m_num_y;

	static constexpr int chip_size = 32;

	enum class Type
	{
		Title
	};

	TextScroll(SceneManager* manager);
	~TextScroll();
	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawGrid(void);
	void Release(void);

private:
	SceneManager* sceneManager_;

	int imageH_[m_num];

	Type type_;

	std::map<Type, std::vector<MsgInfo>> textMap_;

	MsgInfo MakeMsgInfo(std::string msg, int mapCount);
};
