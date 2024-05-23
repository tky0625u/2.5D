#include "Player.h"

void Player::Update()
{
	if (!m_bFlg)return;

	//移動=========================================================================================
	Math::Vector3 Move = Math::Vector3::Zero;  //方向ベクトル

	if (GetAsyncKeyState('W') & 0x8000)Move.z = 1.0f;   //上
	if (GetAsyncKeyState('A') & 0x8000)Move.x = -1.0f;  //左
	if (GetAsyncKeyState('S') & 0x8000)Move.z = -1.0f;  //下
	if (GetAsyncKeyState('D') & 0x8000)Move.x = 1.0f;   //右

	Move.Normalize();  //正規化

	m_pos += ((float)status.Spd * SPDCORREC) * Move;  //移動処理
	//=============================================================================================
	
	//プレイヤー　死亡=============================================================================
	if (status.Hp <= 0)
	{
		status.Hp = 0;   //０に補正
		m_bFlg = false;
	}
	//=============================================================================================
	
	//ワールド行列　合成===========================================================================
	Math::Matrix Scale = Math::Matrix::CreateScale(1);              //大きさ
	Math::Matrix Rot = Math::Matrix::CreateRotationX(0);            //回転
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);    //移動
	m_mWorld = Scale * Rot * Trans;                                 //合成
	//=============================================================================================
}

void Player::DrawLit()
{
	if (!m_bFlg)return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Player::Init()
{
	status = { 1,1,1,1 };
	m_pos = { 0,0,0 };
	m_bFlg = true;
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Character/Player/player.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
}
