#pragma once

#include"../PlayerBase.h"

class Ult;
class CutIn;

class Magic :public PlayerBase
{
public:
	Magic() { Init(); }
	~Magic()override{}

	void Update()override;
	void Draw()override;
	void DrawLit()override;
	void DrawBright()override;
	void DrawSprite()override;
	void Init()override;

	const bool GetShot()const { return m_bStop; }

private:
	//カットイン===========================================
	std::shared_ptr<CutIn>  m_cutIn = nullptr;
	KdTexture               m_cutInTex;
	KdTexture               m_pTex;  //プレイヤー画像
	//=====================================================

	//必殺技===============================================
	std::shared_ptr<Ult>    m_ult;
	bool                    m_bUlt;  //必殺技フラグ
	//=====================================================

	bool                    m_bStop;  //停止フラグ
};