#pragma once

#define SPDCORREC 0.3f  //スピード補正

//アニメーション配列======================
#define ANIMECUT1 4    //縦
#define ANIMESPD 0.1f  //アニメーション速度
//========================================

class CharacterBase :public KdGameObject
{
public:
	//ステータス==============================
	struct Status
	{
		int Hp;   //体力
		int Mp;   //魔力
		int Atk;  //攻撃力
		int Def;  //防御力
		int Spd;  //素早さ
	};
	//========================================

	//キャラタイプ============================
	enum CharaType
	{
		Player = 1 << 0,
		Enemy  = 1 << 1,
	};
	//========================================

	 CharacterBase() {}
	 ~CharacterBase()override{}

	 virtual void Update()override = 0;
	 virtual void Draw() = 0;
	 void GenerateDepthMapFromLight()override;
	 void DrawLit()override;
	 virtual void Init() override = 0;

	 const float GetAngle() const { return m_angle; }

protected:
	//アニメーション=====================================
	int   m_direc;  //縦
	float m_anime;  //横
	//===================================================

	Status status;                               //ステータス
	CharaType type;                              //キャラタイプ
	float m_size;                                //サイズ
	float m_angle;                               //角度
	bool m_bFlg;                                 //生存フラグ
	std::shared_ptr<KdSquarePolygon> m_polygon;  //板ポリ
	Math::Vector3 m_pos;                         //座標
	Math::Vector3 m_move;                        //方向ベクトル
};