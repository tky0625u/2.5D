#include "PlayerBase.h"

void PlayerBase::Update()
{

	//アニメーション===================================================================================================
	int Walk[ANIMECUT1] = { 9,10,11,10 };                                             //アニメーション配列
	m_polygon->SetUVRect(Walk[(int)m_anime]);                                         //描画設定
	m_anime += ANIMESPD;                                                              //アニメーション処理
	if (m_anime >= ANIMECUT1)m_anime = 0;                                             //最後まできたら最初に戻す
	if (m_move == Math::Vector3::Zero)m_anime = 1;                                    //立ち止まり
	//=================================================================================================================

	//行動=============================================================================================================

	//回転===============================================================================
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)m_angle -= 1.0f;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)m_angle += 1.0f;

	if (m_angle > 360.0f)m_angle -= 360.0f;  //角度制御
	//===================================================================================

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

	//前後=============================================================================================================
																   //      ↓*速度制御*↓     //                     前 右 後 左
	m_pos.z += cos(DirectX::XMConvertToRadians(m_angle)) * (((float)status.Spd * SPDCORREC) * m_move.z);  //速度代入  1  0 -1  0=cos
	m_pos.x += sin(DirectX::XMConvertToRadians(m_angle)) * (((float)status.Spd * SPDCORREC) * m_move.z);  //速度代入  0  1  0 -1=sin
	//=================================================================================================================
	//左右=============================================================================================================
	m_pos.z += -sin(DirectX::XMConvertToRadians(m_angle)) * (((float)status.Spd * SPDCORREC) * m_move.x); //速度代入  0 -1  0  1=-sin
	m_pos.x += cos(DirectX::XMConvertToRadians(m_angle)) * (((float)status.Spd * SPDCORREC) * m_move.x);  //速度代入  1  0 -1  0=cos
	//=================================================================================================================

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

void PlayerBase::Draw()
{
	CharacterBase::Draw();
}

void PlayerBase::Init()
{
	type = CharaType(CharaType::Player);
	m_size = 1.0f;
	m_angle = 0.0f;
	m_pos = Math::Vector3::Zero;
	m_move = Math::Vector3::Zero;
	m_anime = 0;
	m_bFlg = true;
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon->SetSplit(3, 4);
}
