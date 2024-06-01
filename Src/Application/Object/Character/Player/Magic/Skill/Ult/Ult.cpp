#include "Ult.h"

void Ult::Update()
{
	
	if (m_size < SIZEMAX)
	{
		m_size += SIZEUP;  //サイズ増加
		m_CirecleSize+=CicleSizeUP;
	}
	else
	{
		//プレイヤーの向いている方向飛ばす=====================================
		m_pos.z += cos(DirectX::XMConvertToRadians(m_angle)) * SPEED;
		m_pos.x += sin(DirectX::XMConvertToRadians(m_angle)) * SPEED;
		//=====================================================================
		m_AliveTime++;  //生存時間増加
		m_CirecleSize-=CicleSizeDown;
		m_CirecleAngle++;
		if (m_CirecleSize <= 0)m_isExpired = true; //生存時間を過ぎたら消滅
	}

	if (m_CirecleAngle >= 360.0f)m_CirecleAngle -= 360.0f;

	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Trans;

	Math::Matrix CircleScale = Math::Matrix::CreateScale(m_CirecleSize);
	Math::Matrix CircleRotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));
	Math::Matrix CircleRotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_CirecleAngle));
	Math::Matrix CircleTrans = Math::Matrix::CreateTranslation(m_CirclePos);
	m_CircleMat = CircleScale * CircleRotX * CircleRotY * CircleTrans;
	
}

void Ult::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_CircleMat);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Ult::DrawLit()
{
	Draw();
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
	m_AliveTime = 0;
	m_Atk = 5;
	m_PlayerAtk = 0;
	m_size = 1.0f;
	m_angle = 0.0f;

	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Effect/magic circle red.png");
	m_CirclePos = {};
	m_CirecleAngle = 0.0f;
	m_CirecleSize = 0.0f;
}

void Ult::SetPos(Math::Vector3 a_pos)
{
	m_pos = a_pos;
}
