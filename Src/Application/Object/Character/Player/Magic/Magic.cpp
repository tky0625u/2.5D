#include "Magic.h"

void Magic::Update()
{
	if (!m_bFlg)return;
	PlayerBase::Update();
}

void Magic::Draw()
{
	if (!m_bFlg)return;
	PlayerBase::Draw();
}

void Magic::Init()
{
	PlayerBase::Init();
	status = { 1,1,1,1,1 };
	m_polygon->SetMaterial("Asset/Textures/Character/Player/player.png");
}
