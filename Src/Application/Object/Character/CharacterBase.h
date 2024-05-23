#pragma once

#define SPDCORREC 0.5f  //スピード補正
#define FALLSPD   0.05f  //落下速度

//アニメーション配列======================
#define ANIMECUT1 4    //縦
#define ANIMECUT2 4    //横
#define ANIMESPD 0.1f  //アニメーション速度
//========================================

//ステータス==============================
struct Status
{
	int Hp;   //体力
	int Atk;  //攻撃力
	int Def;  //防御力
	int Spd;  //素早さ
};
//========================================

class CharacterBase :public KdGameObject
{
public:
	 CharacterBase() { Init(); }
	 ~CharacterBase()override{}

	 virtual void Update()override = 0;
	 virtual void Draw() = 0;
	 void GenerateDepthMapFromLight()override;
	 void DrawLit()override;
	 virtual void Init() override = 0;

protected:
	//アニメーション=====================================
	float m_anime;  //横
	int   m_direc;  //縦
	//===================================================

	float m_size;
	float m_angle;
	bool m_bFlg;
	std::shared_ptr<KdSquarePolygon> m_polygon;
	Status status;
	Math::Vector3 m_pos;
	Math::Vector3 m_move;  //方向ベクトル
};