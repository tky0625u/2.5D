#include "Player.h"

void Player::Update()
{
	if (!m_bFlg)return;

	//アニメーション===================================================================================================
	int Walk[ANIMECUT1][ANIMECUT2] = { {0,1,2,1},{3,4,5,4},{6,7,8,7},{9,10,11,10} };  //アニメーション配列
	m_polygon->SetUVRect(Walk[m_direc][(int)m_anime]);                                //描画設定
	m_anime += ANIMESPD;                                                              //アニメーション処理
	if (m_anime >= ANIMECUT2)m_anime = 0;                                             //最後まできたら最初に戻す
	if (m_move == Math::Vector3::Zero)m_anime = 1;                                    //立ち止まり
	//=================================================================================================================

	//行動=============================================================================================================

	//ジャンプ===========================================================================
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		//二段ジャンプ防止===========================
		if (!m_jumpFlg)
		{
			m_jumpMove = JUMPPOW;
			m_jumpFlg = true;
		}
		//===========================================
	}
	
	//落下処理=======================================================
	if (m_pos.y > 0 && m_jumpFlg)  //ジャンプ中
	{
		m_jumpMove -= FALLSPD;  //落下速度代入
		//地面埋まり防止=============================
		if (m_pos.y + m_jumpMove <= 0.0f)
		{
			m_jumpMove = 0.0f;
			m_pos.y = 0.0f;
		}
		//===========================================
	}
	else
	{
		m_jumpFlg = false;
	}
	//===============================================================

	m_pos.y += m_jumpMove;  //速度代入
	//===================================================================================

	//移動===============================================================================
	m_move = Math::Vector3::Zero;  //方向ベクトル

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_move.z = 1.0f;   //上
		m_direc = UP;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_move.x = -1.0f;  //左
		m_direc = LEFT;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_move.z = -1.0f;  //下
		m_direc = DOWN;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_move.x = 1.0f;   //右
		m_direc = RIGHT;
	}

	m_move.Normalize();  //正規化

	          //      ↓*速度制御*↓     //
	m_pos += ((float)status.Spd * SPDCORREC) * m_move;  //速度代入
	//===================================================================================
	
	//=================================================================================================================
	
	//プレイヤー　死亡=================================================================================================
	if (status.Hp <= 0)
	{
		status.Hp = 0;   //０に補正
		m_bFlg = false;
		m_isExpired = true;
	}
	//=================================================================================================================
	
	//ワールド行列　合成===============================================================================================
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);       //大きさ
	Math::Matrix Rot = Math::Matrix::CreateRotationX(m_angle);    //回転
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);  //移動
	m_mWorld = Scale * Rot * Trans;                               //合成
	//=================================================================================================================
}

void Player::Draw()
{
	if (!m_bFlg)return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Player::Init()
{
	m_size = 1.0f;
	m_angle = 0.0f;
	status = { 1,1,1,1 };
	m_pos = { 0,0,0 };
	m_move = Math::Vector3::Zero;
	m_anime = 0;
	m_direc = 0;
	m_jumpMove = 0.0f;
	m_jumpFlg = false;
	m_bFlg = true;
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Character/Player/player.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon->SetSplit(3, 4);
}
