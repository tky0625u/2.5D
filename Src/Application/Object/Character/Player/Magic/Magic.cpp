#include "Magic.h"
#include"Skill/Ult/Ult.h"

void Magic::Update()
{
	if (!m_bFlg)return;

	if (!m_bUlt)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			m_ult = std::make_shared<Ult>();
			m_ult->SetPos({m_pos.x,m_pos.y+5,m_pos.z});
			m_bUlt = true;
		}
	}

	PlayerBase::Update();

	if (m_bUlt)m_ult->Update();
}

void Magic::Draw()
{
	if (!m_bFlg)return;
	PlayerBase::Draw();
}

void Magic::DrawLit()
{
	PlayerBase::DrawLit();
	if (m_bUlt)m_ult->DrawLit();
}

void Magic::DrawBright()
{
	if (m_bUlt)m_ult->DrawBright();
}

void Magic::Init()
{
	PlayerBase::Init();
	status = { 1,1,1,1,1 };
	m_polygon->SetMaterial("Asset/Textures/Character/Player/player.png");

	m_bUlt = false;
}
