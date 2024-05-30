#include "CharacterBase.h"

void CharacterBase::Draw()
{
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
