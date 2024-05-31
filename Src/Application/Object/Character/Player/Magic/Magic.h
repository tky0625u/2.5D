#pragma once

#include"../PlayerBase.h"

class Ult;

class Magic :public PlayerBase
{
public:
	Magic() { Init(); }
	~Magic()override{}

	void Update()override;
	void Draw()override;
	void DrawLit()override;
	void DrawBright()override;
	void Init()override;

private:
	std::shared_ptr<Ult> m_ult;
	bool                 m_bUlt;
};