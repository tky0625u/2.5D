#include "Player.h"

void Player::Update()
{
	if (!m_bFlg)return;

	//アニメーション===================================================================================================
	int Walk[ANIMECUT1]= {9,10,11,10};  //アニメーション配列
	m_polygon->SetUVRect(Walk[(int)m_anime]);                                //描画設定
	m_anime += ANIMESPD;                                                              //アニメーション処理
	if (m_anime >= ANIMECUT1)m_anime = 0;                                             //最後まできたら最初に戻す
	if (m_move == Math::Vector3::Zero)m_anime = 1;                                    //立ち止まり
	//=================================================================================================================

	//行動=============================================================================================================

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)m_angle += 1.0f;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)m_angle -= 1.0f;

	if (m_angle > 360.0f)m_angle -= 360.0f;

	//移動===============================================================================
	m_move = Math::Vector3::Zero;  //方向ベクトル

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_move.z = 1.0f;   //上
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_move.x = -1.0f;  //左
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_move.z = -1.0f;  //下
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_move.x = 1.0f;   //右
	}

	m_move.Normalize();  //正規化

	          //      ↓*速度制御*↓     //
	m_pos += ((float)status.Spd * SPDCORREC) * m_move;  //速度代入
	//===================================================================================
	
	//=================================================================================================================
	
	//プレイヤー　死亡=================================================================================================
	if (status.Hp <= 0)
	{
		status.Hp = 0;   //０に制御
		m_bFlg = false;
		m_isExpired = true;
	}
	//=================================================================================================================
	
	//ワールド行列　合成===============================================================================================
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);       //大きさ
	Math::Matrix Rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));    //回転
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);  //移動
	m_mWorld = Scale * Rot * Trans;                               //合成
	//=================================================================================================================
}

void Player::Draw()
{
	CharacterBase::Draw();
}

void Player::Init()
{
	m_size = 1.0f;
	m_angle = 0.0f;
	status = { 1,1,1,1,1 };
	m_pos = Math::Vector3::Zero;
	m_move = Math::Vector3::Zero;
	m_anime = 0;
	m_bFlg = true;
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Character/Player/player.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon->SetSplit(3, 4);
}
