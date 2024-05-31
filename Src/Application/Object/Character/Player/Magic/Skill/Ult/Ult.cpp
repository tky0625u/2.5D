#include "Ult.h"

void Ult::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Trans;
}

void Ult::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Ult::DrawBright()
{
	Draw();
}

void Ult::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Player/Skill/Ult/Fire.gltf");
	m_pos = {};
	m_size = 1.0f;
}

void Ult::SetPos(Math::Vector3 a_pos)
{
	m_pos = a_pos;
}
