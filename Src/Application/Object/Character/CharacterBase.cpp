#include "CharacterBase.h"

void CharacterBase::Update()
{
}

void CharacterBase::Draw()
{
	if (!m_bFlg)return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void CharacterBase::GenerateDepthMapFromLight()
{
	Draw();
}

void CharacterBase::DrawLit()
{
	Draw();
}

void CharacterBase::Init()
{
}
