#include "Magic.h"
#include"../../../../WindowUI/WindowUI.h"
#include"Skill/Ult/Ult.h"
#include"Skill/CutIn/CutIn.h"

void Magic::Update()
{
	if (!m_bFlg)return;

	//必殺技===================================================================================================================================================
	if (!m_bUlt)
	{
		//カットイン========================================================================================================
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (!m_bStop)
			{
				m_cutIn = std::make_shared<CutIn>();
				m_cutIn->SetTexture(&m_cutInTex,&m_pTex);
				m_bStop = true;
			}
		}
		//==================================================================================================================
		
		//出現==============================================================================================================
		if (m_cutIn != nullptr && m_cutIn->IsExpired())  //カットインが終わったら
		{
			//カットイン消滅
			m_cutIn.reset();
			m_cutIn = nullptr;

			//必殺技生成
			m_ult = std::make_shared<Ult>();  //生成
			m_ult->SetPos({ m_pos.x + sin(DirectX::XMConvertToRadians(m_angle)) * DEFAULTPOS,m_pos.y,m_pos.z + cos(DirectX::XMConvertToRadians(m_angle)) * DEFAULTPOS });  //座標 ※プレイヤーの少し前
			m_ult->SetAngle(m_angle);  //角度　※プレイヤーの目の前に来るように
			m_bUlt = true; //フラグオン　※二度撃ち防止
		}
		else if(m_cutIn != nullptr)
		{
			m_cutIn->Update();
		}
		//==================================================================================================================
	}
	else
	{
		if (m_ult->GetSize() < SIZEMAX)  //サイズが小さい時はプレイヤーの目の前に来るようにする
		{
			m_ult->SetPos({ m_pos.x + sin(DirectX::XMConvertToRadians(m_angle)) * DEFAULTPOS,m_pos.y,m_pos.z + cos(DirectX::XMConvertToRadians(m_angle)) * DEFAULTPOS });
			m_ult->SetAngle(m_angle);
		}
		else m_bStop = false;

		m_ult->Update();

		if (m_ult->IsExpired())  //消滅したらリセット
		{
			m_ult.reset();
			m_bUlt = false;
		}
	}
	//==============================================================================================================================================================

	if(!m_bStop)PlayerBase::Update();
}

void Magic::Draw()
{
	if (!m_bFlg)return;
	PlayerBase::Draw();
}

void Magic::DrawLit()
{
	PlayerBase::DrawLit();

	//必殺技===============================
	if (m_bUlt)m_ult->DrawLit();
	//=====================================
}

void Magic::DrawBright()
{
	//必殺技===============================
	if (m_bUlt)m_ult->DrawBright();
	//=====================================
}

void Magic::DrawSprite()
{
	//カットイン===========================
	if (m_cutIn != nullptr)m_cutIn->DrawSprite();
	//=====================================
}

void Magic::Init()
{
	//カットイン===============================================================
	m_cutInTex.Load("Asset/Textures/CutIn/CutInYellow.png");
	m_pTex.Load("Asset/Textures/Character/Player/player.png");
	//=========================================================================

	//プレイヤー===============================================================
	PlayerBase::Init();
	status = { 1,1,1,1,1 };
	m_polygon->SetMaterial("Asset/Textures/Character/Player/player.png");
	//=========================================================================

	m_bUlt = false;   //必殺技
	m_bStop = false;  //停止
}
